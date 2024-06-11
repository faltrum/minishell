/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searching.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:55:19 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/12 01:03:00 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_list(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			update_quote_flag_parsing(str[i], &flag);
		else if ( !flag && (str[i] == '(' || str[i] == ')'))
			return (1);
		i++;
	}
	return (0);
}

int	search_andand_or_oror(char *str, char *c)
{
	int		flag;
	int		nesting;
	size_t	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	flag = 0;
	nesting = 0;
	while (!*c && len > 0)
	{
		if (str[len] == '\'' || str[len] == '\"')
			update_quote_flag_parsing(str[len], &flag);
		else if (!flag && str[len] == '(')
			nesting++;
		else if (!flag && str[len] == ')')
			nesting--;
		else if (!flag && !nesting && \
			((str[len] == '|' && str[len - 1] == '|') \
			|| (str[len] == '&' && str[len - 1] == '&')))
			*c = str[len];
		len --;
	}
	return (*c);
}

int	search_pipe(char *str)
{
	int	flag;
	int	nesting;
	int	i;

	i = 0;
	nesting = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			update_quote_flag_parsing(str[i], &flag);
		else if (!flag && str[i] == '(')
			nesting++;
		else if (!flag && str[i] == ')')
			nesting--;
		else if (!flag && nesting == 0 \
			&& str[i] == '|' && str[i + 1] != '|')
			return (1);
		i++;
	}
	return (0);
}

int	search_redir(char *str, int *i)
{
	while (is_blank(str[*i]))
		(*i)++;
	if (str[*i] == '>' || str[*i] == '<')
		return (1);
	return (0);
}

int	search_word(char *str, int *i)
{
	while (is_blank(str[*i]))
		(*i)++;
	if (is_regular(str[*i]))
		return (1);
	else if (str[*i] == '\'' || str[*i] == '"')
		return (1);
	return (0);
}
