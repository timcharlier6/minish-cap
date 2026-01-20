/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:27:43 by ticharli          #+#    #+#             */
/*   Updated: 2026/01/20 12:50:17 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(t_cmd_table *cmd, t_env *my_env)
{
	char	*path;
	char	old[PATH_MAX];

	old[0] = '\0';
	getcwd(old, sizeof(old));
	if (cmd->args[1] && cmd->args[1][0] == '\0')
		return (ft_putendl_fd("", 1), 0);
	path = get_target(cmd, my_env);
	if (!path)
		return (1);
	if (chdir(path))
		return (cd_error(path), 1);
	return (update_pwds(my_env, old, path));
}
