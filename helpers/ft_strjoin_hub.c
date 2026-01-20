/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_hub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:14:45 by ticharli          #+#    #+#             */
/*   Updated: 2026/01/20 12:17:05 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s;
	size_t	len;
	int		i;

	s = NULL;
	len = ft_strlen(s1) + ft_strlen(s2);
	s = ft_calloc(len + 1, sizeof(char));
	if (!s)
		return (NULL);
	len = 0;
	while (s1 && s1[len])
	{
		s[len] = s1[len];
		len++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		s[len + i] = s2[i];
		i++;
	}
	return (s);
}

char	*ft_strjoin_len(char *s1, char *s2, int len)
{
	char	*s;
	int		i;
	int		y;

	s = NULL;
	i = 0;
	s = ft_calloc(len + 1, sizeof(char));
	if (!s)
		return (NULL);
	while (s1 && s1[i] && i < len)
	{
		s[i] = s1[i];
		i++;
	}
	y = 0;
	while (s2 && s2[y] && i < len)
	{
		s[i] = s2[y];
		i++;
		y++;
	}
	return (s);
}

char	*ft_strjoin_m(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;
	int		s1_len;

	s1_len = 0;
	if (s1)
		s1_len = ft_strlen(s1);
	new = malloc(s1_len + ft_strlen(s2) + 1);
	if (!new)
		return (free(s1), NULL);
	i = 0;
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	return (free(s1), new);
}
