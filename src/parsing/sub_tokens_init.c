/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_tokens_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:38:28 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/21 17:18:42 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_text(char *str, t_sub *sub_t, int len);
int	is_var(char *str, t_sub *sub_t, t_env *env, int len);
int	is_status(t_sub *sub_t, int current_status);

static int	is_not_sv_separator_char(char s)
{
	if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z')
		|| (s >= '0' && s <= '9') || s == '_')
		return (0);
	return (1);
}

static int	is_not_sv_separator(char *s, int whole_str_flag, int check_next)
{
	int	count;

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

static t_sub	*new_token(t_sub *sub_t)
{
	if (sub_t == NULL)
	{
		sub_t = calloc(1, sizeof(t_sub));
		if (!sub_t)
			return (0);
	}
	else
	{
		sub_t->next = calloc(1, sizeof(t_sub));
		if (!(sub_t->next))
			return (0);
		sub_t = sub_t->next;
		sub_t->next = NULL;
	}
	return (sub_t);
}

static t_sub	*is_empty(t_sub *sub_t)
{
	sub_t = calloc(1, sizeof(t_sub));
	if (!sub_t)
		return (NULL);
	sub_t->subtok_type = ST_TEXT;
	sub_t->value = ft_strdup("");
	if (!sub_t->value)
		return (NULL);
	return (sub_t);
}

t_sub	*init_sub(char *s, t_sub *sub_t, t_env *env, int c_status)
{
	int		i;
	int		watch_i;
	t_sub	*sub_t_head;

	init_to_zero(&i, &watch_i, &sub_t, &sub_t_head);
	if (s[i] == '\0')
		return (sub_t = is_empty(sub_t));
	while (s[i])
	{
		sub_t = new_token(sub_t);
		if (!sub_t)
			return (free_subt_list(&sub_t), NULL);
		if (watch_i-- == 0)
			sub_t_head = sub_t;
		if (s[i] == '$' && (s[i + 1] == '?'))
			i += is_status(sub_t, c_status);
		else if (s[i] == '$' && is_not_sv_separator(&s[i], 0, 1) != 1)
			i += is_var(&s[i], sub_t, env, is_not_sv_separator(&s[i], 0, 0));
		else
			i += is_text(&s[i], sub_t, is_not_sv_separator(&s[i], 0, 1));
		if (i == 0 || i <= watch_i)
			return (free_subt_list(&sub_t), NULL);
		watch_i = i;
	}
	return (sub_t = sub_t_head, sub_t);
}
