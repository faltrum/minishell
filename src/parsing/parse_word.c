#include "minishell.h"

int	get_length(char *str, int *i)
{
	char	quote;

	quote = 0;
	while (str[*i])
	{
		if (quote == 0 && (is_meta(str[*i]) || is_blank(str[*i])))
			break ;
		else if (str[*i] == '\'' || str[*i] == '"')
		{
			if (quote == 0)
				quote = str[*i];
			else if ((str[*i]) == quote)
				quote = 0;
			(*i)++;
		}
		else if ((quote == 0 && is_regular(str[*i])) || quote)
			(*i)++;
		else
			return (perr(-1, 1,"minishell: syntax error unmatched quote\n"));
	}
	if (quote != 0)
		return (perr(-1, 1, "minishell: syntax error unmatched quote\n"));
	return (0);
}

int	add_word(char *str, int *i, char **word)
{
	int		p0;

	p0 = *i;
	if (get_length(str, i) == -1)
		return (0);
	*word = ft_substr(str, p0, *i - p0);
	if (!*word)
		return (perr(0, 1, "minishell: memory error\n"));
	return (1);
}

int	parse_word(char *str, int *i, t_word_list **words)
{
	t_word_list	*word;

	word = allocate_last_node(words);
	if (!word)
		return (0);
	return (add_word(str, i, &(word->word)));
}
