/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 20:08:51 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/20 12:24:50 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	string_check(const char *str, size_t i)
{
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	while (str[i] == '-' || str[i] == '+')
		i++;
	if ((((i > 0) && (str[i - 1] == '+')) || ((i > 0) && (str[i - 1] == '-')))
		&& (((i > 1) && (str[i - 2] == '-')) || ((i > 1) && (str[i
						- 2] == '+'))))
		return (0);
	return (i);
}

long int	ft_atoi(const char *nptr)
{
	unsigned long	buff;
	unsigned long	v;
	size_t			i;
	int				sign;

	i = 0;
	v = 0;
	buff = 0;
	sign = 1;
	i = string_check(nptr, i);
	if (i > 0 && nptr[i - 1] == '-')
		sign = -1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		v *= 10;
		v += nptr[i] - '0';
		if (buff > v && sign > 0)
			return (-1);
		else if (buff > v && sign < 0)
			return (0);
		buff = v;
		nptr++;
	}
	return (sign * v);
}
