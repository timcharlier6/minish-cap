/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 19:48:34 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/15 17:42:54 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(char **args, t_main *m)
{
	ft_putendl_fd("exit", 2);
	if (!args[1])
	{
		clean_up(m, 1, 1);
		exit(m->last_status);
	}
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		m->last_status = 1;
		return (0);
	}
	if (!(ft_isdigit_m(ft_atoi(args[1]))))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		clean_up(m, 1, 1);
		exit(2);
	}
	clean_up(m, 1, 1);
	exit(ft_atoi(args[1]));
	return (0);
}
