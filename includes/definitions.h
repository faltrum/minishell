/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:38:26 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/11 01:58:25 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

//UTILS
# define PROGRAM_NAME "minishell"
# define STR_EXIT "exit\n"
# define PROMPT_END "$ "
# define END_OF_LINE "\n"
# define BLANK_CHARS " \t"
# define META_CHARS "|&()<>"

//COLORS
# define BLUE "\033[0;34m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"

//ACTIONS
# define NUM_ACTIONS 9
# define EXIT "exit"
# define ECHO "echo"
# define PWD "pwd"
# define CD "cd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define HELP "help"

//ERROR MSG
# define ERR_CMD_NOT_FOUND "command not found"
# define ERR_IS_DIR "Is a directory"
# define ERR_MALLOC "error allocating memory"
# define ERR_SEPARATOR ": "
# define ERR_UNMATCHED_QUOTE "syntax error unmatched quote"
# define ERR_UNEXPECTED_TOKEN "syntax error near unexpected token"
# define ERR_SYNTAX_REDIRECTION "syntax error after redirection"
# define ERR_SYNTAX_PARENTHESIS "syntax error unexpected token near parenthesis"
# define ERR_SYNTAX_PIPE "syntax error near unexpected token `|'"
# define ERR_SYNTAX_CONJ1 "syntax error near unexpected token `||'"
# define ERR_SYNTAX_CONJ2 "syntax error near unexpected token `&&'"
# define ERR_HEREDOC "heredoc error"
# define ERR_PATHNAME_OPENDIR "pathname expansion opendir error"
# define ERR_STDIN_PERROR "minishell: restoring STDIN"
# define ERR_STDOUT_PERROR "minishell: restoring STDOUT"
# define ERR_FORK "fork error on subshell attempt"
# define ERR_AMB_REDIR "ambiguous redirect"
# define ERR_PERROR_INPUT_REDIR "minishell: redirect input"
# define ERR_PERROR_OUTPUT_REDIR "minishell: redirect output"
# define ERR_PERROR_APPEND_REDIR "minishell: append"
# define ERR_VALID_IDENTIFIER "not a valid identifier"
# define ERR_TOO_MANY_ARGS "too many arguments"
# define ERR_NUMERIC_ARG "numeric argument required"

//WARNINGS
# define WAR_BROKE_STDIN "warning broke STDIN"
# define WAR_BROKE_STDOUT "warning broke STOUDOUT"
# define WAR_BUILTIN_MEMORY "warning: memory error allocating builtins"
# define WAR_HERE_EOF "warning: here-document\
	delimited by end-of-file (wanted `"
# define WAR_HERE_EOF2 "')"

//Expansion flags
# define EXP_ERR 0x2
# define QUOTED 0x4
# define DQUOTED 0x8
# define EXPANDED 0x10
# define HEREDOC 0x20
# define QUOTE -1
# define DQUOTE -2

//Execution flags
# define WAIT 0x2
# define SUBSHELL 0x4
# define RESTOREFD 0x8

//Signal helper
# define SINT_OFF 0
# define SINT_ON 1
# define SINT_HEREDOC 2

extern int	g_sigint;

enum e_redir_type
{
	input_redir,
	output_redir,
	append,
	here_doc,
};

enum e_command_type
{
	cm_simple,
	cm_connection,
};

enum e_connector
{
	pipe_con,
	and_and,
	or_or
};

#endif
