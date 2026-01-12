/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:39:25 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/12 22:35:34 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec(t_mothership *m)
{
	if (!m || !m->cmd_table || !m->cmd_table->args || !m->cmd_table->args[0])
		return (0);
	if (ft_strcmp(m->cmd_table->args[0], "echo") == 0)
		my_echo(m->cmd_table);
	if (ft_strcmp(m->cmd_table->args[0], "pwd") == 0)	
		pwd();
	if (ft_strcmp(m->cmd_table->args[0], "cd") == 0)	
		cd(m->cmd_table, m->env);
	if (ft_strcmp(m->cmd_table->args[0], "env") == 0)	
		my_env(m->env);
	if (ft_strcmp(m->cmd_table->args[0], "exit") == 0)
		builtin_exit(m->cmd_table->args, m);
	else
		m->last_status = 0;
	return(0);
}
