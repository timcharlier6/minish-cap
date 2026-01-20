/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncmp_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:45:58 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/20 12:18:39 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// S not NULL -> returns the number of valid env variable chars in input.
// C not NULL -> returns 1 if char is valid var char, else returns 0.
int	is_valid_var_char(const char *s, char c)
{
	int	count;

	count = 0;
	if (!s && !c)
		return (0);
	if (s)
	{
		while ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z')
			|| (*s >= '0' && *s <= '9') || *s == '_')
		{
			s++;
			count++;
		}
	}
	if (c)
	{
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
				&& c <= '9') || c == '_')
			return (1);
	}
	return (count);
}

int	is_not_sv_separator(const char *s, char c)
{
	int	count;

	count = 0;
	if (!s && !c)
		return (0);
	if (s)
	{
		while ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z')
			|| (*s >= '0' && *s <= '9') || *s == '_')
		{
			s++;
			count++;
		}
	}
	if (c)
	{
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
				&& c <= '9') || c == '_')
			return (1);
	}
	return (count);
}

// checks the validity of all chars after <s2 is key name>.
int	ft_strncmp_exp(const char *s1, const char *s2)
{
	int	len;

	len = is_valid_var_char(s1, 0);
	while ((*s1 || *s2) && len)
	{
		if (*s1 != *s2)
		{
			if (!*s2)
				return (-1);
			return (1);
		}
		s1++;
		s2++;
		len--;
	}
	if (s2 && is_valid_var_char(NULL, *s2))
		return (1);
	return (0);
}

// returns 0 if no difference is found
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && n--)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}

// runs the chain until difference is found. ret 0 if: no diff || n->end of s2).
int	ft_strncmp_m(char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned int	y;

	i = 0;
	y = 0;
	y += str_has_space(s1, 0);
	while (i < n)
	{
		if ((unsigned char)s1[y] != (unsigned char)s2[i])
			return ((unsigned char)s1[y] - (unsigned char)s2[i]);
		i++;
		y++;
		if (i == n)
			return (0);
	}
	return (1);
}
