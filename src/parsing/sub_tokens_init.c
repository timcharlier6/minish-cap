/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_tokens_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:38:28 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/09 21:30:00 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_text(char *str, t_sub_tok *sub_t, int len);
int is_var(char *str, t_sub_tok *sub_t, t_env *env, int len);
int is_solo_dollar(t_sub_tok *sub_t);
int is_status(t_sub_tok *sub_t, int current_status);

static int is_not_sv_separator_char(char s)
{
	if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z')
		|| (s >= '0' && s <= '9') || s == '_')
		return (0);
	return (1);
}

static int is_not_sv_separator(char *s, int whole_str_flag, int check_next)
{
	int count;

	count = 0;
	if (!s)
		return (0);
	if (*s == '$')
	{
		s++;
		count++;
	}
	if (check_next == 1)
	{
		if (*s == '\0' || is_not_sv_separator_char(*s))
			return (1);
	}
	while ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z')
		|| (*s >= '0' && *s <= '9') || *s == '_')
	{
		s++;
		count++;
	}
	if (count == ft_strlen(s) && whole_str_flag == 1)
		return (0);
	return (count);
}

static t_sub_tok *new_token(t_sub_tok *sub_t)
{
	if (sub_t == NULL)
	{
		if (!(sub_t = calloc(1, sizeof(t_sub_tok))))
			return (0);
	}
	else
	{
		if (!(sub_t->next = calloc(1, sizeof(t_sub_tok))))
			return (0);
		sub_t = sub_t->next;
		sub_t->next = NULL;
	}
	return (sub_t); 
}

//on analyse toujours a partir du char AVANT la string. dollar? vide? etc
// Un nom de variable doit obligatoirement commencer par une lettre ou '_'. sinon txt
t_sub_tok	*init_sub_tok(char *str, t_sub_tok *sub_t, t_env *env, int c_status)
{
	int 		i;
	int			watch_i;
	t_sub_tok 	*sub_t_head;
	
	init_to_zero(2, &i, &watch_i);
	while(str[i])
	{
		if (!(sub_t = new_token(sub_t)))
			return (free_subt_list(&sub_t), NULL);
		if (watch_i-- == 0) 
			sub_t_head = sub_t;
		if (str[i] == '$' && is_not_sv_separator(&str[i], 0, 1) == 1)
			i += is_solo_dollar(sub_t);			
		else if (str[i] == '$')
			i += is_var(&str[i], sub_t, env, is_not_sv_separator(&str[i], 0, 0));
		else if (str[i] == '$' && (str[i + 1] == '?'))
			i += is_status(sub_t, c_status);
		else
			i += is_text(&str[i], sub_t, is_not_sv_separator(&str[i], 0, 1));
		if (i == 0 || i <= watch_i)
			return (free_subt_list(&sub_t), NULL);
		watch_i = i;
	}
	return (sub_t = sub_t_head, sub_t);
}
