/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:14:59 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/09 14:46:20 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



// // is sent here the rest of the string after $ (only one token)
// static char *expand(char *str, t_env *env, int once, int posit)
// {
// 	char 	*expanded;
// 	char 	*temp_exp;
// 	t_env	*head;

// 	init_to_zero(3, &expanded, &temp_exp, &head);
// 	head = env;
// 	while (!expanded)
// 	{
// 		while (env)
// 		{
// 			while ((ft_strncmp_exp(&str[posit], env->key) == 0) 
// 				&& (posit != 0 || once == 1))
// 			{
// 				temp_exp = expanded;
// 				expanded = ft_strjoin(temp_exp, env->value);
// 				if (char_search_len(str, '$', posit, 0) == 0)
// 					return(expanded);  //ex->  break ;
// 				posit += char_search_len(str, '$', posit, 0);
// 				env = head;
// 				once = 0;
// 			}
// 			env = env->next;
// 		}
// 		if (!(char_search_len(str, '$', posit, 0)))
// 			return(0);
// 		env = head;
// 		posit += char_search_len(str, '$', posit, 0);
// 	}
// 	return(expanded);
// }

// int expander(t_mothership *m, t_token *t_list, t_env *env)
// {
// 	void			*head_m;
// 	char			*exp;
// 	int				position;

// 	head_m = m->token_list;
// 	while(t_list)
// 	{
// 		init_to_zero(2, &position, &exp);
// 		position = char_search_len_0(&t_list->value[position], '$', 0);
// 		while (position && t_list->quotes != QUOTE_SINGLE)
// 		{
// 			if (!(exp = expand(&t_list->value[position], env, 1, 0)))
// 				exp = ft_strdup("");
// 			if (!(t_list->value = cat_of_all_parts(position, exp, t_list->value)))
// 				return (free(exp), 0);
// 			free(exp);
// 			position = char_search_len_0(&t_list->value[position], '$', 0);
// 		}
// 		t_list = t_list->next;
// 		m->token_list = m->token_list->next;
// 	}
// 	m->token_list = head_m;
// 	return (1);
// }

// everything should be freed IN this function if malloc errors happen !
static char *cat_all(int pos, char *exp, char *whole_string, char *before_dollar)
{
	char	*bd_and_exp;
	char	*after_exp;
	char	*whole;
	int		jump_key;

	init_to_zero(4, &bd_and_exp, &after_exp, &whole, &jump_key);
	if (!(bd_and_exp = ft_strjoin(before_dollar, exp)))
		return (free_temp(&exp, &whole, &before_dollar, &bd_and_exp), NULL);
	jump_key = (is_valid_var_char(&whole_string[pos], 0));
	if (jump_key == 0)
		jump_key = (is_valid_var_char(&whole_string[pos + 1], 0) + 2);
	if (whole_string[jump_key + pos] != '\0')
	{
		if (!(after_exp = strdup_max(&whole_string[jump_key + pos], 0,
			ft_strlen(&whole_string[jump_key + pos]))))
		return (free_temp(&exp, &whole, &before_dollar, &bd_and_exp), NULL);
	}
	if (!(whole = ft_strjoin(bd_and_exp, after_exp)))
		return (free_temp(&exp, &whole, &before_dollar, &bd_and_exp),NULL);
	free(before_dollar);
	free_temp(&exp, &whole_string, &after_exp, &bd_and_exp);
	return (whole);
}

static int	process_dollar(char *str, int *position, char **expanded)
{
	if ((((str[*position - 1] == '$')
		&& (str[*position] == '\0' || str[*position] == '$'))
			|| (!is_valid_var_char(0, str[*position]))))
	{
		if (!(*expanded = ft_strdup(str)))
			return (0);
	}
	return (1);
}

// is sent here the rest of the string after $ (only one token)
static char *expand(char *str, int *position, t_env *env)
{
	char 	*expanded;
	// t_env	*head;

	expanded = NULL;
	// if (!(process_dollar(str, *position, &expanded)))
	// 	return (0);
	while (env)
		{
			if (str[*position] && ft_strncmp_exp(&str[*position], env->key) == 0)
			{
				
				expanded = ft_strdup(env->value);
				if (!(expanded))
					return(0);
			}
			else if ((ft_strncmp_exp(&str[*position], env->key)) == -1)
			{
				expanded = ft_strdup("");
				*position -= 1;
				return (expanded);
			}
			env = env->next;
		}
	return (expanded);
}

t_token *expander(t_token *t_list, t_env *env, t_token *head)
{
	char			*exp;
	char			*before_dollar;
	int				position;
	int				temp_position;
	
	while(t_list)
	{
		init_to_zero(4, &position, &temp_position, &exp, &before_dollar);
		while (t_list->quotes != QUOTE_SINGLE)
		{
			position += char_search_len_0(&t_list->value[position], '$', 0);	
			if ((position <= temp_position && t_list->value[0] != '$')
				|| (!(is_valid_var_char(0, t_list->value[position]))))
				break ;
			temp_position = position;
			if (!(exp = expand(t_list->value, &temp_position, env)))
				return (NULL);
			if (position > 1)
			{
				if (!(before_dollar = strdup_max
					(t_list->value, 0, temp_position))) //position-1
					return (0);
			}
			if (!(t_list->value = cat_all(temp_position, exp, t_list->value, 
				before_dollar)))
				return (free(exp), free(before_dollar), NULL);
			exp = NULL;
			if (!(process_dollar(t_list->value, &position, &exp)))
				return (0);
		}
		t_list = t_list->next;
	}
	return (t_list = head);
}
