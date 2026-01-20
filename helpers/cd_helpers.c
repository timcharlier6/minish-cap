/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:49:44 by ticharli          #+#    #+#             */
/*   Updated: 2026/01/20 12:49:56 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_error(const char *arg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd((char *)arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

char	*get_env_val(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	update_env(t_env *env, char *key, char *value)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
}

char	*get_target(t_cmd_table *cmd, t_env *env)
{
	char	*path;

	if (!cmd->args[1] || !ft_strcmp(cmd->args[1], "--"))
	{
		path = get_env_val(env, "HOME");
		if (!path)
			ft_putendl_fd("minishell: cd: HOME not set", 2);
	}
	else if (!ft_strcmp(cmd->args[1], "-"))
	{
		path = get_env_val(env, "OLDPWD");
		if (!path)
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		else
			printf("%s\n", path);
	}
	else
		path = cmd->args[1];
	return (path);
}

int	update_pwds(t_env *env, char *old, char *path)
{
	char	new[PATH_MAX];

	if (old && *old)
		update_env(env, "OLDPWD", old);
	if (getcwd(new, sizeof(new)))
		update_env(env, "PWD", new);
	else
		update_env(env, "PWD", path);
	return (0);
}
