/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space_related.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:35:43 by handler           #+#    #+#             */
/*   Updated: 2025/12/11 19:36:53 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_is_only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (ft_strlen(str) == i)
		return(1);
	return(0);
}

// returns 'i' after spaces. starts at 'int start'
int	str_has_space(char *str, int start)
{
	int i;

	i = 0;
	if (str[start])
	{
		while (str[start + i] && ((str[start + i] >= 9 
			&& str[start + i] <= 13) || str[start + i] == 32))
			i++;
	}
	return (i);
}

//returns len between first and last character beeing one without :
//  spaces  ||  single/double quotes 
int	str_is_char(char *str, int start)
{
	int i;

	i = 0;
	while (str[start + i] > 32 
		&& str[start + i] != 34 
			&& str[start + i] != 39)
		
			i++;
	return (i);
}