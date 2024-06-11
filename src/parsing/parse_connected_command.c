/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_connected_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 02:42:02 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/11 23:22:27 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*free_connected_args(char *ls, char *rs, t_command *node)
{
	free(ls);
	free(rs);
	free_command_tree(node);
	return (NULL);
}

static int	alloc_str(char *str, char **ls, char **rs, enum e_connector c)
{
	*ls = get_left_side(str, c);
	*rs = get_right_side(str, c);
	if (!*ls || !*rs)
		return (ft_err(-1, ERR_MALLOC, 0, 0));
	return (0);
}

static int	alloc_node(t_command **node)
{
	*node = ft_calloc(1, sizeof(**node));
	if (*node)
		(*node)->value.connection = ft_calloc(1, sizeof(t_connection));
	if (!(*node) || !(*node)->value.connection)
		return (ft_err(-1, ERR_MALLOC, 0, 0));
	return (0);
}

static int	has_content(char *str, enum e_connector connector)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == 0)
	{
		if (connector == pipe_con)
			return (ft_err(-1, ERR_SYNTAX_PIPE, 0, 0));
		else if (connector == or_or)
			return (ft_err(-1, ERR_SYNTAX_CONJ1, 0, 0));
		else if (connector == and_and)
			return (ft_err(-1, ERR_SYNTAX_CONJ2, 0, 0));
	}
	return (0);
}

t_command	*parse_connected_command(char	*str, enum e_connector connector)
{
	t_command	*node;
	char		*left_side;
	char		*right_side;

	node = NULL;
	if (alloc_str(str, &left_side, &right_side, connector) == -1 || \
		has_content(left_side, connector) == -1 || \
		has_content(right_side, connector) == -1 || \
		alloc_node(&node) == -1)
		return (free_connected_args(left_side, right_side, node));
	node->type = cm_connection;
	node->value.connection->connector = connector;
	node->value.connection->first = parse_list(left_side);
	node->value.connection->second = parse_list(right_side);
	if (!node->value.connection->first || !node->value.connection->second)
		return (free_connected_args(left_side, right_side, node));
	free(left_side);
	free(right_side);
	return (node);
}
