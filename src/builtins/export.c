#include "minishell.h"

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

static void	quicksort(char **env, int low, int high)
{
	int	pivot;

	if (low < high)
	{
		pivot = partition(env, low, high);
		quicksort(env, low, pivot - 1);
		quicksort(env, pivot + 1, high);
	}
}

static char	*format_env_var(t_env *env)
{
	char	*str;

	str = ft_strjoin("export ", env->key);
	str = ft_strjoin_m(str, "=\"");
	if (env->value)
		str = ft_strjoin_m(str, env->value);
	str = ft_strjoin_m(str, "\"");
	return (str);
}

static char	**create_sorted_env_array(t_env *my_env, int count)
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

static int	print_sorted_env(t_env *my_env)
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

static void	extract_key_value(char *arg, char **key, char **value, int *eq_pos)
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

static int	update_existing_env(t_env *temp, char *key, char *value, int eq_pos)
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

static int	add_new_env(t_env *last, char *key, char *value)
{
	t_env	*new_node;

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
	else
		free(new_node);
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
			break;
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