/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:34:57 by ticharli          #+#    #+#             */
/*   Updated: 2026/01/13 18:28:27 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*cast_s1;
	const unsigned char	*cast_s2;

	cast_s1 = (const unsigned char *)s1;
	cast_s2 = (const unsigned char *)s2;
	while (n != 0 && *cast_s1 == *cast_s2)
	{
		--n;
		++cast_s1;
		++cast_s2;
	}
	if (n != 0)
		return (*cast_s1 - *cast_s2);
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int main ()
{
	char	data1[] = { 'a', 'b', 'd', '\0', 'd', 'e' };
	char	data2[] = { 'a', 'b', 'd', '\0', 'd', 'e' };
	int		result1;
	int		result2;

	result1 = ft_memcmp(data1, data2, 4);
	if (result1 == 0)
		printf(" ==  \n");
	else if (result1 < 0)
		printf(" < \n");
	else
		printf(" > \n");
	result2 = memcmp(data1, data2, 4);
	if (result2 == 0)
		printf(" ==  \n");
	else if (result2 < 0)
		printf(" < \n");
	else
		printf(" > \n");
	return (0);
}

*/