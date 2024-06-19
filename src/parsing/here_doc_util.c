/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:27:59 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/19 16:28:08 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_quotes_hdoc(char *str)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	found = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			found = 1;
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
	return (found);
}
