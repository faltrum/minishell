/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_simple_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:58:22 by oseivane          #+#    #+#             */
/*   Updated: 2024/05/23 12:58:35 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	allocate_simple_command(t_command **node)
{
	*node = calloc(1,sizeof(**node));
	if (!*node)
	{
		printf("Memory error\n");
		return (0);
	}
	(*node)->value.simple = calloc(1, sizeof(*(*node)->value.simple));
	if (!(*node)->value.simple)
	{
		free(*node);
		printf("Memory error\n");
		return (0);
	}
	return (1);
}

t_command	*create_simple_command(char *str)
{
	t_command	*node;

	if (!allocate_simple_command(&node))
		return (NULL);
	node->type = cm_simple;
	if (!pre_parse_words_and_redirects(str, node->value.simple))
	{
		free_command(node);
		return (NULL);
	}
	return (node);
}
