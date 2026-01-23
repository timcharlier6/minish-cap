/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ticharli <ticharli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:22:05 by csimonne          #+#    #+#             */
/*   Updated: 2026/01/23 20:10:26 by ticharli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define PATH_MAX 1024

# include "command_table.h"
# include "token.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_signal;

struct							s_token;
struct							s_cmd_table;

typedef struct s_env
{
	char						*key;
	char						*value;
	struct s_env				*next;
}								t_env;

typedef struct s_main
{
	int							last_status;
	t_token						*token_list;
	t_cmd_table					*cmd_table;
	t_env						*env;
}								t_main;

// helpers TIM
char							*ft_strncpy(char *s1, char *s2, size_t n);
char							*ft_strdup(char *s);
int								ft_strcmp(const char *s1, const char *s2);
char							**ft_split(char *s, char c);
int								ft_memcmp(const void *s1, const void *s2,
									size_t n);
char							*ft_strnstr(char *haystack, char *needle,
									size_t len);
void							cd_error(const char *arg);
char							*get_env_val(t_env *env, char *key);
void							update_env(t_env *env, char *key, char *value);
int								update_pwds(t_env *env, char *old, char *path);
char							*get_target(t_cmd_table *cmd, t_env *env);
void							quicksort(char **env, int low, int high);
char							**create_sorted_env_array(t_env *my_env,
									int count);
char							*format_env_var(t_env *env);
int								print_sorted_env(t_env *my_env);
void							extract_key_value(char *arg, char **key,
									char **value, int *eq_pos);
int								update_existing_env(t_env *temp, char *key,
									char *value, int eq_pos);
char							*ft_substr(char *s, unsigned int start,
									size_t len);
int								is_builtin(char *cmd);
int								run_builtin(t_main *m, t_cmd_table *cmd);
int								ft_strchr(char *s, int c);
int								is_valid_env_var_key(char *arg);
// helpers CAM
int								check_unclosed_quotes(char *input);
int								ft_strlen(char *s);
int								ft_strncmp(const char *s1, const char *s2,
									size_t n);
int								ft_strncmp_m(char *s1, const char *s2,
									size_t n);
int								ft_strncmp_exp(const char *s1, const char *s2);
int								is_valid_subvar_separator(const char *s,
									char c);
int								char_search_len(const char *s, const char c,
									int start, int w_on);
int								char_search_len_0(const char *s, const char c,
									int start);
int								pipe_token_search(t_token *list);
int								quote_search(char *s, char c, char other_quote);
int								token_word_be_arg_count(t_token *token_list);
int								redir_token_count(t_token *t_l, t_tok_type typ1,
									t_tok_type typ2);
int								str_is_only_space(char *str);
int								str_has_space(char *str, int start);
int								str_is_char(char *str, int start);
t_token							*skip_word_or_adjacents(t_token *list,
									int skip_current);
char							*ft_strdup(char *s);
char							*strdup_max(const char *s, int start, int len);
char							*ft_strjoin(char *s1, char *s2);
char							*ft_strjoin_m(char *s1, char *s2);
char							*ft_strjoin_len(char *s1, char *s2, int len);
void							*ft_calloc(size_t nmemb, size_t size);
void							ft_putstr_fd(char *s, int fd);
void							ft_putendl_fd(char *s, int fd);
char							*ft_itoa(int n);
int								ft_isdigit_m(int n);
long int						ft_atoi(const char *nptr);
char							**copy_list_to_array(t_env *env);
int								inc_shlvl(t_env *env);
int								join_redir_adj(t_token *token_list,
									t_redir **outfile);
int								skip_void_arg(t_token **t_l);
int								check_double_redirs(t_main *main, t_token *l);
// helpers : clean / exit
void							clean_up(t_main *main, int free_m_shell,
									int free_env, int exit_status);
void							free_token_list(t_token **s_list);
void							free_redir_list(t_redir **s_list);
void							free_env_list(t_env **env);
void							free_subt_list(t_sub **s_list);
void							free_temp(char **exp, char **whole,
									char **before_d, char **both);
void							exit_w_message(void);
void							free_array(char **array);
void							new_line_message(char *message,
									int not_found, char *redir);
// initialisations
int								init_main(t_main **main, int *ac, char ***av);
int								init_env_list(t_env **env_list, char **envp);
void							init_to_zero(int *i, int *y, t_sub **a,
									t_sub **b);
t_sub							*init_sub(char *s, t_sub *sub_t, t_env *env,
									int c_status);
// signals
void							signal_handler(int sig);
void							signal_init(void);
void							signal_init_to_default(void);
void							signal_ignore(void);
// minishell : parsing
int								check_if_builtin(char *input, int i, int res);
int								token_is_word(t_token **tlist, char *s,
									int start, int quote_type);
t_token							*tokenisation(char *input, t_token *tlist,
									int i);
t_cmd_table						*parsing(t_token *tlist, int n_cmd, int n_cmdcp,
									t_cmd_table *head);
int								clean_all_quotes(t_token *list);
int								errmsg_cmd(char *command, char *error_message,
									int error_nb);

void							double_redir_error(t_main *main, char *token);
void							free_ptr(void *ptr);
t_token							*expander(t_token *tlist, t_env *env,
									t_token *head, int *c_status);
// builtins
int								my_echo(t_cmd_table *cmd);
int								pwd(void);
int								cd(t_cmd_table *cmd, t_env *my_env);
int								my_env(t_env *my_env);
int								export(t_cmd_table *cmd, t_env *my_env);
int								unset(t_cmd_table *cmd, t_env *env);
int								builtin_exit(char **args, t_main *m);
// exec
int								exec(t_main *m, t_env *env);
int								exec_external(t_cmd_table *cmd, char **envp);
char							*find_path(char *cmd, char **envp);
int								handle_redirections(t_cmd_table *cmd,
									t_env *env, int status);

									

void	child_process(t_main *m, t_cmd_table *cmd, int prev_fd,
		int pipe_fd[2]);
int	exec_local(t_cmd_table *cmd, char **envp);
int	exec_external(t_cmd_table *cmd, char **envp);
#endif