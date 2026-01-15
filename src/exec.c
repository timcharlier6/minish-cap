/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:39:25 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/15 18:45:56 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_external(t_cmd_table *cmd, char **envp)
{
	char *path;

	path = NULL;
	if (!envp)
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
		return (free(path), 126);
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
		return(builtin_exit(cmd->args, m));
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
	if (handle_redirections(cmd) != 0)
	 	exit (1);
	if (is_builtin(cmd->args[0]) != 0)
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

int	exec(t_main *m, t_env *env)
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
