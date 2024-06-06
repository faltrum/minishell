#include "minishell.h"

int	set_flag_error(int *flags)
{
	*flags ^= EXP_ERR;
	return (-1);
}

int	allocate_expanded_string(char **str, char *word, char *value, char *key)
{
	*str = ft_calloc(sizeof(char), 1 + ft_strlen(word) + ft_strlen(value));
	if (!*str)
	{
		free(value);
		free(key);
		return (perr(-1, 1, "minishell: expansion: memory error\n"));
	}
	return (0);
}

int	expand_word(t_var *var, char **word, int *i, int *flags)
{
	char	*key;
	char	*value;
	char	*expanded_string;
	int		value_len;
	int		key_len;

	if (get_key_and_value(&(*word)[*i], &key, &value, var) == -1)
		return (set_flag_error(flags));
	if (allocate_expanded_string(&expanded_string, *word, value, key) == -1)
		return (set_flag_error(flags));
	value_len = ft_strlen(value);
	key_len = ft_strlen(key);
	ft_strlcat(expanded_string, *word, *i + 1);
	ft_strlcat(expanded_string, value, value_len + *i + 1);
	ft_strlcat(expanded_string, &(*word)[*i + key_len + 1], ft_strlen(&(*word)[*i + key_len + 1]) + ft_strlen(expanded_string) + 1);
	free(value);
	free(key);
//	free(*word);
	*word = expanded_string;
	if (value_len)
		*flags ^= EXPANDED;
	return (value_len);
}

// MOVE THE START JUMPING ALL SPACES OR UNTIL IT REACHES CURRENT
// COPY FROM START TO THIS PLACE (WE ARE ON SPACE OR END) - IF NOT EMPTY (IF HEADS ARENT EQUAL) - IF EMPTY, ADVANCE HEAD ONE.
// MOVE THE CURRENT POINTER ALL THE WAY TO THE START OF NEXT (SKIP SPACES)
void	 add_word_to_list(t_word_list **head, char *word, int i[4], int *flags)
{
	char		*str;
	t_word_list	*node;

	while (word[i[1]] == ' ' && i[0] > i[1])
		i[1] ++;
	str = NULL;
	if (i[1] != i[0])
	{
		str = ft_substr(word, i[1], i[0] - i[1]);
		if (!str)
		{
			set_flag_error(flags);
			perr(-1, 1, "minishell: expansion: memory error\n");
		}
	}
	node = allocate_last_node(head);
	if (!node)
	{
		free(str);
		set_flag_error(flags);
		perr(-1, 1, "minishell: expansion: memory error\n");
	}
	else
		node->word = str;
	i[1] = i[0];
	advance_one(word, &i[0], &i[2], flags);
}

int	get_expanded_list(t_var *var, char *word, t_word_list **head) // SHOULDNT RETURN NULL // SOLVE FOR "" SHOULD DO EMPTY STRING, and "SPACES"
{
	int			i[4]; // 0 is word index, 1 is end of prev word, 2 is expansion length
	int			flags;

	*head = NULL;
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	flags = 0;
	while (word[i[0]] && !(flags & EXP_ERR))
	{
		if (!(flags & EXPANDED) && (word[i[0]] == '\'' || word[i[0]] == '"'))
			remove_quote(word, i, &flags);
		else if (!(flags & QUOTED) && !(flags & DQUOTED) && word[i[0]] == ' ')
			add_word_to_list(head, word, i, &flags);
		else if (!(flags & QUOTED) && !(flags & EXPANDED) && word[i[0]] == '$' && ((ft_isalpha(word[i[0] + 1]) || word[i[0] + 1] == '?') || word[i[0] + 1] == '_'))
			i[2] = expand_word(var, &word, &i[0], &flags);
		else
			advance_one(word, &i[0], &i[2], &flags);
	}
	if (!(flags & EXP_ERR))
		add_word_to_list(head, word, &i[0], &flags);
	return (-(flags & EXP_ERR));
}

int	expand_node(t_var *var, t_word_list *node, t_word_list *next)
{
	t_word_list *new;

	if (get_expanded_list(var, node->word, &new) == -1)
		return (-1);
	// free(node->word);
	last_word_node(new)->next = next;
	node->word = new->word;
	node->next = new->next;
	free(new);
	return (0);
}

int		expand_redirection(t_var *var, t_redirect *redirect)
{
	t_word_list *node;

	if (get_expanded_list(var, redirect->word, &node) == -1)
		return (-1);
//	free(redirect->word);
	if (node && node->next)
	{
		perr(0, 1, "minishell: ambiguos redirection\n");
		return (-1);
	}
	else
		redirect->word = node->word;
	return (0);
}

int	execute_expansions(t_simple_command *command, t_var *var)
{
	t_word_list	*node;
	t_word_list	*next;
	t_redirect	*redirects;

	node = command->words;
	while (node)
	{
		next = node->next;
		if (expand_node(var, node, next) == -1)
			return (-1);
		node = next;
	}
	redirects = command->redirects;
	while (redirects)
	{
		if (redirects->type != here_doc && expand_redirection(var, redirects) == -1)
			return (EXIT_FAILURE);
		redirects = (redirects)->next;
	}
	return (EXIT_SUCCESS);
}
