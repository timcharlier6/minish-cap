/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:28:18 by ticharli          #+#    #+#             */
/*   Updated: 2026/01/20 15:27:34 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_env(t_env *my_env)
{
	t_env	*temp;

	temp = my_env;
	while (temp)
	{
		if (temp->value)
			printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
	return (0);
}
