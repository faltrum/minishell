/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 02:22:32 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/11 22:17:57 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	left_par(char	*str)
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
			return (ft_err(-1, ERR_SYNTAX_PARENTHESIS, 0, 0));
	}
	return (1);
}

static int	right_par(char	*str)
{
	size_t	len;

	len = ft_strlen(str) - 1;
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
			return (ft_err(-1, ERR_SYNTAX_PARENTHESIS, 0, 0));
	}
	return (0);
}

static int	empty_par(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == 0)
		return (ft_err(-1, ERR_SYNTAX_PARENTHESIS, 0, 0));
	return (0);
}

static t_command	*parse_list_command(char *str)
{
	t_command *command;

	if (left_par(str) == -1)
		return (NULL);
	else if (right_par(str) == -1)
		return (NULL);
	else if (empty_par(str) == -1)
		return (NULL);
	command = parse_list(str);
	if (command)
		command->flags = SUBSHELL;
	return (command);
}

t_command	*parse_list(char *str)
{
	char	c;

	c = 0;
	if (search_andand_or_oror(str, &c))
	{
		if (c == '|')
			return (parse_connected_command(str, or_or));
		else
			return (parse_connected_command(str, and_and));
	}
	else if (search_list(str))
		return (parse_list_command(str));
	else if (search_pipe(str))
		return (parse_connected_command(str, pipe_con));
	else
		return (parse_simple_command(str));
}
