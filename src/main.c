/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:31:53 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/23 20:05:14 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

volatile sig_atomic_t	g_signal = 0;

static void	readline_error_code(t_main *main)
{
	if (g_signal != 0)
	{
		main->last_status = 128 + g_signal;
		g_signal = 0;
	}
}

// cmd_not_found = 1 -> displays cmd not found + message
void	new_line_message(char *message, int not_found, char *redir)
{
	if (not_found == 1)
		printf("command not found : %s\n", message);
	if (redir != NULL)
		printf("syntax error near token : %s\n", redir);
	else
		printf("%s\n", message);
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
	m->token_list = expander(m->token_list, env, m->token_list,
			&m->last_status);
	if (!m->token_list)
		return (0);
	n_commands = pipe_token_search(m->token_list) + 1;
	m->cmd_table = parsing(m->token_list, n_commands, n_commands, 0);
	if (!m->cmd_table)
		return (0);
	return (1);
}

static int	filter_input(char *str, int *last_status)
{
	int	last;

	last = 0;
	if (str[0] == '\0' || str_is_only_space(str))
		return (0);
	last = ft_strlen(str) - 1;
	while (last > 0 && (str[last] == ' ' || (str[last] >= 9
				&& str[last] <= 13)))
		last--;
	if (str[str_has_space(str, 0)] == '|')
		return (*last_status = 2, new_line_message("syntax error near `|'", 0,
				0), add_history(str), 0);
	if (str[last] == '|' || str[last] == '<' || str[last] == '>')
		return (*last_status = 2,
			new_line_message("syntax error near token `newline'", 0, 0),
			add_history(str), 0);
	if (check_unclosed_quotes(str))
	{
		new_line_message("Syntax error : please close your quotes.", 0, 0);
		return (*last_status = 2, add_history(str), 0);
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_main	*main;

	if (!init_main(&main, &ac, &av) || !init_env_list(&main->env, envp))
		return (clean_up(main, 1, 1, 0), 1);
	while (1)
	{
		input = readline("minishell > ");
		readline_error_code(main);
		if (!input)
			exit_w_message();
		if (filter_input(input, &main->last_status))
		{
			add_history(input);
			if (!parsing_hub(input, main, main->env))
				break ;
			if (check_double_redirs(main, main->token_list))
				exec(main, main->env);
		}
		clean_up(main, 0, 0, 0);
		free(input);
	}
	return (clean_up(main, 1, 1, 0), rl_clear_history(), 0);
}
