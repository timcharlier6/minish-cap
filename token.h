/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:41:57 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/20 18:09:12 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}	t_quote_type;

typedef enum e_token_type
{
	T_WORD,
	T_WORD_ADJ,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC
}	t_tok_type;

typedef enum e_st_type
{
	ST_NULL,
	ST_TEXT,
	ST_VAR,
	ST_UNVALID_VAR,
	ST_STATUS
}	t_subtok_type;

typedef struct s_sub_token
{
	char				*value;
	t_subtok_type		subtok_type;
	struct s_sub_token	*next;
}	t_sub;

typedef struct s_token
{
	t_tok_type			type;
	t_quote_type		quotes;
	char				*value;
	struct s_token		*next;
}	t_token;

#endif
