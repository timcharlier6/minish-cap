/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:39:25 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/23 20:09:34 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// signal_ignore ->desactivation des signaux
static int	execute_pipeline(t_main *m, int *pipe_fd, int prev_fd)
{
	t_cmd_table	*cmd;
	pid_t		pid;

	cmd = m->cmd_table;
	while (cmd)
	{
		if (cmd->next)
			pipe(pipe_fd);
		signal_ignore();
		pid = fork();
		if (pid == 0)
			child_process(m, cmd, prev_fd, pipe_fd);
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

// signal_init -> retablissement de la config SIGNAL d origine
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
