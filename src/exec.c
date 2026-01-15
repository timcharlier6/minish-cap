/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:39:25 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/15 16:28:40 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_external(t_cmd_table *cmd, char **envp)  //MODIFS ICI
{
	char *path;

	path = NULL;
	if (!envp) // AJOUT protec execution fonction ds argument
		return (0);
	if (!cmd->args || !cmd->args[0]) 
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		return (127);
	}
	if (access(cmd->args[0], X_OK) == 0) // chemin direct absolu ou relatif
	{
		execve(cmd->args[0], cmd->args, envp);
		perror("execve");
		return (126);
    }
	path = find_path(cmd->args[0], envp);
	if (path)
	{
		execve(path, cmd->args, envp);
		perror("execve");
		free(path);
		return (126);
	}
	ft_putstr_fd("minishell: command not found\n", 2);
	return (127);
}

static int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd,
			"cd") || !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

static int	run_builtin(t_main *m, t_cmd_table *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (my_echo(cmd));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (pwd());
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (cd(cmd, m->env));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (my_env(m->env));
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (export(cmd, m->env));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (unset(cmd, m->env));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
		printf("exit\n");
		clean_up(m, 1, 1);
		exit(0);
	}
	return (0);
}

static int	handle_redirections(t_cmd_table *cmd)
{
	t_redir	*tmp;
	int		fd;

	tmp = cmd->infile;
	while (tmp)
	{
		if (tmp->type == T_REDIR_IN)
		{
			fd = open(tmp->name, O_RDONLY);
			if (fd == -1)
				return (perror(tmp->name), 1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		tmp = tmp->next;
	}
	tmp = cmd->outfile;
	while (tmp)
	{
		fd = -1;
		if (tmp->type == T_REDIR_OUT)
			fd = open(tmp->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (tmp->type == T_REDIR_APPEND)
			fd = open(tmp->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (perror(tmp->name), 1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		tmp = tmp->next;
	}
	return (0);
}

static void	child_process(t_main *m, t_cmd_table *cmd, int prev_fd,
		int pipe_fd[2], t_env *env)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if (handle_redirections(cmd))
	 	exit(1);
	// if (cmd->infile && !handle_redir_in(cmd->infile)) // <--- AJOUT ICI
	// 	return ;
	// if (cmd->outfile && !handle_redir_out(cmd->outfile)) // <--- AJOUT ICI
	// 	return ;
	if (is_builtin(cmd->args[0]))
		exit(run_builtin(m, cmd));
	else
		exit(exec_external(cmd, copy_list_to_array(env))); // EXIT CHILD IF EXECVE FAILS
}

static int	wait_children(pid_t last_pid)
{
	int	status;
	int	exit_status;

	exit_status = 0;
	if (last_pid > 0)
	{
		waitpid(last_pid, &status, 0);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (exit_status);
}

static int	execute_pipeline(t_main *m, int *pipe_fd, int prev_fd, t_env *env)
{
	t_cmd_table	*cmd;
	pid_t		pid;

	cmd = m->cmd_table;
	pid = -1;
	while (cmd)
	{
		if (cmd->next && pipe(pipe_fd) == -1)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		if (pid == 0)
			child_process(m, cmd, prev_fd, pipe_fd, env);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		cmd = cmd->next;
	}
	return (wait_children(pid));
}

// MODIFS ICI --> refonte de la logique pour que execve fasse pas quitter le shell (exemple->/bin/ls) ->  meme si !cmd->next, les execs doivent etre executes ds child process
int	exec(t_main *m, t_env *env) // use my linked list for env in builtins (evrywhere other than execve) cause it's the one that gets updated.
{
	int	pipe_fd[2];

	if (!m || !m->cmd_table || !m->cmd_table->args
		|| !m->cmd_table->args[0] || !env) //ajout de !envp
		return (0);
	if (!m->cmd_table->next && is_builtin(m->cmd_table->args[0]))
		m->last_status = run_builtin(m, m->cmd_table);
	else
		m->last_status = execute_pipeline(m, pipe_fd, -1, env);
	return (m->last_status);
}

// int exec(t_main *m)
// {
// 	if (is_builtin(m) == 2)
// 	{
// 		if (!command_path_finder(m, m->env))
// 			return (0);
// 	}
// 	return(0);
// }
