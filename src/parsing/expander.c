/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:14:59 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/08 13:48:53 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// is sent here the rest of the string after $ (only one token)
static char *expand(char *str, t_env *env, int once, int posit)
{
	char 	*expanded;
	char 	*temp_exp;
	t_env	*head;

	init_to_zero(3, &expanded, &temp_exp, &head);
	head = env;
	while (!expanded)
	{
		while (env)
		{
			while ((ft_strncmp_exp(&str[posit], env->key) == 0) 
				&& (posit != 0 || once == 1))
			{
				temp_exp = expanded;
				expanded = ft_strjoin(temp_exp, env->value);
				if (char_search_len(str, '$', posit, 0) == 0)
					return(expanded);  //ex->  break ;
				posit += char_search_len(str, '$', posit, 0);
				env = head;
				once = 0;
			}
			env = env->next;
		}
		if (!(char_search_len(str, '$', posit, 0)))
			return(ft_strjoin(expanded, ""));
		env = head;
		posit += char_search_len(str, '$', posit, 0);
	}
	return(expanded);
}

// everything should be freed IN this function if malloc errors happen !
static char *cat_of_all_parts(int pos, char *exp, char *whole_string)
{
	char	*before_dollar;
	char	*bd_and_exp;
	char	*after_exp;
	char	*whole;
	int		jump_key;

	init_to_zero(5, &before_dollar, &bd_and_exp, &after_exp, &whole, &jump_key);
	if (pos > 1 && (!(before_dollar = strdup_max(whole_string, 0, pos -1 ))))
		return (free_temp(&exp, &whole, &before_dollar, &bd_and_exp), NULL);
	if (!(bd_and_exp = ft_strjoin(before_dollar, exp)))
		return (free_temp(&exp, &whole, &before_dollar, &bd_and_exp), NULL);
	jump_key = char_search_len_0(whole_string, '$', 0);
	jump_key += (is_valid_var_char(&whole_string[jump_key], 0));
	if (whole_string[jump_key] != '\0')
	{
		if (!(after_exp = strdup_max(&whole_string[jump_key], 0,
			ft_strlen(&whole_string[jump_key]))))
		return (free_temp(&exp, &whole, &before_dollar, &bd_and_exp), NULL);
	}
	if (!(whole = ft_strjoin(bd_and_exp, after_exp)))
		return (free_temp(&exp, &whole, &before_dollar, &bd_and_exp),NULL);
	free(whole_string);
	return (whole);
}

int expander(t_mothership *m, t_token *t_list, t_env *env)
{
	void			*head_m;
	char			*exp;
	int				position;

	head_m = m->token_list;
	while(t_list)
	{
		init_to_zero(2, &position, &exp);
		position = char_search_len_0(&t_list->value[position], '$', 0);
		while (position && t_list->quotes != QUOTE_SINGLE)
		{
			if (!(exp = expand(&t_list->value[position], env, 1, 0)))
				exp = ft_strdup("");
			if (!(t_list->value = cat_of_all_parts(position, exp, t_list->value)))
					return (free(exp), 0);
			free(exp);
			position = char_search_len_0(&t_list->value[position], '$', 0);
		}
		t_list = t_list->next;
		m->token_list = m->token_list->next;
	}
	m->token_list = head_m;
	return (1);
}
