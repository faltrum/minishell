/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 07:28:14 by kseligma          #+#    #+#             */
/*   Updated: 2024/05/20 17:20:14 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	ft_strn(char *s, char c, size_t n)
{
	size_t	ind;

	ind = 0;
	while (ind < n || n == 0)
	{
		if (s[ind] == c)
			return (1);
		if (s[ind] == 0)
			return (0);
		ind ++;
	}
	return (0);
}

char	*manage_left(char **left, char op)
{
	char	*aux;

	if (op == 1)
	{
		aux = 0;
		if (!(*left))
		{
			aux = malloc(1);
			if (aux)
				aux[0] = 0;
			return (aux);
		}
		return (*left);
	}
	else
	{
		free (*left);
		*left = 0;
		return (0);
	}
}

void	ft_cpy(char *dst, char *src, size_t n)
{
	size_t	count;

	count = 0;
	while (count < n)
	{
		dst[count] = src[count];
		count ++;
	}
	dst[count] = 0;
}
