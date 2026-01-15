/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_list_to_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 18:29:05 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/14 19:21:37 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *assemble(t_env *env, char *env_line)
{
	char *temp;

	temp = NULL;
	env_line = ft_strjoin(env->key, "=");
	if (!env_line)
		return (NULL);
	temp = env_line;
	env_line = ft_strjoin(env_line, env->value);
	if (!env_line)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (env_line);
}

char **copy_list_to_array(t_env *env)
{
	char 	**env_copy;
	t_env 	*head;
	int 	i;

	head = env;
	i = 0;
	while(env)
	{
		i++;
		env = env->next;
	}
	env = head;
	env_copy = calloc((i + 1), sizeof(char *));
	if (!env_copy)
		return (NULL);
	i = 0;
	while(env)
	{
		env_copy[i] = assemble(env, env_copy[i]);
		if (!env_copy[i])
			return (free_array(env_copy), NULL);
		i++;
		env = env->next;
	}
	return (env_copy);
}
