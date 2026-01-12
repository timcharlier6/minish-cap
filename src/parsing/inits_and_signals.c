/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_and_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:07:19 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/12 17:20:30 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

volatile sig_atomic_t g_signal;

int	init_mothership(t_mothership **mothership)
{
	(*mothership) = ft_calloc(1, sizeof(t_mothership));
	if (!(*mothership))
		return (0);
	(*mothership)->last_status = 0;
	return (1);
}

void	signal_handler(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line(); // prepares readline for a new line
    rl_redisplay();
}

void	signal_init()
{
	g_signal = 0;
	signal(SIGINT, signal_handler); // SIGINT = CTRL+C (by default)
	signal(SIGQUIT, SIG_IGN);       // Ctrl+\ ignoré
}

int	init_env_list(t_env **env_list, char **envp)
{
	int		i;
	int		split_pos;
	t_env	*new_node;

	i = -1;
	*env_list = NULL;
	if (!envp)
		return (0);
	while (envp[++i])
	{
		split_pos = (char_search_len(envp[i], '=', 0, 0) - 1);
		if (split_pos != -1)
		{
			new_node = malloc(sizeof(t_env));
			if (!new_node)
				return (0);
			new_node->key = strdup_max(envp[i], 0, split_pos);
			new_node->value = ft_strdup(envp[i] + split_pos + 1);
			if (!new_node->key || !new_node->value)
				return (0); 
			new_node->next = *env_list;
			*env_list = new_node;
		}
	}
	return (1);
}
