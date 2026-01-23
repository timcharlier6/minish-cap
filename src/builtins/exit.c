/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 19:48:34 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/22 17:36:09 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isnumber(char *s)
{
	if ((*s == '+' || *s == '-'))
		s++;
	while (s && *s)
	{
		if (!(*s >= '0' && *s <= '9'))
			return (0);
		s++;
	}
	return (1);
}

static int	normal_exit(t_main *m)
{
	int	status;

	status = m->last_status;
	clean_up(m, 1, 1, 0);
	rl_clear_history();
	exit(status);
}

int	builtin_exit(char **args, t_main *m)
{
	int	result;

	ft_putendl_fd("exit", 2);
	if (!args[1])
		normal_exit(m);
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	if (!ft_isnumber(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		clean_up(m, 1, 1, 0);
		rl_clear_history();
		exit(2);
	}
	result = ft_atoi(args[1]);
	clean_up(m, 1, 1, 0);
	rl_clear_history();
	exit(result % 256);
}
