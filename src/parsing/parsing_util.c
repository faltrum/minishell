/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:55:36 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/09 15:33:40 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_blank(char c)
{
	if (c && ft_strchr(" \t", c))
		return (1);
	return (0);
}

int	is_meta(char c)
{
	if (ft_strchr("|&()<>", c) || is_blank(c))
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
