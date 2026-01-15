/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:41:57 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/15 14:29:14 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_quote_type
{
    QUOTE_NONE,      //0  / possible expansion
    QUOTE_SINGLE,    //1  /1 token, no expansion
    QUOTE_DOUBLE     //2 / 1 token, possible expansion
}   t_quote_type;

typedef enum e_token_type 
{
	T_WORD,          //0- ex: echo, "hello", abc.txt
	T_WORD_ADJ,      //1- ex: <a'b'"c"> = 3 adjacent tokens
	T_PIPE,          //2- |
	T_REDIR_IN,      //3- <
	T_REDIR_OUT,     //4- >
	T_REDIR_APPEND,  //5- >>
	T_HEREDOC        //6- <<
}   t_tok_type;
	
typedef enum e_st_type  
{
	NULL,				//0
	ST_TEXT,          //1-   [0]-> blabla<separateur ou '\0'> 
	ST_VAR,           //2-   $USER
	ST_UNVALID_VAR,   //3-   $USERunvalidchars
	ST_STATUS         //4- 	 $?
}   t_subtok_type;

typedef struct s_sub_token
{
    char				*value;
	t_subtok_type		subtok_type;
    struct s_sub_token	*next;
}   t_sub;

typedef struct s_token
{
    t_tok_type    type;
	t_quote_type	quotes;
    char            *value;
    struct s_token  *next;
}   t_token;

#endif
