#include "../../includes/Header.h"

static void	*free_connected_args(char *ls, char *rs, t_command *node)
{
	free(ls);
	free(rs);
	if (node)
		free(node->value.connection);
	free(node);
	return (NULL);
}

int static	alloc_str(char *str, char **ls, char **rs, enum e_connector c)
{
	*ls = get_left_side(str, c);
	*rs = get_right_side(str, c);
	if (!*ls || !*rs) 
	{
		printf("Allocation error\n");
		return (0);
	}
	return (1);
}

int static	alloc_node(t_command **node)
{
	*node = ft_calloc(1, sizeof(**node));
	if (*node)
		(*node)->value.connection = \
		ft_calloc(1, sizeof(*((*node)->value.connection)));
	if (!(*node) || !(*node)->value.connection) 
	{
		printf("Allocation error\n");
		return (0);
	}
	return (1);
}

int	has_content(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == 0) 
	{
		printf("Syntax error: Empty command on && or || or |\n");
		return (0);
	}
	return (1);
}

t_command	*create_connected_command(char* str, enum e_connector connector)
{
	t_command	*node;
	char		*left_side;
	char		*right_side;

	if (!alloc_str(str, &left_side, &right_side, connector) || \
	!has_content(left_side) || !has_content(right_side) || !alloc_node(&node))
		return (free_connected_args(left_side, right_side, node));
	node->type = cm_connection;
	node->value.connection->connector = connector;
	node->value.connection->first = parse_list(left_side);
	node->value.connection->second = parse_list(right_side);
	if (!node->value.connection->first || !node->value.connection->second) 
	{
		free_command(node->value.connection->first);
		free_command(node->value.connection->second);
		return (free_connected_args(left_side, right_side, node));
	}
	free(left_side);
	free(right_side);
	return (node);
}
