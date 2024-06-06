#include "minishell.h"

static void	*free_connected_args(char *ls, char *rs, t_command *node)
{
	free(ls);
	free(rs);
	(void) node;
	if (node)
		free(node->value.connection);
	free(node);
	return (NULL);
}

static int	alloc_str(char *str, char **ls, char **rs, enum e_connector c)
{
	*ls = get_left_side(str, c);
	*rs = get_right_side(str, c);
	if (!*ls || !*rs)
		return (perr(0, 1, "minishell: memory error\n"));
	return (1);
}

static int	alloc_node(t_command **node)
{
	*node = malloc(sizeof(t_command));
	if (*node)
		(*node)->value.connection = malloc(sizeof(t_connection));
	if (!(*node) || !(*node)->value.connection)
		return (perr(0, 1, "minishell: memory error\n"));
	return (1);
}

int	has_content(char *str, enum e_connector connector)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == 0)
	{
		if (connector == pipe_con)
			return (perr(0, 1,"minishell: syntax error near unexpected token '|'\n"));
		else if (connector == or_or)
			return (perr(0, 1,"minishell: syntax error near unexpected token '||'\n"));
		else if (connector == and_and)
			return (perr(0, 1,"minishell: syntax error near unexpected token '&&'\n"));
	}
	return (1);
}

t_command	*parse_connected_command(char* str, enum e_connector connector)
{
	t_command	*node;
	char		*left_side;
	char		*right_side;

	node = NULL;
	if (!alloc_str(str, &left_side, &right_side, connector) || \
	!has_content(left_side, connector) || !has_content(right_side, connector) || !alloc_node(&node))
		return (free_connected_args(left_side, right_side, node));
	node->type = cm_connection;
	node->value.connection->connector = connector;
	node->value.connection->first = parse_list(left_side);
	node->value.connection->second = parse_list(right_side);
	if (!node->value.connection->first || !node->value.connection->second)
	{
		free_command_tree(node->value.connection->first);
		free_command_tree(node->value.connection->second);
		return (free_connected_args(left_side, right_side, node));
	}
	free(left_side);
	free(right_side);
	return (node);
}
