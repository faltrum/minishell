/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:56:39 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/20 10:49:58 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	sort_directories(t_word_list *directories)
{
	t_word_list	*node;
	t_word_list	*head;
	char		*aux;

	head = directories;
	while (directories)
	{
		node = head;
		while (node->next)
		{
			if (ft_strcmp(node->word, node->next->word) > 0)
			{
				aux = node->word;
				node->word = node->next->word;
				node->next->word = aux;
			}
			node = node->next;
		}
		directories = directories->next;
	}
}

int	get_directories(t_word_list **directories)
{
	DIR				*stream;
	struct dirent	*dir;
	t_word_list		*node;

	stream = opendir(".");
	if (!stream)
		return (ft_err(-1, ERR_PATHNAME_OPENDIR, strerror(errno), 0));
	dir = readdir(stream);
	while (dir)
	{
		if (ft_strcmp(dir->d_name, ".") && ft_strcmp(dir->d_name, ".."))
		{
			node = allocate_last_node(directories);
			if (!node)
				continue ;
			node->word = ft_strdup(dir->d_name);
			if (!node->word)
				ft_err(0, ERR_MALLOC, 0, 0);
		}
		dir = readdir(stream);
	}
	closedir(stream);
	sort_directories(*directories);
	return (0);
}
