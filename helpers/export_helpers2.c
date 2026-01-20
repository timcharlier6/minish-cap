/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:59:30 by ticharli          #+#    #+#             */
/*   Updated: 2026/01/20 13:00:04 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_sorted_env(t_env *my_env)
{
	char	**sorted_env;
	int		count;
	int		i;
	t_env	*temp;

	temp = my_env;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	sorted_env = create_sorted_env_array(my_env, count);
	if (!sorted_env)
		return (1);
	i = -1;
	while (++i < count)
	{
		printf("%s\n", sorted_env[i]);
		free(sorted_env[i]);
	}
	free(sorted_env);
	return (0);
}

void	extract_key_value(char *arg, char **key, char **value, int *eq_pos)
{
	*eq_pos = ft_strchr(arg, '=');
	if (*eq_pos != -1)
	{
		*key = strdup_max(arg, 0, *eq_pos);
		*value = ft_strdup(arg + *eq_pos + 1);
	}
	else
	{
		*key = ft_strdup(arg);
		*value = NULL;
	}
}

int	update_existing_env(t_env *temp, char *key, char *value, int eq_pos)
{
	if (!ft_strcmp(temp->key, key))
	{
		free(key);
		if (eq_pos != -1)
		{
			if (temp->value)
				free(temp->value);
			temp->value = value;
		}
		else if (value)
			free(value);
		return (1);
	}
	return (0);
}

int	is_valid_env_var_key(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !arg[0])
		return (0);
	if (!((arg[i] >= 'A' && arg[i] <= 'Z') || (arg[i] >= 'a' && arg[i] <= 'z')
			|| arg[i] == '_'))
		return (0);
	i++;
	while (arg[i] && arg[i] != '=')
	{
		if (!((arg[i] >= 'A' && arg[i] <= 'Z') || (arg[i] >= 'a'
					&& arg[i] <= 'z') || (arg[i] >= '0' && arg[i] <= '9')
				|| arg[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
