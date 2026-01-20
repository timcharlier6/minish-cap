/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_to_zero.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:04:50 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/20 12:22:22 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_to_zero(int count, ...)
{
	va_list	args;
	void	**ptr;

	va_start(args, count);
	while (count > 0)
	{
		ptr = va_arg(args, void **);
		if (ptr)
			*ptr = NULL;
		count--;
	}
	va_end(args);
}
