/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:25:57 by oseivane          #+#    #+#             */
/*   Updated: 2024/05/23 13:26:06 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_normal_word(char *str, int *i, char **word)
{
	int	p0;

	p0 = *i;
	while (wordchar(str[*i]))
		(*i)++;
	*word = ft_substr(str, p0, *i - p0);
	if (!*word)
	{
		printf("Malloc error\n");
		return (0);
	}
	return (1);
}

int	add_quoted_word(char *str, int *i, char **word, char c)
{
	int	p0;

	(*i)++;
	p0 = *i;
	while (str[(*i)] != c && str[(*i)])
		(*i)++;
	if (!str[*i])
	{
		printf("Syntax error, unmatched %c\n", c);
		return (0);
	}
	(*i)++;
	*word = ft_substr(str, p0, *i - p0 - 1);
	if (!*word)
	{
		printf("Malloc error\n");
		return (0);
	}
	return (1);
}

t_word_list	*last_word(t_word_list **words)
{
	t_word_list	*move;

	move = *words;
	if (move == NULL)
	{
		*words = calloc(1, sizeof(**words));
		if (!*words)
			return (NULL);
		return (*words);
	}
	else
	{
		while (move->next)
			move = move->next;
		move->next = calloc(1, sizeof(**words));
		if (!move->next)
			return (NULL);
		return (move->next);
	}
}

int	parse_word(char *str, int *i, t_word_list **words)
{
	t_word_list	*word;

	word = last_word(words);
	if (!word)
		return (0);
	if (str[*i] == '\'' || str[*i] == '"')
	{
		if (str[*i] == '\'')
			word->type = quoted;
		else
			word->type = dquoted;
		return (add_quoted_word(str, i, &(word->word), str[*i]));
	}
	else
	{
		word->type = single;
		return (add_normal_word(str, i, &(word->word)));
	}
	return (0);
}
