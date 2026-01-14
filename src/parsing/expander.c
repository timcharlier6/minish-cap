/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:14:59 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/13 11:53:31 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_list(t_sub *sub_tok, t_token *t_list)
{
	char	*t_list_value_temp;

	t_list_value_temp = NULL;
	if (t_list->value)
		free(t_list->value);
	t_list->value = NULL;
	while (sub_tok)
	{
		t_list_value_temp = ft_strjoin(t_list->value, sub_tok->value);
		if (!t_list_value_temp)
			return (0);
		free(t_list->value);
		t_list->value = t_list_value_temp;
		sub_tok = sub_tok->next;
	}
	return (1);
}

t_token	*expander(t_token *tlist, t_env *env, t_token *head, int *c_stat)
{
	t_sub	*sub_tok;
	t_sub	*sub_token_head;

	sub_tok = NULL;
	while (tlist)
	{
		if (tlist->quotes != QUOTE_SINGLE)
		{
			sub_tok = init_sub(tlist->value, sub_tok, env, *c_stat);
			if (!sub_tok)
				return (0);
			sub_token_head = sub_tok;
			if (!(fill_list(sub_tok, tlist)))
				return (free_subt_list(&sub_tok), NULL);
			free_subt_list(&sub_token_head);
		}
		tlist = tlist->next;
	}
	c_stat = 0;
	return (tlist = head);
}
