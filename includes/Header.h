#ifndef HEADER_H

# define HEADER_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include "stdio.h"

/* TEMPORARY FILE !!! */

# include "structs.h"
# include "minishell.h"
# include "definitions.h"
# include "get_next_line.h"

/* Grammar

<REDIRECTION> ::=  '>' <WORD>
                |  '<' <WORD>
                |  '>>' <WORD>
                |  '<<' <WORD>

<SIMPLE-COMMAND-ELEMENT> ::= <WORD>
                          |  <REDIRECTION>

<COMMAND> ::=  <SIMPLE-COMMAND-ELEMENT>
                   |  <COMMAND> <SIMPLE-COMMAND-ELEMENT>

<LIST> ::=   <LIST> '&&' <LIST>
           |  <LIST> '||' <LIST>
           |  <PIPELINE>
           |  <COMMAND>


<PIPELINE> ::=
          <PIPELINE> '|' <PIPELINE>
       |  <COMMAND>
*/

/*

 TEST LIST:



*/
// Commands

enum e_redir_type
{
	input_redir,
	output_redir,
	append,
	here_doc,
};

enum e_wordtype
{
	quoted,
	dquoted,
	single
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

typedef struct s_redirect	t_redirect;

struct s_redirect
{
	t_redirect			*next;
	enum e_redir_type	type;
	char				*word;
	int					fd;
};

typedef struct s_word_list	t_word_list;

struct s_word_list
{
	t_word_list		*next;
	char			*word;
	enum e_wordtype	type;
};

struct						s_command;

typedef struct s_command	t_command;

typedef struct s_connection
{
	t_command			*first;
	t_command			*second;
	enum e_connector	connector;
}	t_connection;

typedef struct s_simple_command
{
	t_redirect	*redirects;
	t_word_list	*words;
	char		**args;
}	t_simple_command;

union u_command_value
{
	t_connection		*connection;
	t_simple_command	*simple;	
};

struct s_command
{
	enum e_command_type		type;
	union u_command_value	value;
};

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

t_command *temp_name_additions(char *str); // TEMP

char	*expansion(t_var *var, char *command);

#endif