/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:55:36 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/17 11:26:07 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	update_quote_flag_parsing(char c, int *flag)
{
	if (c == '\'' && !(*flag & DQUOTED))
		*flag ^= QUOTED;
	else if (c == '"' && !(*flag & QUOTED))
		*flag ^= DQUOTED;
}

int	is_blank(char c)
{
	if (c && ft_strchr(BLANK_CHARS, c))
		return (1);
	return (0);
}

int	is_meta(char c)
{
	if (ft_strchr(META_CHARS, c) || is_blank(c))
		return (1);
	return (0);
}

int	is_regular(char c)
{
	return (!is_meta(c));
}

int	is_identifier(char c, int first)
{
	if (first)
		return (ft_isalpha(c) || c == '_');
	else
		return (ft_isalnum(c) || c == '_');
}
