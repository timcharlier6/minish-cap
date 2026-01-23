/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:16:06 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/23 20:04:39 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns len before c, or 0 if not found. starts from start.
// w_on = warning message on
int	char_search_len(const char *s, const char c, int start, int w_on)
{
	int	i;

	i = 0;
	if (!s && w_on == 1)
		printf("Parsing Error : char searching function ->empty string.\n");
	if (!s && w_on == 0)
		return (0);
	while (s[start + i])
	{
		i++;
		if (s[start + i] == c)
			return (i + 1);
	}
	return (0);
}

int	char_search_len_0(const char *s, const char c, int start)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[start + i])
	{
		if (s[start + i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

int	check_unclosed_quotes(char *input)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (input[i] == '\"' && !single_quote)
			double_quote = !double_quote;
		i++;
	}
	return (single_quote || double_quote);
}

int	pipe_token_search(t_token *list)
{
	int	count;

	count = 0;
	while (list)
	{
		if (list->type == T_PIPE)
			count++;
		list = list->next;
	}
	return (count);
}

int	check_double_redirs(t_main *main, t_token *l)
{
	while (l)
	{
		if (l->type == T_REDIR_IN || l->type == T_REDIR_OUT
			|| l->type == T_REDIR_APPEND || l->type == T_HEREDOC)
		{
			if (l->next && (l->next->type != T_WORD
					&& l->next->type != T_WORD_ADJ))
			{
				double_redir_error(main, l->next->value);
				return (0);
			}
		}
		if (l->type == T_PIPE)
		{
			if (l->next && (l->next->type == T_PIPE))
			{
				double_redir_error(main, l->next->value);
				return (0);
			}
		}
		l = l->next;
	}
	return (1);
}
