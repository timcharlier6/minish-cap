/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 12:09:29 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/06 12:44:10 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Dans la fonction cd, il faudra utiliser getcwd() pour récupérer 
// le nouveau chemin et aller mettre à jour la value du maillon PWD 
// dans ta liste env_list.
int pwd(void)
{
    char buf[PATH_MAX];
    char *cwd;

    cwd = getcwd(buf, PATH_MAX);
    if (cwd)
    {
        ft_putendl_fd(cwd, STDOUT_FILENO);
        return (0);
    }
    errmsg_cmd("pwd", strerror(errno), errno);
    return (1);
}