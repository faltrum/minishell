#include "minishell.h"

int	get_expanded_list(t_var *var, char *word, t_word_list **head)
{
	*head = NULL;
	hide_quotes(word);
	if (parameter_expansion(var, &word) == -1)
		return (-1);
	if (word_splitting(word, head) == -1)
		return (-1);
	if (pathname_expansion(*head) == -1)
		return (-1);
	sanitize_list(*head);
	return (0);
}

static int	expand_argument(t_var *var, t_word_list *node, t_word_list *next)
{
	t_word_list	*new;

	if (get_expanded_list(var, node->word, &new) == -1)
		return (-1);
	// free(node->word);
	last_word_node(new)->next = next;
	node->word = new->word;
	node->next = new->next;
	free(new);
	return (0);
}

static int	expand_redirection(t_var *var, t_redirect *redirect)
{
	t_word_list *node;

	node = NULL;
	if (redirect->type == here_doc)
		do_here_doc(var, redirect);
	else if (get_expanded_list(var, redirect->word, &node) == -1)
		return (-1);
	redirect->expanded = node;
	return (0);
}

int	expand_command_lists(t_simple_command *command, t_var *var)
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
			return (EXIT_FAILURE);
		redirects = (redirects)->next;
	}
	return (EXIT_SUCCESS);
}
