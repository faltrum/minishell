/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:38:34 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/20 10:47:24 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

# include "definitions_bonus.h"

typedef struct s_var		t_var;

struct						s_command;

typedef struct s_command	t_command;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_actions
{
	char	*action;
	int		(*function)(t_var *var, char **params);
}	t_actions;

typedef struct s_var
{
	t_command			*command_tree;
	struct s_env		*env;
	struct s_actions	*act;
	int					exit;
	int					kill;
	int					fds_list[3];
}	t_var;

typedef struct s_redirect	t_redirect;

typedef struct s_word_list	t_word_list;

struct s_word_list
{
	t_word_list		*next;
	char			*word;
};

struct s_redirect
{
	t_redirect			*next;
	enum e_redir_type	type;
	char				*word;
	t_word_list			*expanded;
	int					fd;
};

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
	int						flags;
};

#endif
