/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_expansion_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:57:16 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/17 11:26:08 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	expand_pathname(t_word_list *next, \
t_word_list *node, t_word_list *directories)
{
	t_word_list	*matches;
	t_word_list	*head;

	head = NULL;
	while (directories)
	{
		if (node->word && *(node->word) \
		&& wildcard_matches(node->word, directories->word, 0, 0))
		{
			matches = allocate_last_node(&head);
			matches->word = ft_strdup(directories->word);
		}
		directories = directories->next;
	}
	if (head)
	{
		matches->next = next;
		free(node->word);
		node->word = head->word;
		node->next = head->next;
		free(head);
	}
	return (1);
}

static int	should_be_expanded(char *str)
{
	int	i;
	int	flags;

	i = 0;
	flags = 0;
	while (str[i])
	{
		if (str[i] == QUOTE || str[i] == DQUOTE)
			update_quote_flag(str, &i, &flags);
		else if (!(flags & QUOTED) && !(flags & DQUOTED) && str[i] == '*')
			return (1);
		else
			i ++;
	}
	return (0);
}

int	pathname_expansion(t_word_list *node)
{
	t_word_list	*next;
	t_word_list	*directories;

	directories = NULL;
	if (get_directories(&directories) == -1)
		return (-1);
	while (node)
	{
		next = node->next;
		if (should_be_expanded(node->word))
			expand_pathname(next, node, directories);
		node = next;
	}
	free_word_list(directories, 1);
	return (0);
}
