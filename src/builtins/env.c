/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:26:25 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/12 18:26:26 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int my_env(t_env *my_env)
{
    t_env *temp;

    temp = my_env;

    while (temp->next)
    {
        printf("%s=%s\n", temp->key, temp->value);
        temp = temp->next;
    }
    return 0;
}