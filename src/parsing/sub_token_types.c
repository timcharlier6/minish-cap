/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_token_types.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:38:28 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/23 15:37:42 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand(char *str, t_env *env, t_sub **sub_t)
{
	if (str[1])
		str++;
	while (env)
	{
		if (ft_strncmp_exp(str, env->key) == 0)
		{
			(*sub_t)->value = ft_strdup(env->value);
			if (!((*sub_t)->value))
				return (0);
		}
		else if ((ft_strncmp_exp(str, env->key)) == -1)
		{
			(*sub_t)->value = ft_strdup("");
			if (!((*sub_t)->value))
				return (0);
			return (-1);
		}
		env = env->next;
	}
	return (1);
}

int	is_var(char *str, t_sub *sub_t, t_env *env, int len)
{
	int	result;

	result = 0;
	result = expand(str, env, &sub_t);
	if (result == 0)
		return (0);
	else if (result == -1)
		sub_t->subtok_type = ST_UNVALID_VAR;
	else if (result == 1)
		sub_t->subtok_type = ST_VAR;
	return (len);
}

int	is_text(char *str, t_sub *sub_t, int len)
{
	sub_t->value = strdup_max(str, 0, len);
	if (!sub_t->value)
		return (0);
	sub_t->subtok_type = ST_TEXT;
	return (len);
}

int	is_status(t_sub *sub_t, int current_status)
{
	sub_t->value = ft_itoa(current_status);
	if (!sub_t->value)
		return (0);
	sub_t->subtok_type = ST_STATUS;
	return (2);
}
