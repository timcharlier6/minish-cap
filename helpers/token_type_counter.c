/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_counter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 17:22:54 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/23 17:17:41 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_word_be_arg_count(t_token *token_list)
{
	int	count;

	count = 0;
	while (token_list && token_list->type != T_PIPE)
	{
		if (token_list->type == T_WORD)
		{
			if (skip_void_arg(&token_list))
				continue ;
			count++;
			token_list = token_list->next;
		}
		else if (token_list->type == T_PIPE)
			return (count);
		else if (token_list->type == T_WORD_ADJ)
		{
			if (skip_void_arg(&token_list))
				continue ;
			token_list = skip_word_or_adjacents(token_list, 0);
			count++;
		}
		else
			token_list = skip_word_or_adjacents(token_list, 1);
	}
	return (count);
}

// enter the type you want to count as 2nd argument &&|| 3rd arg.
int	redir_token_count(t_token *t_l, t_tok_type typ1, t_tok_type typ2)
{
	int	count;

	count = 0;
	while (t_l)
	{
		if (t_l->type == typ1 || t_l->type == typ2)
		{
			count++;
		}
		t_l = t_l->next;
		if (!t_l)
			break ;
		if (t_l->type == T_PIPE)
			break ;
	}
	return (count);
}
