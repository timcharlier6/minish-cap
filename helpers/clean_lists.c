/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 22:40:28 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/20 12:25:31 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token **s_list)
{
	t_token	*temp;

	temp = 0;
	if (!s_list || !*s_list)
		return ;
	while (*s_list)
	{
		temp = (*s_list)->next;
		if ((*s_list)->value)
		{
			free((*s_list)->value);
			(*s_list)->value = NULL;
		}
		free(*s_list);
		*s_list = NULL;
		*s_list = temp;
	}
}

void	free_redir_list(t_redir **s_list)
{
	t_redir	*temp;

	temp = 0;
	if (!s_list || !*s_list)
		return ;
	while (*s_list)
	{
		temp = (*s_list)->next;
		if ((*s_list)->name)
		{
			free((*s_list)->name);
			(*s_list)->name = NULL;
		}
		free(*s_list);
		*s_list = NULL;
		*s_list = temp;
	}
}

void	free_env_list(t_env **env)
{
	t_env	*temp;

	temp = 0;
	if (!env || !*env)
		return ;
	while (*env)
	{
		temp = (*env)->next;
		if ((*env)->key)
		{
			free((*env)->key);
			(*env)->key = NULL;
		}
		if ((*env)->value)
		{
			free((*env)->value);
			(*env)->value = NULL;
		}
		free(*env);
		*env = NULL;
		*env = temp;
	}
}

void	free_subt_list(t_sub **s_list)
{
	t_sub	*temp;

	temp = 0;
	if (!s_list || !*s_list)
		return ;
	while (*s_list)
	{
		temp = (*s_list)->next;
		if ((*s_list)->value)
		{
			free((*s_list)->value);
			(*s_list)->value = NULL;
		}
		free(*s_list);
		*s_list = NULL;
		*s_list = temp;
	}
}
