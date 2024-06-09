/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:38:26 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/09 02:24:37 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

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
# define PROGRAM_NAME "minishell"
# define LSKIP "\n"
# define WRONG_OP_NL "minishell: syntax error 'new line'\n"
# define WRONG_OP "minishell: syntax error near unexpected token"
# define NO_CLOSED "minishell: syntax error no closed quote\n"
# define NOT_FOUND "command not found\n"
# define NO_PERM "Permission denied\n"
# define NO_DIR "Not a directory\n"
# define NO_EXIST "No such file or directory.\n"
# define NO_FORK "Error. Fork no created\n"
# define STR_EXIT "exit\n"
# define STR_MEMORY_ERR "memory error"

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
extern int	g_sigint; //REVISAR

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

typedef int	t_bool;

#endif
