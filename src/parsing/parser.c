/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:26:40 by oseivane          #+#    #+#             */
/*   Updated: 2024/05/23 13:26:42 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	left_par(char *str)
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
		else if (str[i] == ')')
		{
			printf("Syntax error, unmatched )\n");
			return (0);
		}
		else
		{
			printf("Syntax error, unexpected token before parenthesis\n");
			return (0);
		}
	}
	return (0);
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
		else if (str[len] == '(')
		{
			printf("Syntax error, unmatched (");
			return (0);
		}
		else
		{
			printf("Syntax error, unexpected token after parenthesis\n");
			return (0);
		}
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
	{
		printf("Empty parenthesis\n");
		return (1);
	}
	return (0);
}

t_command	*parse_group(char *str)
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
		return (create_connected_command(str, and_and));
	else if (search_andand_or_oror(str, '|'))
		return (create_connected_command(str, or_or));
	else if (search_group(str))
		return (parse_group(str));
	else if (search_pipe(str))
		return (create_connected_command(str, pipe_con));
	else
		return (create_simple_command(str));
}
