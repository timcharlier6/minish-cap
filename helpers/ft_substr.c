/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:39:38 by ticharli          #+#    #+#             */
/*   Updated: 2026/01/14 15:13:44 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	else if (s_len - start < len)
		len = s_len - start;
	ptr = ft_calloc(len + 1, sizeof(*ptr));
	if (ptr != NULL)
		ft_strncpy(ptr, s + start, len + 1);
	return (ptr);
}
