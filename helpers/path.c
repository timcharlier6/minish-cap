/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:21:08 by ticharli          #+#    #+#             */
/*   Updated: 2026/01/20 12:21:32 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**find_paths(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

static char	*build_path(char *dir, char *cmd)
{
	char	*part;
	char	*full;

	part = ft_strjoin(dir, "/");
	if (!part)
		return (NULL);
	full = ft_strjoin(part, cmd);
	free(part);
	return (full);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*path;
	int		i;

	i = 0;
	while (paths[i])
	{
		path = build_path(paths[i], cmd);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;

	paths = find_paths(envp);
	if (!paths)
		return (NULL);
	path = search_in_paths(paths, cmd);
	free_array(paths);
	return (path);
}
