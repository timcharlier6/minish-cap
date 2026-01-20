/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:31:18 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/20 17:54:56 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_main *m)
{
	int	got_in;

	got_in = 2;
	if (!m || !m->cmd_table || !m->cmd_table->args || !m->cmd_table->args[0])
		return (0);
	if (ft_strcmp(m->cmd_table->args[0], "echo") == 0)
		got_in = my_echo(m->cmd_table);
	if (ft_strcmp(m->cmd_table->args[0], "pwd") == 0)
		got_in = pwd();
	if (ft_strcmp(m->cmd_table->args[0], "cd") == 0)
		got_in = cd(m->cmd_table, m->env);
	if (ft_strcmp(m->cmd_table->args[0], "env") == 0)
		got_in = my_env(m->env);
	if (ft_strcmp(m->cmd_table->args[0], "exit") == 0)
		got_in = builtin_exit(m->cmd_table->args, m);
	else
		m->last_status = 0;
	return (got_in);
}
