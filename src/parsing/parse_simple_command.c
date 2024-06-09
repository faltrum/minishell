/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:12:26 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/09 05:03:48 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	allocate_simple_command(t_command **node)
{
	if (ft_errloc(sizeof(**node), 1, (void **) node) == -1)
		return (-1);
	if (ft_errloc(sizeof(t_simple_command), 1, \
		(void **) &(*node)->value.simple) == -1)
	{
		free(*node);
		return (-1);
	}
	return (0);
}

static void	parse_words_and_redirects(char *str, \
t_redirect **redir, t_word_list **words)
{
	int			i;
	int			res;

	i = 0;
	res = 0;
	while (res == 0 && str[i])
	{
		if (search_redir(str, &i))
			res = parse_redir(str, &i, redir);
		else if (search_word(str, &i))
			res = parse_word(str, &i, words);
		else if (str[i])
			res = ft_err(-1, "syntax error near unexpected token", 0, 0);
	}
	if (res == -1)
	{
		free_word_list(*words, 1);
		free_redirects(*redir);
		*redir = NULL;
		*words = NULL;
	}
}

t_command	*parse_simple_command(char* str)
{
	t_command	*node;
	t_word_list	*words;
	t_redirect	*redirects;

	words = NULL;
	redirects = NULL;
	node = NULL;
	if (allocate_simple_command(&node) == -1)
		return (NULL);
	parse_words_and_redirects(str, &redirects, &words);
	if (!words && !redirects)
	{
		free(node->value.simple);
		free(node);
		return (NULL);
	}
	node->type = cm_simple;
	node->value.simple->words = words;
	node->value.simple->redirects = redirects;
	return (node);
}
