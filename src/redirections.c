/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:03:46 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/23 18:17:27 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir_in(t_redir *infile, t_env *env, int status)
{
	int	fd;

	fd = -1;
	if (infile->type == T_REDIR_IN)
		fd = open(infile->name, O_RDONLY);
	else if (infile->type == T_HEREDOC)
		fd = handle_heredoc(infile, env, status);
	if (fd == -1)
		return (perror(infile->name), 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	is_redir_out(t_redir *outfile)
{
	int	fd;

	fd = -1;
	if (outfile->type == T_REDIR_OUT)
		fd = open(outfile->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (outfile->type == T_REDIR_APPEND)
		fd = open(outfile->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror(outfile->name), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_redirections(t_cmd_table *cmd, t_env *env, int status)
{
	t_redir	*infile_temp;
	t_redir	*outfile_temp;

	infile_temp = cmd->infile;
	outfile_temp = cmd->outfile;
	while (infile_temp)
	{
		if (is_redir_in(infile_temp, env, status) != 0)
			return (1);
		infile_temp = infile_temp->next;
	}
	while (outfile_temp)
	{
		if (is_redir_out(outfile_temp) != 0)
			return (1);
		outfile_temp = outfile_temp->next;
	}
	return (0);
}

// O_WRONLY permet l'écriture, O_CREAT crée le fichier s'il n'existe pas,
// et O_TRUNC le vide s'il existe déjà.