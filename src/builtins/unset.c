/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:28:41 by ticharli          #+#    #+#             */
/*   Updated: 2026/01/20 12:29:36 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	rm_env_var(t_env **env, const char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	unset(t_cmd_table *cmd, t_env *env)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (!is_valid_env_var_key(cmd->args[i]))
		{
			printf("minishell: unset %s: not a valid identifier\n",
				cmd->args[i]);
			return (1);
		}
		rm_env_var(&env, cmd->args[i]);
		i++;
	}
	return (0);
}
