/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 20:04:50 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/20 15:56:02 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//il faut encore gerer le cas ou le infile/outfile suivant c est des ADJ...car la value recue ici ds ce cas sera seulement le premier adj...
static int is_redir_in(t_redir **infile, t_token *token_list, int n_of_redirs)
{
	t_redir 					**head;

	if (n_of_redirs == 0)
	{
		if (!((*infile) = ft_calloc(1, sizeof(t_redir))))
			return (0);
	}
	head = infile;
	if (n_of_redirs > 0)
	{
		while (n_of_redirs-- > 0)
		{
			(infile) = &(*infile)->next;
		}
		if (!((*infile) = ft_calloc(1, sizeof(t_redir))))
			return (0);
	}
	(*infile)->type = token_list->type;
	(*infile)->name = strdup_max(token_list->next->value, 0, 
		ft_strlen(token_list->next->value));
	(*infile)->quotes = token_list->next->quotes;
	if(!((*infile)->name))			
		return (0);
	infile = head;
	return (1);
}

static int is_redir_out(t_redir **outfile, t_token *token_list, int n_of_redirs)
{
	t_redir 					**head;

	if (n_of_redirs == 0)
	{
		if (!((*outfile) = ft_calloc(1, sizeof(t_redir))))
			return (0);
	}
	head = outfile;
	if (n_of_redirs > 0)
	{
		while (n_of_redirs-- > 0)
		{
			(outfile) = &(*outfile)->next;
		}
		if (!((*outfile) = ft_calloc(1, sizeof(t_redir))))
			return (0);
	}
	(*outfile)->type = token_list->type;
	(*outfile)->name = strdup_max(token_list->next->value, 0, 
		ft_strlen(token_list->next->value));
	if(!((*outfile)->name))			
		return (0);
	outfile = head;
	return (1);
}

static int is_arg(t_cmd_table *t, t_token *list, int n_of_args, int n_for_array)
{
	if (n_of_args == 0)
	{
		t->args = ft_calloc(n_for_array + 1, sizeof(char *));
		if (!(t->args))
			return(0);
	}
	if (list->type == T_WORD)
	{
		if (!(t->args[n_of_args] = 
		strdup_max(list->value, 0, ft_strlen(list->value))))
				return (0);
	}
	else if (list->type == T_WORD_ADJ)
	{
		while (list && list->type == T_WORD_ADJ)
		{
			if (!(t->args[n_of_args] = 
				ft_strjoin_m(t->args[n_of_args], list->value)))
				return (0);
			list = list->next;	
		}
	}
	return (1);
}

//table's been allocated, let's fill every cmd on the table with allocs and data
static int	fill_table(t_token **t_l, t_cmd_table *t, int *n_redirs, int n_args)
{
	while((*t_l) && (*t_l)->type != T_PIPE)
	{
		if ((*t_l)->type == T_REDIR_IN || (*t_l)->type == T_HEREDOC)
		{
			if (!(is_redir_in(&t->infile, *t_l, n_redirs[0]++)))
				return (0);
		}
		else if ((*t_l)->type == T_REDIR_OUT || (*t_l)->type == T_REDIR_APPEND)
		{
			if (!(is_redir_out(&t->outfile, *t_l, n_redirs[1]++)))
				return (0);
		}
		else if ((*t_l)->type == T_WORD || (*t_l)->type == T_WORD_ADJ)
		{
			if (!(is_arg(t, *t_l, n_args++, token_word_be_arg_count((*t_l)))))
				return (0);
		}
		if ((*t_l)->type != T_WORD)
			(*t_l) = skip_word_or_adjacents(*t_l, 1);
		else
			(*t_l) = (*t_l)->next;
	}
	return (n_redirs[0] = 0, n_redirs[1] = 0, 1);
}

//devrais je creer un head de la stlist pour pouvoir 
// la free, ou est ce ici une copie?
t_cmd_table *parsing(t_token *s_tlist, int number_of_cmds, int number_of_cmds2)
{
	t_cmd_table	*command_table;
	t_cmd_table	*head;
	static int	indexs[2];
	
	if(!(command_table = ft_calloc(1 + 1, sizeof(t_cmd_table))))
			return (0);
	head = command_table;
	while(--number_of_cmds > 0)
	{
		if(!(command_table->next = ft_calloc(1, sizeof(t_cmd_table))))
			return (0);
		command_table = command_table->next;
	}
	command_table = head;
	while(number_of_cmds2 > 0) // defilement des '|'
	{
		if (!(fill_table(&s_tlist, command_table, indexs, 0)))
			return (0);
		if (s_tlist) // passer le '|' 
			s_tlist = s_tlist->next;
		command_table = command_table->next;
		number_of_cmds2--;
	}
	command_table = head;
	return (command_table);
}
