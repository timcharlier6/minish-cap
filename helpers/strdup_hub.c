/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup_hub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:28:17 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/08 20:44:53 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// string to copy - start - len.
char	*strdup_max(const char *s, int start, int len)
{
	char	*new;
	int		i;

	new = NULL;
	i = 0;
	if (len < 0)
		return (NULL);
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	while (i < len)
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strdup(char *s)
{
	char	*stcopy;
	size_t	size;
	size_t	i;

	i = 0;
	stcopy = NULL;
	if (*s == '\0')
		size = 1;
	else
		size = ft_strlen(s) + 1;
	stcopy = (malloc(size));
	if (stcopy == NULL)
		return (0);
	while (s[i])
	{
		stcopy[i] = s[i];
		i++;
	}
	stcopy[i] = '\0';
	return (stcopy);
}
