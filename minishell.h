/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:22:05 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/15 15:07:25 by csimonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "token.h"
# include "command_table.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>

#define PATH_MAX 1024

struct t_token;
struct t_cmd_table;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_main
{
	int			last_status; // on devra stocker le code d'erreur, en cas d'erreur, ici.
	t_token		*token_list;
	t_cmd_table	*cmd_table;
	t_env		*env;
	// char		**env_copy;  //UTILE ?  ->fonction static ds main <copy_env_array> pourrait ne pas etre indispensable
}	t_main;

//helpers TIM
char		*ft_strncpy(char *s1, char *s2, size_t n);
char		*ft_strdup(char *s);
int			ft_strcmp(const char *s1, const char *s2);
char		**ft_split(char *s, char c);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(char *haystack, char *needle, size_t len);
char		*ft_substr(char *s, unsigned int start, size_t len);  // doublon ft_strdup?
int			ft_strchr(char *s, int c);
int			is_valid_env_var_key(char *arg);
//helpers CAM
int 		ft_strlen(char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strncmp_m(char *s1, const char *s2, size_t n);
int			ft_strncmp_exp(const char *s1, const char *s2);
int			is_valid_subvar_separator(const char *s, char c);
int			char_search_len(const char *s, const char c, int start, int w_on);
int			char_search_len_0(const char *s, const char c, int start);
int			char_search_n(char *s, char c);
int			token_word_be_arg_count(t_token *token_list);
int			redir_token_count(t_token *t_l, t_tok_type typ1, t_tok_type typ2);
int			str_is_only_space(char *str);
int			str_has_space(char *str, int start);
int			str_is_char(char *str, int start);
t_token 	*skip_word_or_adjacents(t_token *list, int skip_current);
char		*ft_strdup(char *s);  // doublon ft_substr?
char		*strdup_max(const char *s, int start, int len);
char		*ft_strjoin(char *s1, char *s2);
char 		*ft_strjoin_m(char *s1, char *s2);
char		*ft_strjoin_len(char *s1, char *s2, int len);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
char		*ft_itoa(int n);
int			ft_isdigit_m(int n);
long int	ft_atoi(const char *nptr);
char		**copy_list_to_array(t_env *env);
//helpers : clean / exit
void 		clean_up(t_main *main, int free_m_shell, int free_env);
void		free_token_list(t_token **s_list);
void		free_redir_list(t_redir **s_list);
void		free_env_list(t_env **env);
void		free_subt_list(t_sub **s_list);
void		free_temp(char **exp, char **whole, char **before_d, char **both);
void		exit_w_message(void);
void		free_array(char **array);
//initialisations et signals
int			init_main(t_main **main);
void		signal_handler(int sig);
void		signal_init();
int			init_env_list(t_env **env_list, char **envp);
void		init_to_zero(int count, ...);
t_sub		*init_sub(char *s, t_sub *sub_t, t_env *env, int c_status);
//minishell : parsing
void		new_line_after_message(char *message, int error_number);
int			check_if_builtin(char *input, int i, int res);
int			token_is_word(t_token **tlist, char *s, int start, int quote_type);
t_token 	*tokenisation(char *input, t_token *tlist, int i);
t_cmd_table	*parsing(t_token *s_tlist, int number_of_cmds, int number_of_cmds2);
int			clean_all_quotes(t_token *list);
int			errmsg_cmd(char *command, char *error_message, int error_nb);
void		free_ptr(void *ptr);
t_token		*expander(t_token *tlist, t_env *env, t_token *head, int *c_status);
//builtins
int			my_echo(t_cmd_table *cmd);
int			pwd(void);
int			cd(t_cmd_table *cmd, t_env *my_env);
int			my_env(t_env *my_env);
int			export(t_cmd_table *cmd, t_env *my_env);
int			unset(t_cmd_table *cmd, t_env *env);
int			builtin_exit(char **args, t_main *m);
//exec
int			exec(t_main *m, t_env *env);
int			exec_external(t_cmd_table *cmd, char **envp);
char		*find_path(char *cmd, char **envp); // doublon avec command_path_finder ?
int			command_path_finder(t_main *m, t_env *env); // doublon find_path ?
int			handle_redir_in(t_redir *infile);
int			handle_redir_out(t_redir *outfile);


#endif