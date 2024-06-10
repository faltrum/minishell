/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:56:55 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/10 08:44:35 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_expanded_list(t_var *var, char **word, t_word_list **head)
{
	hide_quotes(*word);
	if (parameter_expansion(var, word) == -1)
		return (-1);
	if (word_splitting(*word, head) == -1)
		return (-1);
	if (pathname_expansion(*head) == -1)
		return (-1);
	sanitize_list(*head);
	return (0);
}

static int	expand_argument(t_var *var, t_word_list *node, t_word_list *next)
{
	t_word_list	*new;

	new = NULL;
	if (get_expanded_list(var, &(node->word), &new) == -1)
		return (-1);
	last_word_node(new)->next = next;
	free(node->word);
	node->word = new->word;
	node->next = new->next;
	free(new);
	return (0);
}

static int	expand_redirection(t_var *var, t_redirect *redirect)
{
	t_word_list	*node;
	int			here_exit;

	node = NULL;
	if (redirect->type == here_doc)
	{
		g_sigint = SINT_HEREDOC;
		here_exit = do_here_doc(var, redirect);
		if (g_sigint == SINT_HEREDOC)
			g_sigint = SINT_OFF;
		if (g_sigint == SINT_ON)
			return (-1);
		return (here_exit);
	}
	else if (get_expanded_list(var, &(redirect->word), &node) == -1)
		return (-1);
	redirect->expanded = node;
	return (0);
}

int	expand_command_list(t_simple_command *command, t_var *var)
{
	t_word_list	*node;
	t_word_list	*next;
	t_redirect	*redirects;

	node = command->words;
	while (node)
	{
		next = node->next;
		if (expand_argument(var, node, next) == -1)
			return (-1);
		node = next;
	}
	redirects = command->redirects;
	while (redirects)
	{
		if (expand_redirection(var, redirects) == -1)
			return (-1);
		redirects = (redirects)->next;
	}
	return (0);
}
