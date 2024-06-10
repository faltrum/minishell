/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:55:36 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/09 04:18:03 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_blank(char c)
{
	if (c && ft_strchr(" \t", c))
		return (1);
	return (0);
}

t_bool	is_meta(char c)
{
	if (ft_strchr("|&()<>", c) || is_blank(c))
		return (1);
	return (0);
}

t_bool	is_regular(char c)
{
	return (!is_meta(c));
}

t_redirect	*last_redir_node(t_redirect *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}
t_word_list	*last_word_node(t_word_list *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}
