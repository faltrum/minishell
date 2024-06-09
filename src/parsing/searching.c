/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searching.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:55:19 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/09 04:35:07 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_list(char *str)
{
	int	i;
	int	quoted;

	i = 0;
	quoted = -1;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quoted *= -1;
		else if (quoted == -1 && (str[i] == '(' || str[i] == ')'))
			return (1);
		i++;
	}
	return (0);
}

int	search_andand_or_oror(char *str, char c)
{
	int		quoted;
	int		nesting;
	size_t	len;

	if (!str)
		return (0);
	len = strlen(str);
	quoted = -1;
	nesting = 0;
	while (len > 0)
	{
		if (str[len] == '\'' || str[len] == '\"')
			quoted *= -1;
		else if (quoted == -1 && str[len] == '(')
			nesting++;
		else if (quoted == -1 && str[len] == ')')
			nesting--;
		else if (quoted == -1 && nesting == 0 && \
			str[len] == c && str[len - 1] == c)
			return (1);
		len --;
	}
	return (0);
}

int	search_pipe(char *str)
{
	int	quoted;
	int	nesting;
	int	i;

	i = 0;
	nesting = 0;
	quoted = -1;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quoted *= -1;
		else if (quoted == -1 && str[i] == '(')
			nesting++;
		else if (quoted == -1 && str[i] == ')')
			nesting--;
		else if (quoted == -1 && nesting == 0 \
			&& str[i] == '|' && str[i + 1] != '|')
			return (1);
		i++;
	}
	return (0);
}

int	search_redir(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
	if (str[*i] == '>' || str[*i] == '<')
		return (1);
	return (0);
}

int	search_word(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
	if (is_regular(str[*i]))
		return (1);
	else if (str[*i] == '\'' || str[*i] == '"')
		return (1);
	return (0);
}
