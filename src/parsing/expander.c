/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:14:59 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/12 16:53:06 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int fill_list(t_sub_tok *sub_tok, t_token *t_list)
// {
// 	char *t_list_value_temp;

// 	t_list_value_temp = NULL;
// 	if (t_list->value)
// 		free(t_list->value);
// 	t_list->value = NULL;
// 	while (sub_tok)
// 	{
// 		t_list_value_temp = t_list value
// 		if (!(t_list->value = 
// 			ft_strjoin(t_list->value, sub_tok->value)))
// 				return (0);
// 		sub_tok = sub_tok->next;
// 	}
// 	return (1);
// }

static int fill_list(t_sub_tok *sub_tok, t_token *t_list)
{
	char *t_list_value_temp;

	t_list_value_temp = NULL;
	if (t_list->value)
		free(t_list->value);
	t_list->value = NULL;
	while (sub_tok)
	{
		if (!(t_list_value_temp = 
			ft_strjoin(t_list->value, sub_tok->value)))
				return (0);
		free(t_list->value);
		t_list->value = t_list_value_temp;
		sub_tok = sub_tok->next;
	}
	return (1);
}

t_token *expander(t_token *t_list, t_env *env, t_token *head, int *c_stat)
{
	t_sub_tok 		*sub_tok;
	t_sub_tok 		*sub_token_head;
	
	sub_tok = NULL;
	while(t_list)
	{
		if (t_list->quotes != QUOTE_SINGLE)
		{
			if (!(sub_tok = init_sub_tok(t_list->value, sub_tok, env, *c_stat)))
					return (0);
			sub_token_head = sub_tok;
			if (!(fill_list(sub_tok, t_list)))
				return (free_subt_list(&sub_tok), NULL);
			free_subt_list(&sub_token_head);
		}
		t_list = t_list->next;
	}
	c_stat = 0;
	return (t_list = head);
}
