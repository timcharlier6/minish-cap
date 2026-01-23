/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 20:04:50 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/23 17:16:24 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir_in(t_redir **infile, t_token *token_list, int n_of_redirs)
{
	if (n_of_redirs == 0)
	{
		*infile = ft_calloc(1, sizeof(t_redir));
		if (!*infile)
			return (0);
	}
	if (n_of_redirs > 0)
	{
		while (n_of_redirs-- > 0)
			(infile) = &(*infile)->next;
		*infile = ft_calloc(1, sizeof(t_redir));
		if (!*infile)
			return (0);
	}
	(*infile)->type = token_list->type;
	(*infile)->name = strdup_max(token_list->next->value, 0,
			ft_strlen(token_list->next->value));
	(*infile)->quotes = token_list->next->quotes;
	if (!((*infile)->name))
		return (0);
	token_list = token_list->next;
	if (!join_redir_adj(token_list->next, infile))
		return (0);
	return (1);
}

static int	is_redir_out(t_redir **outfile, t_token *token_list,
		int n_of_redirs)
{
	if (n_of_redirs == 0)
	{
		*outfile = ft_calloc(1, sizeof(t_redir));
		if (!*outfile)
			return (0);
	}
	if (n_of_redirs > 0)
	{
		while (n_of_redirs-- > 0)
		{
			(outfile) = &(*outfile)->next;
		}
		*outfile = ft_calloc(1, sizeof(t_redir));
		if (!*outfile)
			return (0);
	}
	(*outfile)->type = token_list->type;
	(*outfile)->name = strdup_max(token_list->next->value, 0,
			ft_strlen(token_list->next->value));
	if (!((*outfile)->name))
		return (0);
	token_list = token_list->next;
	if (!join_redir_adj(token_list->next, outfile))
		return (0);
	return (1);
}

static int	is_arg(t_cmd_table *t, t_token *list, int n_of_args, int n_array)
{
	if (n_of_args == 0)
	{
		t->args = ft_calloc(n_array + 1, sizeof(char *));
		if (!(t->args))
			return (0);
	}
	if (list->type == T_WORD)
	{
		t->args[n_of_args] = strdup_max(list->value, 0, ft_strlen(list->value));
		if (!t->args[n_of_args])
			return (0);
	}
	else if (list->type == T_WORD_ADJ)
	{
		while (list && list->type == T_WORD_ADJ)
		{
			t->args[n_of_args] = ft_strjoin_m(t->args[n_of_args], list->value);
			if (!t->args[n_of_args])
				return (0);
			list = list->next;
		}
	}
	return (1);
}

static int	fill_table(t_token **t_l, t_cmd_table *t, int *n_redirs, int n_args)
{
	while ((*t_l) && (*t_l)->type != T_PIPE)
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
			if (skip_void_arg(*&(t_l)))
				continue ;
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

t_cmd_table	*parsing(t_token *tlist, int n_cmd, int n_cmdcp, t_cmd_table *head)
{
	t_cmd_table	*command_table;
	static int	indexs[2];

	command_table = ft_calloc(1 + 1, sizeof(t_cmd_table));
	if (!command_table)
		return (0);
	head = command_table;
	while (--n_cmd > 0)
	{
		command_table->next = ft_calloc(1, sizeof(t_cmd_table));
		if (!command_table->next)
			return (0);
		command_table = command_table->next;
	}
	command_table = head;
	while (n_cmdcp > 0)
	{
		if (!(fill_table(&tlist, command_table, indexs, 0)))
			return (0);
		if (tlist)
			tlist = tlist->next;
		command_table = command_table->next;
		n_cmdcp--;
	}
	return (command_table = head);
}
