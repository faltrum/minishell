/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 02:23:53 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/11 01:22:21 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_errloc(size_t size, size_t qty, void **ptr)
{
	*ptr = ft_calloc(qty, size);
	if (!*ptr)
		return (ft_err(-1, ERR_MALLOC, strerror(errno), 0));
	return (0);
}

int	empty_line(char *str)
{
	while (is_blank(*str))
		str ++;
	if (*str == 0)
		return (1);
	return (0);
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
