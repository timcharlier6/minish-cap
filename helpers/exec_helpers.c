/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:11:38 by ticharli          #+#    #+#             */
/*   Updated: 2026/01/21 14:12:04 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd,
			"cd") || !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	run_builtin(t_main *m, t_cmd_table *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (my_echo(cmd));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (pwd());
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (cd(cmd, m->env));
	else if (ft_strcmp(cmd->args[0], "env") == 0 && !cmd->args[1])
		return (my_env(m->env));
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (export(cmd, m->env));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (unset(cmd, m->env));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
		return (builtin_exit(cmd->args, m));
	}
	return (0);
}
