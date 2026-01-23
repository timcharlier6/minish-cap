/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:07:19 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/23 19:46:29 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_to_zero(int *i, int *y, t_sub **a, t_sub **b)
{
	*i = 0;
	*y = 0;
	*a = NULL;
	*b = NULL;
}

int	init_main(t_main **main, int *ac, char ***av)
{
	(void)ac;
	(void)av;
	signal_init();
	(*main) = ft_calloc(1, sizeof(t_main));
	if (!(*main))
		return (0);
	(*main)->last_status = 0;
	return (1);
}

static int	init_envp(char ***envp)
{
	char	buf[PATH_MAX];
	char	*cwd;

	cwd = getcwd(buf, PATH_MAX);
	if (!cwd)
		return (0);
	*envp = ft_calloc(4, sizeof(char *));
	if (!*envp)
		return (0);
	(*envp)[0] = ft_strjoin("PWD=", cwd);
	(*envp)[1] = ft_strdup("SHLVL=1");
	(*envp)[2] = ft_strdup("_=/usr/bin/env");
	(*envp)[3] = NULL;
	return (1);
}

static int	process_env_string(t_env **env_list, char *env_str)
{
	t_env	*new_node;
	int		split_pos;

	split_pos = (char_search_len(env_str, '=', 0, 0) - 1);
	if (split_pos == -1)
		return (1);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (0);
	new_node->key = strdup_max(env_str, 0, split_pos);
	new_node->value = ft_strdup(env_str + split_pos + 1);
	if (!new_node->key || !new_node->value)
	{
		free_ptr(new_node->key);
		free_ptr(new_node->value);
		free(new_node);
		return (0);
	}
	new_node->next = *env_list;
	*env_list = new_node;
	return (1);
}

int	init_env_list(t_env **env_list, char **envp)
{
	int	i;
	int	free_env;
	int	status;

	i = -1;
	free_env = 0;
	status = 1;
	*env_list = NULL;
	if (!envp || !*envp)
	{
		if (!init_envp(&envp))
			return (0);
		free_env = 1;
	}
	while (status && envp[++i])
		status = process_env_string(env_list, envp[i]);
	if (!status)
		free_env_list(env_list);
	if (free_env)
		free_array(envp);
	if (!status)
		return (status);
	return (inc_shlvl(*env_list));
}
