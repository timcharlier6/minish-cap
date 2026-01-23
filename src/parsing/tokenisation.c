/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:52:58 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/23 15:34:52 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

static int	add_token(t_token **lst, t_tok_type type, char *s, t_quote_type q)
{
	int		inc;
	t_token	*new;
	t_token	**temp;

	if (!s)
		return (free_token_list(lst), 0);
	if ((*lst)->type == T_REDIR_APPEND || (*lst)->type == T_HEREDOC)
		inc = 2;
	else if ((*lst)->type == T_WORD || (*lst)->type == T_WORD_ADJ)
		inc = ft_strlen(s);
	else
		inc = 1;
	new = malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->type = type;
	new->value = s;
	new->next = NULL;
	new->quotes = q;
	if ((*lst)->value == NULL)
		return (free_token_list(lst), *lst = new, inc);
	temp = lst;
	while ((*temp)->next)
		temp = &(*temp)->next;
	return ((*temp)->next = new, inc);
}

int	token_is_word(t_token **tlist, char *s, int start, int quote_type)
{
	int	len;

	len = 0;
	if (s[start] == '\'')
	{
		len = char_search_len(s, '\'', start, 1);
		quote_type = 1;
	}
	else if (s[start] == '\"')
	{
		len = char_search_len(s, '\"', start, 1);
		quote_type = 2;
	}
	else
		len = (str_is_char(s, start));
	if (s[start + len] > 32
		&& s[start + len] != '|'
		&& s[start + len] != '<'
		&& s[start + len] != '>')
		add_token(tlist, T_WORD_ADJ, strdup_max(s, start, len), quote_type);
	else if (start > 0 && s[start - 1] && s[start - 1] > 32)
		add_token(tlist, T_WORD_ADJ, strdup_max(s, start, len), quote_type);
	else
		add_token(tlist, T_WORD, strdup_max(s, start, len), quote_type);
	return (start + len);
}

//ADJ = 1 argument, multiple token definitions.
t_token	*tokenisation(char *input, t_token *tlist, int i)
{
	tlist = ft_calloc(1, sizeof(*tlist));
	if (!(tlist))
		return (0);
	while (input[i])
	{
		i += str_has_space(input, i);
		if (input[i] == '\0')
			break ;
		if (input[i] == '|')
			i += add_token(&(tlist), T_PIPE, strdup_max("|", 0, 1), 0);
		else if (input[i + 1] && (input[i] == '>' && input[i + 1] == '>'))
			i += add_token(&(tlist), T_REDIR_APPEND, strdup_max(">>", 0, 2), 0);
		else if (input[i + 1] && (input[i] == '<' && input[i + 1] == '<'))
			i += add_token(&(tlist), T_HEREDOC, strdup_max("<<", 0, 2), 0);
		else if (input[i] == '>')
			i += add_token(&(tlist), T_REDIR_OUT, strdup_max(">", 0, 1), 0);
		else if (input[i] == '<')
			i += add_token(&(tlist), T_REDIR_IN, strdup_max("<", 0, 1), 0);
		else
			i = token_is_word(&(tlist), input, i, 0);
		if (!(tlist))
			return (0);
	}
	return ((tlist));
}
