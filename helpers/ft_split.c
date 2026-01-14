/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:37:13 by ticharli          #+#    #+#             */
/*   Updated: 2026/01/14 15:12:50 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_wordcounter(const char *s, const char c);
static size_t	ft_strlen_split(const char *s, const char c);
static char		**ft_free_whole_tab(char **tab);

char	**ft_split(char *s, char c)
{
	char	**tab;
	char	**o_tab;
	size_t	wordcount;

	if (s == NULL)
		return (NULL);
	wordcount = ft_wordcounter(s, c);
	tab = ft_calloc(wordcount + 1, sizeof(char *));
	if (tab == NULL)
		return (NULL);
	o_tab = tab;
	while (wordcount-- != 0)
	{
		while (*s != '\0' && *s == c)
			++s;
		*tab = ft_substr(s, 0, ft_strlen_split(s, c));
		if (*tab == NULL)
			return (ft_free_whole_tab(o_tab));
		s += ft_strlen_split(s, c);
		++tab;
	}
	return (o_tab);
}

static size_t	ft_wordcounter(const char *s, const char c)
{
	size_t	wordcount;

	wordcount = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			++wordcount;
			while (*s != c && *s != '\0')
				++s;
		}
		else
			++s;
	}
	return (wordcount);
}

static size_t	ft_strlen_split(const char *s, const char c)
{
	const char	*ptr;

	ptr = s;
	while (*ptr != '\0' && *ptr != c)
		++ptr;
	return ((size_t)(ptr - s));
}

static char	**ft_free_whole_tab(char **tab)
{
	char	**ptr;

	ptr = tab;
	while (*tab != NULL)
		free(*tab++);
	free(ptr);
	return (NULL);
}
