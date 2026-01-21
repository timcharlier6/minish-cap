/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:16:06 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/21 14:37:56 by ticharli         ###   ########.fr       */
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

// returns 'n' of elements, or 0 if not found
int	char_search_n(char *s, char c)
{
	int	i;
	int	y;
	int	count;

	i = 0;
	y = 0;
	count = 0;
	y = ft_strlen(s);
	while ((s[i]) && i < y)
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
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
