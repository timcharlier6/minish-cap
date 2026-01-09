/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:39:25 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/08 20:38:52 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec(t_mothership *m)
{
	if (ft_strncmp(m->s_cmd_table->args[0], "echo", 4) == 0)
		my_echo(m->s_cmd_table);
	if (ft_strncmp(m->s_cmd_table->args[0], "pwd", 3) == 0)	
		pwd();
	return(0);
}