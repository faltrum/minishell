/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:01:27 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/17 08:14:42 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_flag(char **params, int *ind, int *flag)
{
	int	j;

	while (params[*ind])
	{
		j = 0;
		if (params[*ind][j] == '-')
			j ++;
		else
			break ;
		while (params[*ind][j] == 'n')
			j ++;
		if (params[*ind][j])
			break ;
		(*flag)++;
		(*ind)++;
	}
}

int	ft_echo(t_var *var, char **params)
{
	int	ind;
	int	flag;

	(void) var;
	flag = 0;
	ind = 1;
	check_flag(params, &ind, &flag);
	while (params[ind])
	{
		if (ind > 1 + flag)
			if (printf(" ") == -1)
				return (EXIT_FAILURE);
		if (printf("%s", params[ind]) == -1)
			return (EXIT_FAILURE);
		ind ++;
	}
	if (!flag && printf("\n") == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
