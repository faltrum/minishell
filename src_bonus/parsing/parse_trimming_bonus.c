/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_trimming_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:55:58 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/20 10:49:58 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static char	*get_left_side_pipe(char *str)
{
	int	i;
	int	nesting;
	int	flag;

	nesting = 0;
	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			update_quote_flag_parsing(str[i], &flag);
		else if (!flag && str[i] == '(')
			nesting++;
		else if (!flag && str[i] == ')')
			nesting--;
		else if (!flag && nesting == 0 && str[i] == '|')
			break ;
		i++;
	}
	return (ft_substr(str, 0, i));
}

static char	*get_right_side_pipe(char *str)
{
	int	i;
	int	nesting;
	int	flag;

	nesting = 0;
	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			update_quote_flag_parsing(str[i], &flag);
		else if (!flag && str[i] == '(')
			nesting++;
		else if (!flag && str[i] == ')')
			nesting--;
		else if (!flag && nesting == 0 && str[i] == '|')
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
	int		flag;

	nesting = 0;
	flag = 0;
	len = ft_strlen(str);
	if (!get_connector_char(connector, &c))
		return (get_left_side_pipe(str));
	while (len > 1)
	{
		if (str[len] == '\'' || str[len] == '\"')
			update_quote_flag_parsing(str[len], &flag);
		else if (!flag && str[len] == '(')
			nesting++;
		else if (!flag && str[len] == ')')
			nesting--;
		else if (!flag && !nesting && str[len] == c && str[len - 1] == c)
			break ;
		len --;
	}
	return (ft_substr(str, 0, len - 1));
}

char	*get_right_side(char *str, enum e_connector connector)
{
	int		len;
	char	c;
	int		nesting;
	int		flag;

	nesting = 0;
	flag = 0;
	len = ft_strlen(str);
	if (!get_connector_char(connector, &c))
		return (get_right_side_pipe(str));
	while (len > 1)
	{
		if (str[len] == '\'' || str[len] == '\"')
			update_quote_flag_parsing(str[len], &flag);
		else if (!flag && str[len] == '(')
			nesting++;
		else if (!flag && str[len] == ')')
			nesting--;
		else if (!flag && !nesting && str[len] == c && str[len - 1] == c)
			break ;
		len--;
	}
	return (ft_substr(str, len + 1, ft_strlen(str)));
}
