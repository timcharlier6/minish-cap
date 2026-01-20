/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inc_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:53:14 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/20 17:55:16 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	inc_shlvl(t_env *env)
{
	int	result;
	int	new_value;

	result = 0;
	new_value = 0;
	while (env && (ft_strncmp(env->key, "SHLVL", 5) != 0))
		env = env->next;
	result = ft_atoi(env->value);
	free(env->value);
	if (result == 0)
		new_value = 1;
	else if (result < 0)
		new_value = 0;
	else
		new_value = result + 1;
	if (result >= 1000)
		new_value = 1;
	env->value = ft_itoa(new_value);
	if (!env->value)
		return (0);
	return (1);
}
