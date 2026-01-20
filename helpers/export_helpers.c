/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:59:21 by ticharli          #+#    #+#             */
/*   Updated: 2026/01/20 13:01:26 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_strings(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static int	partition(char **env, int low, int high)
{
	char	*pivot;
	int		i;
	int		j;

	pivot = env[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (ft_strcmp(env[j], pivot) < 0)
		{
			i++;
			swap_strings(&env[i], &env[j]);
		}
		j++;
	}
	swap_strings(&env[i + 1], &env[high]);
	return (i + 1);
}

void	quicksort(char **env, int low, int high)
{
	int	pivot;

	if (low < high)
	{
		pivot = partition(env, low, high);
		quicksort(env, low, pivot - 1);
		quicksort(env, pivot + 1, high);
	}
}

char	**create_sorted_env_array(t_env *my_env, int count)
{
	char	**sorted_env;
	int		i;
	t_env	*temp;

	sorted_env = ft_calloc(count + 1, sizeof(char *));
	if (!sorted_env)
		return (NULL);
	i = 0;
	temp = my_env;
	while (temp)
	{
		sorted_env[i] = format_env_var(temp);
		temp = temp->next;
		i++;
	}
	quicksort(sorted_env, 0, count - 1);
	return (sorted_env);
}

char	*format_env_var(t_env *env)
{
	char	*str;

	str = ft_strjoin("export ", env->key);
	str = ft_strjoin_m(str, "=\"");
	if (env->value)
		str = ft_strjoin_m(str, env->value);
	str = ft_strjoin_m(str, "\"");
	return (str);
}
