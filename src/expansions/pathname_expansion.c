# include "minishell.h"

int	match_everything(char *str, int flag)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (str[i])
	{
		if (str[i] == QUOTE || str[i] == DQUOTE)
			update_quote_flag(str, &i, &flag);
		else if (!(flag & QUOTED) && !(flag & DQUOTED) && str[i++] == '*')
			found = 1;
		else
			return (0);
	}
	return (found);
}

int	wildcard_matches(char *wild, char *match, int flag)
{
	int	i;
	int	j;

	i = 0;
	while ((wild[i] && match[i]) || flag)
	{
		if (wild[i] == QUOTE || wild[i] == DQUOTE)
		{
			update_quote_flag(wild, &i, &flag); // Create custom
			wild ++;
			i --;
		}
		else if (!(flag & QUOTED) && !(flag & DQUOTED) && wild[i] == '*')
		{
			j = 0;
			if (match_everything(wild + i, 0))
				return (1);
			while (match[i + j])
			{
				if (wildcard_matches(wild + i + 1, match + i + j, flag))
					return (1);
				j ++;
			}
			return (0);
		}
		else if (wild[i] == match[i])
			i ++;
		else if (wild[i] != match[i])
			return (0);
	}
	if (wild[i] == match[i] || match_everything(wild + i, 0))
		return (1);
	return (0);
}

int	expand_pathname(t_word_list *next, t_word_list *node, t_word_list *directories)
{
	t_word_list	*matches;
	t_word_list *head;

	head = NULL;
	while (directories)
	{
		if (node->word  && *(node->word) && wildcard_matches(node->word, directories->word, 0))
		{
			matches = allocate_last_node(&head);
			matches->word = ft_strdup(directories->word);
		}
		directories = directories->next;
	}
	if (head)
	{
		matches->next = next;
		node->word = head->word;
		node->next = head->next;
		free(head);
	}
	return (1);
}

int	should_be_expanded(char *str)
{
	int	i;
	int	flags;

	i = 0;
	flags = 0;
	while (str[i])
	{
		if (str[i] == QUOTE || str[i] == DQUOTE)
			update_quote_flag(str, &i, &flags);
		else if (!(flags & QUOTED) && !(flags & DQUOTED) && str[i] == '*')
			return (1);
		else
			i ++;
	}
	return (0);
}

int	pathname_expansion(t_word_list *node)
{
	t_word_list	*next;
	t_word_list	*directories;

	directories = NULL;
	if (get_directories(&directories) == -1)
		return (-1);
	(void) node;
	while (node)
	{
		next = node->next;
		if (should_be_expanded(node->word))
			expand_pathname(next, node, directories);
		node = next;
	}
	return (0);
}
