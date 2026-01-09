/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:31:53 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/08 17:57:05 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error_messages.h"

// see error_macros inside this function to define error_number
void	new_line_after_message(char *message, int error_number)
{
	static char *error_macros[] = {CMD_NF, SYN1};
	if (message == NULL)
		printf("%s\n", error_macros[error_number]);
	else
		printf("%s%s\n", error_macros[error_number], message);
	rl_redisplay(); // displays the current prompt line again after info line
	// rl_on_new_line(); // prepares readline for a new line
}
