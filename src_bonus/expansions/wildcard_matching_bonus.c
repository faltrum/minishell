/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_matching_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:35:35 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/17 11:26:08 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	match_everything(char *str, int flag)
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

static int	word_matches(char *wild, char *match, int i)
{
	if (wild[i] == match[i] || match_everything(wild + i, 0))
		return (1);
	return (0);
}

static void	update_pathname_flag(char **wild, int *i, int *flag)
{
	if ((*wild)[*i] == QUOTE)
		(*flag) ^= QUOTED;
	else if ((*wild)[*i] == DQUOTE)
		(*flag) ^= DQUOTED;
	(*wild)++;
	(*i)--;
}

int	wildcard_matches(char *wild, char *match, int flag, int j)
{
	int	i;

	i = 0;
	while (((wild[i] && match[i]) || flag))
	{
		if (wild[i] == QUOTE || wild[i] == DQUOTE)
			update_pathname_flag(&wild, &i, &flag);
		else if (!(flag & QUOTED) && !(flag & DQUOTED) && wild[i] == '*')
		{
			j = 0;
			if (match_everything(wild + i, 0))
				return (1);
			while (match[i + j])
			{
				if (wildcard_matches(wild + i + 1, match + i + j, flag, 0))
					return (1);
				j ++;
			}
			return (0);
		}
		else if (wild[i] != match[i])
			return (0);
		i ++;
	}
	return (word_matches(wild, match, i));
}
