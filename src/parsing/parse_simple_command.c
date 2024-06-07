#include "minishell.h"

int	allocate_simple_command(t_command **node)
{
	*node = ft_calloc(1 ,sizeof(**node));
	if (!*node)
		return (perr(-1, 1, "minishell: memory error\n"));
	(*node)->value.simple = ft_calloc(1, sizeof(*(*node)->value.simple));
	if (!(*node)->value.simple)
	{
		free(*node);
		return (perr(-1, 1, "minishell: memory error\n"));
	}
	return (0);
}

t_command	*parse_simple_command(char* str)
{
	t_command	*node;
	t_word_list	*words;
	t_redirect	*redirects;

	words = NULL;
	redirects = NULL;
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
