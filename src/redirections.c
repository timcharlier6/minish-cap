/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:03:46 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/15 15:17:11 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_heredoc(t_redir *redir)
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
		if (ft_strcmp(line, redir->name) == 0)
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

int	handle_redir_in(t_redir *infile)
{
	int	fd;

	fd = -1;
	while (infile)
	{
		if (infile->type == T_REDIR_IN)
			fd = open(infile->name, O_RDONLY);
		else if (infile->type == T_HEREDOC)
			fd = handle_heredoc(infile);
		if (fd == -1)
			return (perror(infile->name), 1);  
		dup2(fd, STDIN_FILENO);  // STDIN_FILENO = 0
		close(fd);
		infile = infile->next;
	}
	return (0);
}

int	handle_redir_out(t_redir *outfile)
{
	int	fd;

	fd = -1;
	while (outfile)
	{
		if (outfile->type == T_REDIR_OUT)
			fd = open(outfile->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);  //branche mon fichier sur un fd disponible (vide) le fd est un genre de pointeur sur un tableau de correspondance
		else if (outfile->type == T_REDIR_APPEND)
			fd = open(outfile->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (perror(outfile->name), 1);  
		dup2(fd, STDOUT_FILENO);   // STDOUT-FILENO est en fait 1, dup2 dupliaue le flux de fd sur 1, donc la case 1 pointe maintenant sur le meme <objet-fichier> que la case fd du tableau de correspondances.
		close(fd); // on n a plus besoin de fd, on peut le fermer.
		outfile = outfile->next;
	}
	return (0);
}

// O_WRONLY permet l'écriture, O_CREAT crée le fichier s'il n'existe pas, 
// et O_TRUNC le vide s'il existe déjà.