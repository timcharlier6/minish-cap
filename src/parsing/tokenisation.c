/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:52:58 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/12 16:37:23 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

static int add_token(t_token **s_tlist, t_token_type type, char *s, t_quote_type q)
{
	int 	inc;
	t_token *new;
	t_token	**temp;
	
	if (!s)
		return (free_token_list(s_tlist), 0);
	if ((*s_tlist)->type == T_REDIR_APPEND || (*s_tlist)->type == T_HEREDOC)
		inc = 2;
	else if ((*s_tlist)->type == T_WORD || (*s_tlist)->type == T_WORD_ADJ)
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
	if ((*s_tlist)->value == NULL) // c est toujours la tete qu on recoit ici
		return (free_token_list(s_tlist), *s_tlist = new, inc); //  OVERWRITE ICIIIIIIII ahaaaa faut pas oublier de freeeeeeee un des deux !!!
	temp = s_tlist;
	while((*temp)->next)
		temp = &(*temp)->next;
	return((*temp)->next = new, inc);
}

//returns: i = (starting point + found length)
//quotes check inside
int token_is_word(t_token **s_tlist, char *s, int start, int quote_type)
{
	int len;
	
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
	if (s[start + len] > 32 && 
			s[start + len] != '|' &&
				s[start + len] != '<' &&
					s[start + len] != '>') //end of WORD = other WORD (no space)
		add_token(s_tlist, T_WORD_ADJ, strdup_max(s, start, len), quote_type);	
	else if (start > 0 && s[start - 1] && s[start - 1] > 32) // beggining = other WORD (n/s)
		add_token(s_tlist, T_WORD_ADJ, strdup_max(s, start, len), quote_type);	
	else // Normal WORD
		add_token(s_tlist, T_WORD, strdup_max(s, start, len), quote_type);	
	return(start + len);
}

t_token *tokenisation(char *input, t_token *s_tlist, int i)
{
	s_tlist = ft_calloc(1, sizeof(* s_tlist));
	if (!(s_tlist))
		return (0);
	while(input[i])
	{
		i += str_has_space(input, i); //ignorer les espaces en debut de ligne
		if (input[i] == '\0')  //utile ?
			break ;
		if (input[i] == '|')
			i += add_token(&(s_tlist), T_PIPE, strdup_max("|", 0, 1), 0);
		else if (input[i + 1] && (input[i] == '>' && input[i + 1] == '>'))
			i += add_token(&(s_tlist), T_REDIR_APPEND, strdup_max(">>", 0, 2), 0);
		else if (input[i + 1] && (input[i] == '<' && input[i + 1] == '<'))
			i += add_token(&(s_tlist), T_HEREDOC, strdup_max("<<", 0, 2), 0);
		else if (input[i] == '>')
			i += add_token(&(s_tlist), T_REDIR_OUT, strdup_max(">", 0, 1), 0);
		else if (input[i] == '<')
			i += add_token(&(s_tlist), T_REDIR_IN, strdup_max("<", 0, 1), 0);
		else // word!
			i = token_is_word(&(s_tlist), input, i, 0);
		if (!(s_tlist)) // i = 0 -> malloc failed in strdup or add_token
			return (0);
	}
	return ((s_tlist));
}

	// while ((*s_tlist)) //DEBUGG
	// {
	// 	printf("\n"); // pour DEBUGG
	// 	printf("output : %s\n", (*s_tlist)->value); // pour DEBUGG
	// 	printf("type : %u\n", (*s_tlist)->type); // pour DEBUGG
	// 	printf("quote type : %u\n", (*s_tlist)->quotes); // pour DEBUGG
	// 	(*s_tlist) = (*s_tlist)->next;
	// }
	// printf("\n"); // pour DEBUGG