/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:55:52 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/11 01:59:40 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_word_list	*allocate_last_node(t_word_list **words)
{
	t_word_list	*move;

	move = *words;
	if (*words == NULL)
	{
		ft_errloc(sizeof(t_word_list), 1, (void **) words);
		return (*words);
	}
	else
	{
		move = last_word_node(*words);
		ft_errloc(sizeof(t_word_list), 1, (void **) &(move->next));
		return (move->next);
	}
}

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
			return (ft_err(-1, ERR_UNMATCHED_QUOTE, 0, 0));
	}
	if (quote != 0)
		return (ft_err(-1, ERR_UNMATCHED_QUOTE, 0, 0));
	return (0);
}

int	add_word(char *str, int *i, char **word)
{
	int		p0;

	p0 = *i;
	if (get_length(str, i) == -1)
		return (-1);
	*word = ft_substr(str, p0, *i - p0);
	if (!*word)
		return (ft_err(-1, ERR_MALLOC, 0, 0));
	return (0);
}

int	parse_word(char *str, int *i, t_word_list **words)
{
	t_word_list	*word;

	word = allocate_last_node(words);
	if (!word)
		return (-1);
	return (add_word(str, i, &(word->word)));
}
