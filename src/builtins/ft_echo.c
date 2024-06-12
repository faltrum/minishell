/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:01:27 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/11 06:12:23 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_flag(char **params, int *ind, int *flag)
{
	int	j;

	while (params[*ind])
	{
		// If is flag, set flag to 1, advance ind. If is not flag, break
		j = 0;
		if (params[*ind][j] == '-')
			j ++;
		else
			break ;
		while (params[*ind][j] == 'n')
			j ++;
		if (params[*ind][j])
			break ;
		(*flag) ++;
		(*ind) ++;
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
