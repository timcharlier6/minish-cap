/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:16:06 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/06 15:47:56 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns len before c, or 0 if not found. starts from start.
// arg3: 1 = warning message on / arg 4: 1 = exit on.
int	char_search_len(const char *s, const char c, int start, int warning_on)
{
	int	i;

	i = 0;
	if (!s && warning_on == 1)
		printf("Parsing Error : char searching function ->empty string.\n");
	if (!s && warning_on == 0)
		return(0);
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
		return(0);
	while (s[start + i])
	{
		if (s[start + i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

//returns 'n' of elements, or 0 if not found
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
