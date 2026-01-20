/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_word_or_adjacents.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:21:09 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/20 12:23:54 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// (arg2)skip_current = 1 to skip current pointed element ( <, > etc)
t_token	*skip_word_or_adjacents(t_token *list, int skip_current)
{
	if (skip_current == 1)
		list = list->next;
	if (list->type == T_WORD)
		list = list->next;
	else if (list->type == T_WORD_ADJ)
	{
		while (list && list->type == T_WORD_ADJ)
			list = list->next;
	}
	return (list);
}
