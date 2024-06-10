/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:01:19 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/10 23:31:27 by kseligma         ###   ########.fr       */
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
		return (ft_err(0, "exit", s, "numeric argument required"));
	return (1);
}

int ft_exit(t_var *var, char **params) // FREE DE COSAS
{
	printf("exit\n");
	if (params[1] && params[2])
		return (ft_err(EXIT_FAILURE, "exit" ,"too many arguments", 0));
	if (params[1])
	{
		if (!is_num(params[1]))
			return (2);
		exit ((unsigned char) ft_atoi(params[1]));
	}
	exit(var->exit);
}
