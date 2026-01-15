/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:03:46 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/15 17:30:32 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_heredoc(t_redir *infile)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
		return (perror("heredoc pipe"), -1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		// Si la ligne est exactement le délimiteur, on s'arrête
		if (ft_strcmp(line, infile->name) == 0)
		{
			free(line);
			break ;
		}
		// On écrit la ligne dans le pipe avec un retour à la ligne
		ft_putstr_fd(line, pipe_fd[1]);
		ft_putstr_fd("\n", pipe_fd[1]);
		free(line);
	}
	// On ferme l'écriture pour que le lecteur reçoive EOF
	close(pipe_fd[1]);
	// On renvoie le bout de lecture pour le dup2
	return (pipe_fd[0]);
}

static int is_redir_in(t_redir *infile)
{
	int		fd;

	fd = -1;
	if (infile->type == T_REDIR_IN)
		fd = open(infile->name, O_RDONLY);
	else if (infile->type == T_HEREDOC)
		fd = handle_heredoc(infile);
	if (fd == -1)
		return (perror(infile->name), 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int is_redir_out(t_redir *outfile)
{
	int fd;

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

int	handle_redirections(t_cmd_table *cmd)
{
	t_redir *infile_temp;
	t_redir *outfile_temp;

	infile_temp = cmd->infile;
	outfile_temp = cmd->outfile;
	while (infile_temp)
	{
		if (is_redir_in(infile_temp) != 0)
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