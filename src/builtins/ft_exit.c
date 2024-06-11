/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:01:19 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/11 02:05:30 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_num(char *str)
{
	char	*s;

	s = str;
	while (*str == ' ')
		str ++;
	if (*str == '+' || *str == '-')
		str ++;
	while (ft_isdigit(*str))
		str ++;
	if (*str)
		return (ft_err(0, EXIT, s, ERR_NUMERIC_ARG));
	return (1);
}

int	ft_exit(t_var *var, char **params) // FREE DE COSAS
{
	printf(STR_EXIT);
	if (params[1] && params[2])
		return (ft_err(EXIT_FAILURE, EXIT, ERR_TOO_MANY_ARGS, 0));
	if (params[1])
	{
		if (!is_num(params[1]))
			return (2);
		exit ((unsigned char) ft_atoi(params[1]));
	}
	exit(var->exit);
}
