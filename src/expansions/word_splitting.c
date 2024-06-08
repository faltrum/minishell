#include "minishell.h"

static int	 add_word_to_list(t_word_list **head, char *str, int *i, int flags)
{
	int		end;
	t_word_list *node;

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
	{
		free(node);
		return (-1); // ERROR MESSAGE
	}
	*i = end;
	return (0);
}

int	word_splitting(char *str, t_word_list **head)
{
	int	i;
	int	flags;

	flags = 0;
	i = 0;
	while (str[i])
	{
		if (!is_blank(str[i]) && add_word_to_list(head, str, &i, flags) == -1)
			return (-1);
		if (str[i] == QUOTE || str[i] == DQUOTE)
			update_quote_flag(str, &i, &flags);
		else
			i ++;
	}
	if (add_word_to_list(head, str, &i, flags) == -1)
		return (-1);
	return (0);
}
