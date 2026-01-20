/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_redir_adj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:18:12 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/20 18:01:02 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	join_redir_adj(t_token *token_list, t_redir **in_out)
{
	if (!token_list || token_list->type != T_WORD_ADJ)
		return (1);
	while (token_list && token_list->type == T_WORD_ADJ)
	{
		(*in_out)->name = ft_strjoin_m((*in_out)->name, token_list->value);
		if (!(*in_out)->name)
			return (0);
		token_list = token_list->next;
	}
	return (1);
}
