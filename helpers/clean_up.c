/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 22:40:28 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/22 17:36:30 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_w_message(void)
{
	printf("exit\n");
	exit(1);
}

int	clean_all_quotes(t_token *list)
{
	t_token	*tmp;
	char	*new_val;

	tmp = list;
	while (tmp)
	{
		if ((tmp->type == T_WORD || tmp->type == T_WORD_ADJ)
			&& tmp->quotes != 0)
		{
			new_val = strdup_max(tmp->value, 1, ft_strlen(tmp->value) - 2);
			if (!new_val)
				return (0);
			free(tmp->value);
			tmp->value = new_val;
		}
		tmp = tmp->next;
	}
	return (1);
}

void	free_temp(char **a, char **b, char **c, char **d)
{
	if (*a && a)
	{
		free(*a);
		*a = NULL;
	}
	if (*b && b)
	{
		free(*b);
		*b = NULL;
	}
	if (*c && c)
	{
		free(*c);
		*c = NULL;
	}
	if (*d && d)
	{
		free(*d);
		*d = NULL;
	}
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

//arg2->free main's shell // arg3->free env list //arg4->exit
void	clean_up(t_main *m, int free_m_shell, int free_env, int exit_status)
{
	t_cmd_table	*temp;

	if (!m)
		return ;
	if (m->token_list)
		free_token_list(&m->token_list);
	if (m->env && free_env == 1)
		free_env_list(&m->env);
	while (m->cmd_table)
	{
		if (m->cmd_table->args)
			free_array(m->cmd_table->args);
		if (m->cmd_table->infile)
			free_redir_list(&m->cmd_table->infile);
		if (m->cmd_table->outfile)
			free_redir_list(&m->cmd_table->outfile);
		temp = m->cmd_table;
		m->cmd_table = m->cmd_table->next;
		free(temp);
	}
	m->cmd_table = NULL;
	if (free_m_shell == 1)
		free(m);
	if (exit_status != 0)
		exit (exit_status);
}
