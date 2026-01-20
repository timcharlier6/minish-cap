/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 20:33:05 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/20 13:04:36 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

typedef struct s_redir
{
    char			*name;
    t_tok_type		type;
    struct s_redir	*next;
}	t_redir;

typedef struct cmd_table
{
	char				**args;   // !<a'b'"c">= 3 tokens (via lexer) mais UN SEUL ARG FINAL!
	t_redir				*infile;    // Utilisé pour < et <<
	t_redir				*outfile;   // Utilisé pour > et >>
	struct cmd_table 	*next;
}	t_cmd_table;
