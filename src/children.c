/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:10:36 by ticharli          #+#    #+#             */
/*   Updated: 2026/01/23 20:10:46 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ajojut de m->cmd au lieu de juste cmd, afin de pouvoir free ds child
int	exec_local(t_cmd_table *cmd, char **envp)
{
	DIR	*dir;

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

int	exec_external(t_cmd_table *cmd, char **envp)
{
	char	*path;
	int		return_status;

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

void	child_process(t_main *m, t_cmd_table *cmd, int prev_fd,
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
