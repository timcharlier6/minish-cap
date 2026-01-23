/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:02:22 by ticharli          #+#    #+#             */
/*   Updated: 2026/01/23 18:17:22 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_warning(t_redir *infile, int line_nbr)
{
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putstr_fd(ft_itoa(line_nbr), 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(infile->name, 2);
	ft_putstr_fd("')\n", 2);
}

int	read_heredoc_lines(t_redir *infile, t_env *env, int status,
		int *pipe_write_fd)
{
	char	*line;
	int		line_nbr;

	line_nbr = 1;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			heredoc_warning(infile, line_nbr);
			break ;
		}
		if (ft_strcmp(line, infile->name) == 0)
		{
			free(line);
			break ;
		}
		line = process_line(line, infile, env, status);
		ft_putstr_fd(line, *pipe_write_fd);
		ft_putstr_fd("\n", *pipe_write_fd);
		free(line);
		line_nbr++;
	}
	return (0);
}

char	*process_line(char *line, t_redir *infile, t_env *env, int status)
{
	char	*expanded;

	if (infile->quotes == 0 && ft_strchr(line, '$') != -1)
	{
		expanded = expand_heredoc_line(line, env, status);
		free(line);
		return (expanded);
	}
	return (line);
}

int	handle_heredoc(t_redir *infile, t_env *env, int status)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (perror("heredoc pipe"), -1);
	read_heredoc_lines(infile, env, status, &pipe_fd[1]);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

char	*expand_heredoc_line(char *line, t_env *env, int status)
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
