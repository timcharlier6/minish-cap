/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_to_zero.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:04:50 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/06 15:08:02 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdarg.h>
#include <stdlib.h>

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