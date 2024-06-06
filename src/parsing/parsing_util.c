#include "minishell.h"

t_bool	is_blank(char c)
{
	if (c && ft_strchr(" \t", c))
		return (TRUE);
	return (FALSE);
}

t_bool	is_meta(char c)
{
	if (ft_strchr("|&()<>", c) || is_blank(c))
		return (TRUE);
	return (FALSE);
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

t_word_list	*allocate_last_node(t_word_list **words)
{
	t_word_list	*move;

	move = *words;
	if (move == NULL)
	{
		*words = ft_calloc(1, sizeof(t_word_list));
		return (*words);
	}
	else
	{
		move = last_word_node(*words);
		move->next = ft_calloc(1, sizeof(t_word_list));
		return (move->next);
	}
}
