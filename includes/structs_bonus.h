/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:38:34 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/17 11:28:44 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

# include "definitions.h"

typedef struct s_var		t_var;

struct						s_command;

typedef struct s_command	t_command;

// Descripción: Esta estructura representa una variable
// de entorno en la shell.
// Campos:
// 	name: Un puntero a una cadena que representa el
// 		nombre de la variable de entorno.
// 	value: Un puntero a una cadena que representa
// 		el valor de la variable de entorno.
// 	end_type: Un entero que indica el tipo de finalización.
// 	prev: Un puntero al elemento previo en la lista enlazada.
// 	next: Un puntero al siguiente elemento en la lista enlazada.
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

// Descripción: Esta estructura representa una acción (
// comando interno) que puede ejecutar la shell.
// Campos:
// 	action: Un puntero a una cadena que representa
// 		el nombre de la acción.
// 	function: Un puntero a una función que ejecuta
// 		la acción.

typedef struct s_actions
{
	char	*action;
	int		(*function)(t_var *var, char **params);
}	t_actions;

// Descripción: Esta estructura representa el estado
// general de la shell.
// Campos:
//     tree: Un puntero a la raíz del árbol de análisis
//		sintáctico que se construye a partir de los comandos
//      ingresados por el usuario.
//     env: Un puntero a una lista enlazada que contiene
//		las variables de entorno de la shell.
//     act: Un puntero a una lista de acciones
//		(comandos internos) que puede ejecutar la shell.
//     op: Un puntero a una lista de operadores
//		(redirecciones, secuenciadores) que pueden estar
//			presentes en los comandos.

typedef struct s_var
{
	t_command			*command_tree;
	struct s_env		*env;
	struct s_actions	*act;
	int					exit;
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
