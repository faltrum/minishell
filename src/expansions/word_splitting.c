/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:57:21 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/10 06:49:51 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_word_to_list(t_word_list **head, char *str, int *i, int flags)
{
	int			end;
	t_word_list	*node;

	end = *i;
	while (str[end])
	{
		if (str[end] == QUOTE || str[end] == DQUOTE)
			update_quote_flag(str, &end, &flags);
		else if (is_blank(str[end]) && !(flags & DQUOTED) && !(flags & QUOTED))
			break ;
		else
			end ++;
	}
	node = allocate_last_node(head);
	if (!node)
		return (-1);
	node->word = ft_substr(str, *i, end - *i);
	if (!node->word)
		return (ft_err(-1, STR_MEMORY_ERR, strerror(errno), 0));
	*i = end;
	return (0);
}

static int	splitting_error(t_word_list **head)
{
	free_word_list(*head, 1);
	*head = NULL;
	return (-1);
}
int	word_splitting(char *str, t_word_list **head)
{
	int	i;
	int	flags;

	flags = 0;
	i = 0;
	(void) flags;
	(void) head;
	while (str[i])
	{
		if (!is_blank(str[i]) && add_word_to_list(head, str, &i, flags) == -1)
			return (splitting_error(head));
		if (str[i] == QUOTE || str[i] == DQUOTE)
			update_quote_flag(str, &i, &flags);
		else if (str[i])
			i ++;
	}
	if (add_word_to_list(head, str, &i, flags) == -1)
		return (splitting_error(head));
	return (0);
}
