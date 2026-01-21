/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:31:53 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/21 14:59:02 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

static int	init_main(t_main **main)
{
	(*main) = ft_calloc(1, sizeof(t_main));
	if (!(*main))
		return (0);
	(*main)->last_status = 0;
	return (1);
}

static void	new_line_after_message(char *message)
{
	if (message == NULL)
		printf("%s\n", "Syntax error : please close your quotes.");
	else
		printf("command not found : %s\n", message);
	rl_redisplay();
}

static int	parsing_hub(char *input, t_main *m, t_env *env)
{
	int	n_commands;

	n_commands = 0;
	m->token_list = tokenisation(input, m->token_list, 0);
	if (!(m->token_list))
		return (0);
	if (!(clean_all_quotes(m->token_list)))
		return (0);
	m->token_list = expander(m->token_list, env,
			m->token_list, &m->last_status);
	if (!m->token_list)
		return (0);
	n_commands = pipe_token_search(m->token_list) + 1;
	m->cmd_table = parsing(m->token_list, n_commands, n_commands, 0);
	if (!m->cmd_table)
		return (0);
	return (1);
}

static int	filter_input(char *input)
{
	if (input[0] == '\0')
		return (0);
	if (input[str_has_space(input, 0)] == '|')
	{
		new_line_after_message("syntax error near `|'");
		return (add_history(input), 0);
	}
	if (input[ft_strlen(input) - 1] == '|' || input[ft_strlen(input) - 1] == '<'
		|| input[ft_strlen(input) - 1] == '>')
	{
		new_line_after_message("syntax error near `\\n'");
		return (add_history(input), 0);
	}
	if (str_is_only_space(input))
	{
		rl_redisplay();
		return (0);
	}
	if (check_unclosed_quotes(input))
	{
		new_line_after_message(NULL);
		return (add_history(input), 0);
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_main	*main;

	(void)ac;
	(void)av;
	signal_init();
	if (!init_main(&main) || !init_env_list(&main->env, envp))
		return (clean_up(main, 1, 1), 1);
	while (1)
	{
		input = readline("minishell > ");
		if (!input)
			exit_w_message();
		if (filter_input(input))
		{
			add_history(input);
			if (!parsing_hub(input, main, main->env))
				break ;
			exec(main, main->env);
		}
		clean_up(main, 0, 0);
		free(input);
	}
	clean_up(main, 1, 1);
	return (rl_clear_history(), 0);
}
