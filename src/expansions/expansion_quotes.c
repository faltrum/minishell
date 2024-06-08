#include "minishell.h"

void	remove_quotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] == DQUOTE || str[i] == QUOTE)
		{
			j = i;
			while (str[j])
			{
				str[j] = str[j + 1];
				j ++;
			}
		}
		else
			i ++;
	}
}

void	sanitize_list(t_word_list *node)
{
	while (node)
	{
		if (*(node->word) == 0)
		{
			free(node->word);
			node->word = NULL;
		}
		else
			remove_quotes(node->word);
		node = node->next;
	}
}

void	hide_quotes(char *str)
{
	int quoted;

	quoted = 0;
	while (*str)
	{
		if (*str == '\'' && quoted != DQUOTED)
		{
			*str = QUOTE;
			quoted ^= QUOTED;
		}
		else if (*str == '"' && quoted != QUOTED)
		{
			*str = DQUOTE;
			quoted ^= DQUOTED;
		}
		str ++;
	}
}

void	update_quote_flag(char *str , int *i, int *flags)
{
	if (str[*i] == QUOTE)
		(*flags) ^= QUOTED;
	else if (str[*i] == DQUOTE)
		(*flags) ^= DQUOTED;
	(*i) ++;
}
