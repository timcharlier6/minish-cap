/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 22:40:28 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/06 13:51:34 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exit_w_message(void)
{
		printf("exit\n");
		exit(1);
}

void free_token_list(t_token **s_list)
{
	t_token *temp;

	temp = 0;
    if (!s_list || !*s_list)
		return ;
	while(*s_list)
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

void free_redir_list(t_redir **s_list)
{
	t_redir *temp;

	temp = 0;
    if (!s_list || !*s_list)
		return ;
	while(*s_list)
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

static void free_env_list(t_env **env)
{
	t_env *temp;

	temp = 0;
    if (!env|| !*env)
		return ;
	while(*env)
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

static void free_array(char **array)
{
	int i;

	i = 0;
	if (!array)
		return ;
	while(array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

// arg2 : 1 = free mothership's shell // arg3 : 1 = free environnement list 
void clean_up(t_mothership *m, int free_m_shell, int free_env)
{
    t_cmd_table *temp;
    
	if (!m) // Protection indispensable
		return ;
	if (m->token_list)
		free_token_list(&m->token_list);
	if (m->env && free_env == 1)
		free_env_list(&m->env);
	while (m->s_cmd_table)
	{
		if (m->s_cmd_table->args)
			free_array(m->s_cmd_table->args);
		if (m->s_cmd_table->infile)
			free_redir_list(&m->s_cmd_table->infile);
		if (m->s_cmd_table->outfile)
			free_redir_list(&m->s_cmd_table->outfile);
		temp = m->s_cmd_table;
		m->s_cmd_table = m->s_cmd_table->next;
		free(temp);
	}
	m->s_cmd_table = NULL;
	if (free_m_shell == 1)
		free(m);
}
