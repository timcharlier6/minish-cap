/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:39:25 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/12 17:59:58 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec(t_mothership *m)
{
	if (!m || !m->s_cmd_table || !m->s_cmd_table->args || !m->s_cmd_table->args[0])
		return (0);
	if (ft_strcmp(m->s_cmd_table->args[0], "echo") == 0)
		my_echo(m->s_cmd_table);
	if (ft_strcmp(m->s_cmd_table->args[0], "pwd") == 0)	
		pwd();
	if (ft_strcmp(m->s_cmd_table->args[0], "cd") == 0)	
		cd(m->s_cmd_table, m->env);
	if (ft_strcmp(m->s_cmd_table->args[0], "env") == 0)	
		my_env(m->env);
	if (ft_strcmp(m->s_cmd_table->args[0], "exit") == 0)
	{
		printf("exit\n");
		clean_up(m, 1, 1);
		exit(0);
	}
	return(0);
}
