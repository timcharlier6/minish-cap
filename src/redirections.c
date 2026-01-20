/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:03:46 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/20 15:56:03 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_heredoc_line(char *line, t_env *env, int status)
{
	t_sub	*sub_list;
	t_sub	*temp;
	char	*res;
	char	*join;

	sub_list = init_sub(line, NULL, env, status);
	if (!sub_list)
		return (ft_strdup(""));
	res = ft_strdup("");
	temp = sub_list;
	while (temp)
	{
		join = ft_strjoin(res, temp->value);
		free(res);
		res = join;
		temp = temp->next;
	}
	free_subt_list(&sub_list);
	return (res);
}

static int	handle_heredoc(t_redir *infile, t_env *env, int status)
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
		if (infile->quotes == 0 && ft_strchr(line, '$') != -1)
		{
			char *expanded = expand_heredoc_line(line, env, status);
			free(line);
			line = expanded;
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

static int	is_redir_in(t_redir *infile, t_env *env, int status)
{
	int		fd;

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

int	handle_redirections(t_cmd_table *cmd, t_env *env, int status)
{
	t_redir *infile_temp;
	t_redir *outfile_temp;

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