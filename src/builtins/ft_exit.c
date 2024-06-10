/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:01:19 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/09 04:24:43 by kseligma         ###   ########.fr       */
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
		 str++ ;
	if (*str)
		return (perr(0, 3, "minishell: exit: ", s, ": numeric argument required\n"));
	return (1);
}

int ft_exit(t_var *var, char **params) // FREE DE COSAS
{
	printf("exit\n");
	if (params[1] && params[2])
		return (perr(EXIT_FAILURE, 1, "minishell: exit: too many arguments\n"));
	if (params[1])
	{
		if (!is_num(params[1]))
			return (2);
		exit ((unsigned char) ft_atoi(params[1]));
	}
	exit(var->exit);
}
