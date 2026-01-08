/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 22:40:28 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/08 13:25:22 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exit_w_message(void)
{
		printf("exit\n");
		exit(1);
}

int clean_all_quotes(t_token *list)
{
	t_token *tmp;
	char    *new_val;

	tmp = list;
	while (tmp)
    {
		if ((tmp->type == T_WORD || tmp->type == T_WORD_ADJ) && tmp->quotes != 0)
		{
			new_val = strdup_max(tmp->value, 1, ft_strlen(tmp->value) - 2);
			if (!new_val)
				return (0); // Échec malloc
			free(tmp->value);
			tmp->value = new_val;
		}
		tmp = tmp->next;
	}
	return (1);
}

void	free_temp(char **exp, char **whole, char **before_d, char **both)
{
	if (*before_d && before_d)
	{
		free(*before_d);
		*before_d = NULL;
	}
	if (*exp && exp)
	{
		free(*exp);
		*exp = NULL;
	}
	if (*both && both)
	{
		free(*both);
		*both = NULL;
	}
	if (*whole && whole)
	{
		free(*whole);
		*whole = NULL;
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
