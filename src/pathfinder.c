/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:50:43 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/14 17:25:48 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *find_path_var(t_env *env)
{
	char *env_path_line;

	env_path_line = 0;
	while(env && env_path_line == 0)
	{
		if (ft_strncmp_m(env->key, "PATH=", 5) == 0)
		{
			env_path_line = ft_strdup(env->value);
			if (!env_path_line)
				return (0);
		}
		env = env->next;
	}
	if (env_path_line == 0)
		return (0);
	return (env_path_line);
}

int	command_path_finder(t_main *m, t_env *env)
{
	char *path;

	(void)m;
	path = find_path_var(env);
	printf("Path de ls: %s\n", path);
	if (path == 0)
		return (0);
	return (1);
} 