/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 20:33:05 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/20 17:56:07 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

typedef struct s_redir
{
	char				*name;
	t_tok_type			type;
	int					quotes;
	struct s_redir		*next;
}						t_redir;

typedef struct cmd_table
{
	char				**args;
	t_redir				*infile;
	t_redir				*outfile;
	struct cmd_table	*next;
}						t_cmd_table;
