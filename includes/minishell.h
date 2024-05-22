/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:39:15 by oseivane          #+#    #+#             */
/*   Updated: 2024/05/20 21:17:36 by kseligma         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/wait.h>

// Readline .h files
# include "../readline/readline.h"
# include "../readline/history.h"

// Our .h files
# include "../libft/libft.h"
# include "structs.h"
# include "definitions.h"
# include "get_next_line.h"


//GLOBAL VARIABLE

int wstatus;

//DISPLAYS
void		ft_printall(t_var *var);
char		*intToString(int num);
char		*toString_t_var(t_var *var);
char		*toString_t_env(t_env *env);
char		*toString_t_info_tree(t_info_tree *tree);

//INITIALIZE
int			init_loop(char **argv, char **env, int fd);
t_var		*init_struct(char **env);
t_info_tree	*init_linked_tree(char *command, char *operator, char *prev_op);
t_info_tree	*init_struct_tree(void);

//ENVIROMENT
void		save_env(t_var *var, char **env);
void		add_in_env(t_var *var, char *name, char *value);
void		ft_lstdelone_env(t_env **lst, t_env *todelate);
void		ft_lstadd_back_env(t_env **lst, t_env *new);
t_env		*ft_lstnew_env(void *name, char *value);
t_env		*ft_lstlast_env(t_env *lst);
t_env		*find_in_env(t_env *lst, char *name);

//INPUT
char		*get_cwd(t_var *var);
void		manage_history(char *line, char **previous_str);

//UTILS
int			valid_chars(char n);
char		*ft_strcat(char *dest, char *src);
void		func_exit(t_var *var);
char		*ft_newold(char *new, char *old);

//TREE OPERATIONS
bool		ft_replace_chrchr(char *str, char find, char replace);
char		*ft_replace_strstr(char *string, int index, int len, char *replace);
void		ft_remove_chr(char *str, char find);
char		*save_sentence_r(char *string, int num);
char		*save_sentence_l(char *string, int num);
void		check_operator(t_info_tree *tree);

//FREE
void		free_arr(char **arr);
void		free_binnarytree(t_info_tree *tree);
void		make_binnary_tree(t_var *var, char *line);

//GET INFORMATION
int			get_biggest_priority(char *string);
char		*get_operator(char *string, int j);
char		*save_params(char *str);
char		*save_command(char *str);

//SIGNALS
void		update_signal(t_env *env);
static void	read_handler(int signal, siginfo_t *data, void *n_data);
static void	heredoc_handler(int signal, siginfo_t *data, void *n_data);
static void	exec_handler(int signal, siginfo_t *data, void *n_data);
void		init_signals(int mode);

//BUILT-IN
void		save_actions(t_var *var);
int			function_ptr(t_var *var, char **params, int should_wait);

void		save_actions_op(t_var *var);
void		function_ptr_op(t_var *var, t_info_tree *tree);

void		ft_echo(t_var *var, char **params);
void		ft_pwd(t_var *var, char **params);
void		update_oldpwd(t_var *var, char *newpwd);
void		change_path(t_var *var, char*param, char *path, char *old_path);
void		ft_cd(t_var *var, char **params);
void		print_env(t_var *var, char *str);
void		ft_exit(t_var *var, char **params);
char		*ft_strcat(char *dest, char *src);
char		*find_func(char **paths, char *function);
int			execute_action(t_var *var, char **params);
void		ft_unset(t_var *var, char**params);
void		ft_help(t_var *var, char **params);
void		get_add_var_env(t_var *var, char **params, int index);
void		ft_export(t_var *var, char **params);
void		ft_env(t_var *var, char **params);
void		ft_redirection_out(t_var *var, t_info_tree *tree);
void		ft_doubleredirection_out(t_var *var, t_info_tree *tree);
void		ft_redirection_in(t_var *var, t_info_tree *tree);
void		ft_doubleredirection_in(t_var *var, t_info_tree *tree);
void		ft_semicolon(t_var *var, t_info_tree *tree);

//ERROR
void		stx_error(char *error_msg);
int			exec_error(char *command, char *error_msg);
void		stx_error_op(char *error_msg, char op);

//PIPES
int			func_pipe(t_var *var, char *command);


// NEW FUNCITONS (TODO: ORDER)
int			search_pipe(char *str);

int			search_andand_or_oror(char *str, char c);

int			search_group(char *str);

t_command	*parse_list(char *str);

char		*ft_substr(char const *s, unsigned int start, size_t len);

char		*get_left_side(char *str, enum e_connector connector);

char		*get_right_side(char *str, enum e_connector connector);

void		free_command(t_command *command);

void		free_word_list(t_word_list *words, int free_word);

void		free_redirects(t_redirect *redirects);

t_command	*create_simple_command(char *str);

t_command	*create_connected_command(char *str, enum e_connector connector);

int			wordchar(char c);

int			search_redir(char *str, int *i);

int			search_word(char *str, int *i);

int			pre_parse_words_and_redirects(char *str, t_simple_command *command);

int			parse_word(char *str, int *i, t_word_list** words);

int			add_quoted_word(char *str, int* i, char** word, char c);

int			add_normal_word(char *str, int* i, char** word);

int			parse_redir(char *str, int *i, t_redirect** redirs);

int			execute_commands(t_command *head, t_var *var);

char		**list_to_arr(t_word_list *words);

void		printf_commands(t_command *node);

int			do_here_doc(t_redirect *redir);

t_command	*parser(char *str);

char		*expansion(t_var *var, char *command);

int			execute_pipeline(t_connection *command, t_var *var);

#endif