/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:28:31 by ticharli          #+#    #+#             */
/*   Updated: 2026/01/20 16:51:47 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_new_env(t_env *last, char *key, char *value)
{
	t_env	*new_node;

	if (!last)
		return (1);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		free(key);
		if (value)
			free(value);
		return (1);
	}
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	if (last)
		last->next = new_node;
	return (0);
}

static int	process_export(char *arg, t_env *my_env)
{
	char	*key;
	char	*value;
	int		eq_pos;
	t_env	*temp;

	extract_key_value(arg, &key, &value, &eq_pos);
	temp = my_env;
	while (temp)
	{
		if (update_existing_env(temp, key, value, eq_pos))
			return (0);
		if (!temp->next)
			break ;
		temp = temp->next;
	}
	return (add_new_env(temp, key, value));
}

static int	validate_export_args(char **args, int start_index)
{
	int	i;

	i = start_index;
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]))
		{
			printf("export: `%s': not a valid identifier\n", args[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	execute_export_args(char **args, int start_index, t_env *my_env)
{
	int	i;

	i = start_index;
	while (args[i])
	{
		if (process_export(args[i], my_env) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	export(t_cmd_table *cmd, t_env *my_env)
{
	int	count;
	int	i;

	count = 0;
	while (cmd->args[count])
		count++;
	if (!ft_strcmp(cmd->args[count - 1], "export"))
		return (print_sorted_env(my_env));
	i = 0;
	while (i < count && ft_strcmp(cmd->args[i], "export"))
		i++;
	i++;
	if (validate_export_args(cmd->args, i))
		return (1);
	return (execute_export_args(cmd->args, i, my_env));
}
