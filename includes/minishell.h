/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseus <kseus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:39:15 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/08 09:48:57 by kseus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//System .h files
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/signal.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/wait.h>
# include <stdarg.h>
# include <dirent.h>

// Readline .h files
# include "../readline/readline.h"
# include "../readline/history.h"

// Our .h files
# include "../libft/libft.h"
# include "structs.h"
# include "definitions.h"
# include "get_next_line.h"

//INITIALIZE
t_var		*init_struct(char **env);
void		save_actions(t_var *var);

//ENVIROMENT
void		save_env(t_var *var, char **env);
void		add_in_env(t_var *var, char *name, char *value);
void		ft_lstdelone_env(t_env **lst, t_env *todelate);
void		ft_lstadd_back_env(t_env **lst, t_env *new);
t_env		*ft_lstnew_env(void *name, char *value);
t_env		*ft_lstlast_env(t_env *lst);
t_env		*find_in_env(t_env *lst, char *name);
void		replace_or_set_env(t_var *var, char *name, char *value);

//INPUT
char		*get_cwd(t_var *var);

//PARSING
t_command	*parser(t_var *var, char *str);
t_command	*parse_list(char *str);
t_command	*parse_simple_command(char *str);
t_command	*parse_connected_command(char *str, enum e_connector connector);
int			parse_redir(char *str, int *i, t_redirect **redirs);
int			parse_word(char *str, int *i, t_word_list **words);
int			add_word(char *str, int *i, char **word);
int			search_pipe(char *str);
int			search_andand_or_oror(char *str, char c);
int			search_group(char *str);
int			search_redir(char *str, int *i);
int			search_word(char *str, int *i);
char		*get_left_side(char *str, enum e_connector connector);
char		*get_right_side(char *str, enum e_connector connector);
char		**list_to_arr(t_word_list *words);
void		parse_words_and_redirects(char *str, \
				t_redirect **redir, t_word_list **words);

//SIGNALS
void		init_signals(void);
void		reset_signal(t_var *var);
void		set_signal_ignore(int signal);
void		set_signal_handler(int signal, void (*handler));
void		sint_handler(int signal);

//BUILT-IN
int			is_builtin(t_var *var, char *command);
int			ft_echo(t_var *var, char **params);
int			ft_pwd(t_var *var, char **params);
int			ft_cd(t_var *var, char **params);
int			ft_exit(t_var *var, char **params);
int			ft_unset(t_var *var, char**params);
int			ft_help(t_var *var, char **params);
int			ft_export(t_var *var, char **params);
int			ft_env(t_var *var, char **params);

//ERROR
void		stx_error(char *error_msg);
int			exec_error(char *command, char *error_msg);
void		stx_error_op(char *error_msg, char op);
long long	perr(int return_value, int argc, ...); // Prohibido variadicos

//EXECUTION
int			execute_command_tree(t_command *head, t_var *var);
int			execute_pipeline(t_command *node, t_var *var);
int			do_here_doc(t_var *var, t_redirect *redir);
int			execute_simple_command(t_simple_command	*command, \
			t_var *var, int flags);
int			try_execution(t_var *var, char **params, int should_wait);
int			execute_here(t_var *var, char **params);
int			execute_redirections(t_redirect *redirects);
char		*find_path(char *env, char *param);
char		**env_to_array(t_env *env);

//EXPANSIONS
int			expand_command_lists(t_simple_command *command, t_var *var);
void		remove_quotes(char *str);
void		sanitize_list(t_word_list *node);
void		hide_quotes(char *str);
int			parameter_expansion(t_var *var, char **str);
int			word_splitting(char *str, t_word_list **head);
int			pathname_expansion(t_word_list *node);
int			get_directories(t_word_list **directories);

//UTILS
void		func_exit(t_var *var);
void		restore_fds(int fds[2]);
t_word_list	*last_word_node(t_word_list *node);
t_redirect	*last_redir_node(t_redirect *node);
t_bool		is_blank(char c);
t_bool		is_regular(char c);
t_bool		is_meta(char c);
t_bool		empty_line(char *str);
void		update_quote_flag(char *str, int *i, int *flags);

//MEMORY UTILS
void		free_command_tree(t_command *command);
void		free_word_list(t_word_list *words, int free_word);
void		free_redirects(t_redirect *redirects);
void		free_arr(char **arr);
t_word_list	*allocate_last_node(t_word_list **words);

//OTHER UTILS (TO BE DELETED)
void		printf_commands(t_command *node);
void		print_args(t_word_list *words);

#endif
