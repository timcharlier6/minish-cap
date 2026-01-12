/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:31:53 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/12 18:47:58 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"   
#include <limits.h>

// static void debugg_print(const t_mothership *m)
// {
//     t_cmd_table *cmd;
//     t_redir     *in;
//     t_redir     *out;

//     cmd = m->s_cmd_table;
//     while (cmd)
//     {
//         printf("-----CMD-------\n");

//         for (int i = 0; cmd->args[i]; i++)
//             printf("args -> %s\n", cmd->args[i]);

//         in = cmd->infile;
//         while (in)
//         {
//             printf("Infiles ------\n");
//             printf("type -> %u\n", in->type);
//             printf("name -> %s\n", in->name);
//             in = in->next;
//         }

//         out = cmd->outfile;
//         while (out)
//         {
//             printf("Outfiles ------\n");
//             printf("type -> %u\n", out->type);
//             printf("name -> %s\n", out->name);
//             out = out->next;
//         }

//         printf("\n");
//         cmd = cmd->next;
//     }
// }

static int parsing_hub(char *input, t_mothership *m, t_env *env)
{
	int n_commands;
	(void)env;

	n_commands = 0;
	n_commands = char_search_n(input, '|') + 1;
	m->token_list = tokenisation(input, m->token_list, 0);
	if (!(m->token_list))
		return (0);
	if (!(clean_all_quotes(m->token_list)))
		return (0);
	if (!(m->token_list = expander
		(m->token_list, env, m->token_list, &m->last_status)))
		return (0);
	if (!(m->s_cmd_table = parsing(m->token_list, n_commands, n_commands)))
		return (0);
	// debugg_print(m);
	return(1);
}

static int filter_input(char *input)
{
	if (input[0] == '\0') // blank entry
		return (0);
	if (input[str_has_space(input, 0)] == '|')
	{
		new_line_after_message("parse error near `|'", 0);
		return(add_history(input), 0);
	}
	if (input[ft_strlen(input) - 1] == '|' || input[ft_strlen(input) - 1] == '<' 
		|| input[ft_strlen(input) - 1] == '>')
	{
		new_line_after_message("parse error near `\\n'", 0);
		return(add_history(input), 0);
	}
	if (str_is_only_space(input))
	{
		rl_redisplay();
		return(0);
	}
	if (((char_search_n(input, '\'')) % 2 != 0) || 
		((char_search_n(input, '\"')) % 2 != 0)) // not pair number of quotes '
	{
		new_line_after_message(NULL, 1);
		return(add_history(input), 0);
	}
	return (1);
}

int main(int ac, char **av, char **envp)
{
	char 			*input;
	t_mothership	*mothership;
	(void)ac;
	(void)av;
	
	signal_init();
	if (!init_mothership(&mothership) || !init_env_list(&mothership->env, envp))
		return(clean_up(mothership, 1, 1), 1);
	while (1)
	{
		if (!(input = readline("minishell > "))) // error or CTRL + D (EOF simulated)
			exit_w_message();
		if (filter_input(input))
        {
			if (!parsing_hub(input, mothership, mothership->env))
				break ;
			exec(mothership);
			add_history(input);
		}
		clean_up(mothership, 0, 0);
		free(input);
	}
	clean_up(mothership, 1, 1);
	rl_clear_history();
    return (0);
}
