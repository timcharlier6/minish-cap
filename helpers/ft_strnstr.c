/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:39:11 by ticharli          #+#    #+#             */
/*   Updated: 2026/01/14 15:11:49 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	if (len == 0 || ft_strlen(haystack) < (int)needle_len)
		return (NULL);
	while (*haystack != '\0' && len >= needle_len)
	{
		if (ft_memcmp(haystack, needle, needle_len) == 0)
			return ((char *)haystack);
		++haystack;
		--len;
	}
	return (NULL);
}
