/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:31:53 by csimonne          #+#    #+#             */
/*   Updated: 2025/12/05 16:34:20 by csimonne         ###   ########.fr       */
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
// transformer cette fonction en IS_BUILTIN et ne pas l utiliser pour Filtrer !
// puis aussi retirer tt ce qui n ets pas nom de builtin
// static void fill_tab(char **cmd_name_chain)
// {
// 	cmd_name_chain[0] = "echo";
// 	cmd_name_chain[1] = "cd";
// 	cmd_name_chain[2] = "pwd";
// 	cmd_name_chain[3] = "export";
// 	cmd_name_chain[4] = "unset";
// 	cmd_name_chain[5] = "env";
// 	cmd_name_chain[6] = "exit";
// 	cmd_name_chain[7] = "/";  // absolu
// 	cmd_name_chain[8] = "./";  //relatif courant
// 	cmd_name_chain[9] = "../";  // relatif parent
// 	cmd_name_chain[10] = "'";  // simple quote
// 	cmd_name_chain[11] = "\"";  // double quote
// 	cmd_name_chain[12] = NULL;
// }

// int	check_if_builtin(char *input, int i, int res)
// {
// 	char *cmd_name_chain[11 + 1];

// 	fill_tab(cmd_name_chain);
// 	while (i < 12)
// 	{
// 		res = ft_strncmp_m(input, cmd_name_chain[i], 
// 			ft_strlen(cmd_name_chain[i]));
// 		if (res == 0)
// 			return (1);
// 		i++;
// 	}
// 	// if (!str_is_only_space(input)) // if its not just space, display error msg
// 	// 		new_line_after_message(input, 0);
// 	return (0);
// }
