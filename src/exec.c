/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:39:25 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/22 18:36:54 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ajojut de m->cmd au lieu de juste cmd, afin de pouvoir free ds child
static int	exec_local(t_cmd_table *cmd, char **envp)
{
	DIR			*dir;

	dir = opendir(cmd->args[0]);
	if (dir)
		return (closedir(dir), errmsg_cmd(cmd->args[0], "Is a directory", 126));
	if (access(cmd->args[0], F_OK) != 0)
		return (errmsg_cmd(cmd->args[0], "No such file or directory", 127));
	if (access(cmd->args[0], X_OK) != 0)
		return (errmsg_cmd(cmd->args[0], "Permission denied", 126));
	execve(cmd->args[0], cmd->args, envp);
	return (perror("execve"), 126);
}

int	exec_external(t_cmd_table	*cmd, char **envp)
{
	char		*path;
	int			return_status;

	return_status = 0;
	if (!envp)
		return (0);
	if (!cmd->args || !cmd->args[0])
	{
		return_status = errmsg_cmd(NULL, "command not found", 127);
		return (free_array(envp), return_status);
	}
	if (ft_strchr(cmd->args[0], '/') != -1)
	{
		return_status = exec_local(cmd, envp);
		return (free_array(envp), return_status);
	}
	path = find_path(cmd->args[0], envp);
	if (path)
	{
		execve(path, cmd->args, envp);
		perror("execve");
		return (free_array(envp), free(path), 126);
	}
	return_status = errmsg_cmd(cmd->args[0], "command not found", 127);
	return (free_array(envp), return_status);
}

static void	child_process(t_main *m, t_cmd_table *cmd, int prev_fd,
		int pipe_fd[2])
{
	t_env	*env;
	int		exit_status;

	exit_status = 0;
	env = m->env;
	signal_init_to_default();
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
	if (handle_redirections(cmd, env, m->last_status) != 0)
		clean_up(m, 1, 1, 1);
	if (is_builtin(cmd->args[0]) != 0)
		exit_status = (run_builtin(m, cmd));
	else
		exit_status = (exec_external(cmd, copy_list_to_array(env)));
	clean_up(m, 1, 1, 0);
	exit(exit_status);
}

// line 88 : status de l'enfant +CTRL-C
static int	wait_children(pid_t last_pid)
{
	int	status;
	int	exit_status;

	exit_status = 0;
	if (last_pid > 0)
	{
		waitpid(last_pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			exit_status = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGINT)
				write(1, "\n", 1);
			else if (WTERMSIG(status) == SIGQUIT)
				write(1, "Quit (core dumped)\n", 19);
		}
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (exit_status);
}

/*
flow:
  - parent:
		- create two pipes
		- fork child
		- write data to pipe1 (write end)
  - child:
		- read data from pipe1 (read end)
		- process data
		- write result to pipe2 (write end)
  - parent:
		- read result from pipe2 (read end)
		- wait for child to exit
*/

//signal_ignore ->desactivation des signaux
static int	execute_pipeline(t_main *m, int *pipe_fd, int prev_fd)
{
	t_cmd_table	*cmd;
	pid_t		pid;

	cmd = m->cmd_table;
	while (cmd)
	{
		if (cmd->next) // S'il y a une commande suivante, on crée un pipe
			pipe(pipe_fd);
		signal_ignore();
		pid = fork();
		if (pid == 0)
			child_process(m, cmd, prev_fd, pipe_fd);
		// PARENT : On ferme les FDs dont on n'a plus besoin
		if (prev_fd != -1)
			close(prev_fd); // Ferme la lecture de la commande précédente
		if (cmd->next)
		{
			close(pipe_fd[1]); // Ferme l'écriture du pipe actuel
			prev_fd = pipe_fd[0]; // Garde la lecture pour la commande suivante
		}
		cmd = cmd->next;
	}
	return (wait_children(pid));
}

//signal_init -> retablissement de la config SIGNAL d origine
int	exec(t_main *m, t_env *env)
{
	int	pipe_fd[2];

	if (!m || !m->cmd_table || !m->cmd_table->args || !m->cmd_table->args[0]
		|| !env)
		return (0);
	if (!m->cmd_table->next && is_builtin(m->cmd_table->args[0]))
		m->last_status = run_builtin(m, m->cmd_table);
	else
	{
		m->last_status = execute_pipeline(m, pipe_fd, -1);
		signal_init();
	}
	return (m->last_status);
}
