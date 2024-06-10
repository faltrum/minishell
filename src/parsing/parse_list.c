/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 02:22:32 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/09 02:22:33 by kseligma         ###   ########.fr       */
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
			return (ft_err(-1, \
			"syntax error unexpected token near parenthesis", 0, 0));
	}
	return (1);
}

static int	right_par(char	*str)
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
			return (ft_err(-1, \
			"syntax error unexpected token near parenthesis", 0, 0));
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
		return (ft_err(-1, \
		"syntax error unexpected token near parenthesis", 0, 0));
	return (0);
}

static t_command	*parse_list_command(char *str)
{
	if (left_par(str) == -1)
		return (NULL);
	else if (right_par(str) == -1)
		return (NULL);
	else if (empty_par(str) == -1)
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
	else if (search_list(str))
		return (parse_list_command(str));
	else if (search_pipe(str))
		return (parse_connected_command(str, pipe_con));
	else
		return (parse_simple_command(str));
}
