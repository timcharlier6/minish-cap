/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:42:25 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/08 18:27:29 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_echo_fd(t_cmd_table *cmd)
{
	t_redir	*tmp;
	int		fd;

	fd = 1;
	tmp = cmd->outfile;
	while (tmp)
	{
		if (fd != 1)
			close(fd);
		if (tmp->type == T_REDIR_OUT)
			fd = open(tmp->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (tmp->type == T_REDIR_APPEND)
			fd = open(tmp->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("minishell");
			return (-1);
		}
		tmp = tmp->next;
	}
	return (fd);
}

int	my_echo(t_cmd_table *cmd)
{
	int i;
	int n_flag;
	int fd;

	i = 1;
	n_flag = 0;
	while (cmd->args[i] && !ft_strncmp(cmd->args[i], "-n", 3))
	{
		n_flag = 1;
		i++;
	}
	fd = get_echo_fd(cmd);
	if (fd == -1)
		return (1);
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], fd);
		if (cmd->args[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (!n_flag)
		write(fd, "\n", 1);
	if (fd != 1)
		close(fd);
	return (0);
}