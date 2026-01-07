/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 20:33:05 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/05 13:44:41 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_redir
{
    char			*name;
    t_token_type	type;
    struct s_redir	*next;
}	t_redir;

typedef struct s_cmd_table
{
	char		**args;   // !<a'b'"c">= 3 tokens (via lexer) mais UN SEUL ARG FINAL!
	t_redir		*infile;    // Utilisé pour < et <<
	t_redir		*outfile;   // Utilisé pour > et >>
	struct s_cmd_table *next;
}	t_cmd_table;
