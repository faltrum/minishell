#include "../../includes/minishell.h"

static void	free_local_args(t_redirect **redir, t_word_list **words)
{
//	free_word_list(*words, 1);
	free_redirects(*redir);
	*redir = NULL;
	*words = NULL;
}

void	parse_words_and_redirects(char *str, \
t_redirect **redir, t_word_list **words)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	while (res && str[i])
	{
		if (search_redir(str, &i))
		{
			res = parse_redir(str, &i, redir);
			if (res && (*redir)->type == here_doc)
				res = do_here_doc(*redir);
		}
		else if (search_word(str, &i))
			res = parse_word(str, &i, words);
		else if (str[i] && res) 
		{
			printf("Syntax error: Unexpected token %c\n", str[i]);
			res = 0;
		}
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
		words = words->next;
		count ++;
	}
	return (count);
}

char	**list_to_arr(t_word_list *words)
{
	int		count;
	char	**arr_words;

	arr_words = malloc((count_list_args(words) + 1) * sizeof(*arr_words));
	if (!arr_words)
	{
		printf("Malloc error\n");
		return (0);
	}
	count = 0;
	while (words)
	{
		arr_words[count] = words->word;
		words = words->next;
		count++;
	}
	arr_words[count] = NULL;
	//free_word_list(words, 0);
	return (arr_words);
}

int	pre_parse_words_and_redirects(char* str, t_simple_command *command)
{
	t_word_list	*words;

	words = NULL;
	parse_words_and_redirects(str, &command->redirects, &words);
	if (!command->redirects && !words)
		return (0);
	command->words = words;
	return (1);
}
