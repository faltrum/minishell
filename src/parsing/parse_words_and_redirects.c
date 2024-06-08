#include "minishell.h"

static void	free_local_args(t_redirect **redir, t_word_list **words)
{
	free_word_list(*words, 1);
	free_redirects(*redir);
	*redir = NULL;
	*words = NULL;
}

void	parse_words_and_redirects(char *str, \
t_redirect **redir, t_word_list **words)
{
	int			i;
	int			res;

	i = 0;
	res = 1;
	while (res && str[i])
	{
		if (search_redir(str, &i))
			res = parse_redir(str, &i, redir);
		else if (search_word(str, &i))
			res = parse_word(str, &i, words);
		else if (res && str[i])
			res = perr(0, 1, "minishell: syntax error near unexpected token\n");
	}
	if (!res)
		free_local_args(redir, words);
}

int	count_list_args(t_word_list *words)
{
	int	count;

	count = 0;
	while (words)
	{
		if (words->word)
			count ++;
		words = words->next;
	}
	return (count);
}

char	**list_to_arr(t_word_list *words)
{
	int		count;
	char	**arr_words;

	arr_words = malloc((count_list_args(words) + 1) * sizeof(*arr_words));
	if (!arr_words)
		return ((char **) perr(0, 1, "minishell: memory error\n"));
	count = 0;
	while (words)
	{
		if (words->word)
		{
			arr_words[count] = words->word;
			count++;
		}
		words = words->next;
	}
	arr_words[count] = NULL;
	//free_word_list(words, 0);
	return (arr_words);
}
