#include "minishell.h"

int	left_par(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else if (str[i] == '(')
		{
			str[i] = ' ';
			return (1);
		}
		else
			return (perr(0, 1, "minishell: syntax error unexpected token near parenthesis\n"));
	}
	return (1);
}

int	right_par(char	*str)
{
	size_t	len;

	len = strlen(str) - 1;
	while (len > 0)
	{
		if (str[len] == ' ')
			len--;
		else if (str[len] == ')')
		{
			str[len] = ' ';
			return (1);
		}
		else
			return (perr(0, 1, "minishell: syntax error unexpected token near parenthesis\n"));
	}
	return (0);
}

int	empty_par(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == 0)
		return (perr(1, 1, "minishell:  syntax error unexpected token near parenthesis\n"));
	return (0);
}

t_command	*parse_grouped_command(char *str)
{
	if (!left_par(str))
		return (NULL);
	else if (!right_par(str))
		return (NULL);
	else if (empty_par(str))
		return (NULL);
	else
		return (parse_list(str));
}

t_command	*parse_list(char *str)
{
	if (search_andand_or_oror(str, '&'))
		return (parse_connected_command(str, and_and));
	else if (search_andand_or_oror(str, '|'))
		return (parse_connected_command(str, or_or));
	else if (search_group(str))
		return (parse_grouped_command(str));
	else if (search_pipe(str))
		return (parse_connected_command(str, pipe_con));
	else
		return (parse_simple_command(str));
}
