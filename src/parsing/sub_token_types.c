/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_token_types.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:38:28 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/09 21:33:48 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int expand(char *str, t_env *env, t_sub_tok **sub_t)
{
	if (str[1])
		str++;
	while (env)
		{
			if (ft_strncmp_exp(str, env->key) == 0)
			{
				
				(*sub_t)->value = ft_strdup(env->value);
				if (!((*sub_t)->value))
					return(0);
			}
			else if ((ft_strncmp_exp(str, env->key)) == -1)
			{
				(*sub_t)->value = ft_strdup("");
				if (!((*sub_t)->value))
					return(0);
				return (-1);
			}
			env = env->next;
		}
	return (1);
}

int is_var(char *str, t_sub_tok *sub_t, t_env *env, int len)
{
	int result;
	
	result = 0;
	result = expand(str, env, &sub_t);
	// result = 0; //TEST
	if (result  == 0)
		return (0);
	else if (result  == -1)
		sub_t->subtok_type = ST_UNVALID_VAR;
	else if (result  == 1)
		sub_t->subtok_type = ST_VAR;
	return (len);
}

int is_text(char *str, t_sub_tok *sub_t, int len)
{
	if (!(sub_t->value = strdup_max(str, 0, len)))
		return (0);
	sub_t->subtok_type = ST_TEXT;
	return (len);
}

int is_solo_dollar(t_sub_tok *sub_t)
{
	if (!(sub_t->value = ft_strdup("$")))
		return (0);
	sub_t->subtok_type = ST_TEXT;
	return (1);
}

int is_status(t_sub_tok *sub_t, int current_status)
{	
	sub_t->value = ft_itoa(current_status);
	if (!sub_t->value)
		return (0);
	sub_t->subtok_type = ST_STATUS;
	return (2);
}

// int is_var(char *str, t_sub_tok *sub_t, t_env *env, int len)
// {
// 	int result;
	
// 	result = 0;
// 	if (!(sub_t = calloc(1, sizeof(t_sub_tok))))
// 		return (0);
// 	result = expand(str, env, &sub_t);
// 	if (result  == 0)
// 		return (0);
// 	else if (result  == -1)
// 		sub_t->subtok_type = ST_UNVALID_VAR;
// 	else if (result  == 1)
// 		sub_t->subtok_type = ST_VAR;
// 	sub_t->next = NULL;
// 	sub_t = sub_t->next;
// 	return (len);
// }

// int is_text(char *str, t_sub_tok *sub_t, int len)
// {
// 	if (!(sub_t = calloc(1, sizeof(t_sub_tok))))
// 		return (0);
// 	if (!(sub_t->value = strdup_max(str, 0, len)))
// 		return (0);
// 	sub_t->subtok_type = ST_TEXT;
// 	sub_t->next = NULL;
// 	sub_t = sub_t->next;
// 	return (len);
// }


// int is_solo_dollar(t_sub_tok *sub_t)
// {
// 	if (!(sub_t = calloc(1, sizeof(t_sub_tok))))
// 		return (0);
// 	sub_t->value = "$";
// 	sub_t->subtok_type = ST_TEXT;
// 	sub_t->next = NULL;
// 	sub_t = sub_t->next;
// 	return (1);
// }

// int is_status(t_sub_tok *sub_t, int current_status)
// {	
// 	if (!(sub_t = calloc(1, sizeof(t_sub_tok))))
// 		return (0);
// 	sub_t->value = ft_itoa(current_status);
// 	if (!sub_t->value)
// 		return (0);
// 	sub_t->subtok_type = ST_STATUS;
// 	sub_t->next = NULL;
// 	sub_t = sub_t->next;
// 	return (2);
// }
