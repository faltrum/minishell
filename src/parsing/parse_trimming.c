/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_trimming.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:55:58 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/11 22:17:57 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_left_side_pipe(char *str)
{
	int	i;
	int	nesting;

	nesting = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '(')
			nesting++;
		else if (str[i] == ')')
			nesting--;
		else if (nesting == 0 && str[i] == '|')
			break ;
		i++;
	}
	if (i == 0)
		return (ft_strdup(""));
	else
		return (ft_substr(str, 0, i));
}

static char	*get_right_side_pipe(char *str)
{
	int	i;
	int	nesting;

	nesting = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '(')
			nesting++;
		else if (str[i] == ')')
			nesting--;
		else if (nesting == 0 && str[i] == '|')
			break ;
		i++;
	}
	return (ft_substr(str, i + 1, ft_strlen(str)));
}

int	get_connector_char(enum e_connector connector, char *c)
{
	if (connector == or_or)
	{
		*c = '|';
		return (1);
	}
	else if (connector == and_and)
	{
		*c = '&';
		return (1);
	}
	return (0);
}

char	*get_left_side(char	*str, enum e_connector connector)
{
	int		len;
	char	c;
	int		nesting;

	nesting = 0;
	len = ft_strlen(str);
	if (!get_connector_char(connector, &c))
		return (get_left_side_pipe(str));
	while (len > 1)
	{
		if (str[len] == '(')
			nesting++;
		else if (str[len] == ')')
			nesting--;
		else if (nesting == 0 && str[len] == c && str[len - 1] == c)
			break ;
		len --;
	}
	if (len < 2)
		return (ft_strdup(""));
	else
		return (ft_substr(str, 0, len - 1));
}

char	*get_right_side(char *str, enum e_connector connector)
{
	int		len;
	char	c;
	int		nesting;

	nesting = 0;
	len = ft_strlen(str);
	if (!get_connector_char(connector, &c))
		return (get_right_side_pipe(str));
	while (len > 1)
	{
		if (str[len] == '(')
			nesting++;
		else if (str[len] == ')')
			nesting--;
		else if (nesting == 0 && str[len] == c && str[len - 1] == c)
			break ;
		len--;
	}
	return (ft_substr(str, len + 1, ft_strlen(str)));
}
