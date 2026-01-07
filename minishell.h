/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:22:05 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/07 19:06:36 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "token.h"
#include "command_table.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define PATH_MAX 1024

struct t_token;
struct t_cmd_table;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_mothership
{
	t_token		*token_list;
	t_cmd_table	*s_cmd_table;
	t_env		*env;
}	t_mothership;

typedef struct s_i
{
	int i; // utilise ?
	int j;
	int y;
	int count;  // utilise ?
	int count_1;
	int count_2;
	int count_3;
	int	flag;
	int error;
} t_for_static_indexes;

//helpers
int 	ft_strlen(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strncmp_m(char *s1, const char *s2, size_t n);
int		ft_strncmp_exp(const char *s1, const char *s2);
int		char_search_len(const char *s, const char c, int start, int warning_on);
int		char_search_len_0(const char *s, const char c, int start);
int		char_search_n(char *s, char c);
int		token_word_be_arg_count(t_token *token_list);
int		redir_token_count(t_token *t_l, t_token_type typ1, t_token_type typ2);
int		str_is_only_space(char *str);
int		str_has_space(char *str, int start);
int		str_is_char(char *str, int start);
t_token *skip_word_or_adjacents(t_token *list, int skip_current);
char	*ft_strdup(char *s);
char	*ft_strdup_n_free(char *s);
char	*strdup_max(const char *s, int start, int len);
char	*ft_strjoin_m(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
//helpers : clean / exit
void 	clean_up(t_mothership *mothership, int free_m_shell, int free_env);
void	free_token_list(t_token **s_list);
void	free_redir_list(t_redir **s_list);
void	exit_w_message(void);
//initialisations et signals
int		init_mothership(t_mothership **mothership);
void	signal_handler(int sig);
void	signal_init();
int		init_env_list(t_env **env_list, char **envp);
void	init_to_zero(int count, ...);
//minishell : parsing
void		new_line_after_message();
int			check_if_builtin(char *input, int i, int res);
int			token_is_word(t_token **s_tlist, char *s, int start, int quote_type);
t_token 	*tokenisation(char *input, t_token *s_tlist, int i);
t_cmd_table *parsing(t_token *s_tlist, int number_of_cmds, int number_of_cmds2);
int			clean_all_quotes(t_token *list);
int			errmsg_cmd(char *command, char *error_message, int error_nb);
void		free_ptr(void *ptr);
int 		expander(t_mothership *m, t_token *t_list, t_env *env);
//builtins
void		my_echo(t_cmd_table *cmd);
int			pwd(void);
//exec
int			exec(t_mothership *m);

#endif