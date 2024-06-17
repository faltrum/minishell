/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:01:19 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/17 08:14:50 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_num(char *str)
{
	char	*s;

	s = str;
	if (!*str)
		return (ft_err(0, EXIT, s, ERR_NUMERIC_ARG));
	if (*str == '+' || *str == '-')
		str ++;
	while (ft_isdigit(*str))
		str ++;
	if (*str)
		return (ft_err(0, EXIT, s, ERR_NUMERIC_ARG));
	return (1);
}

static void	actual_exit(t_var *var, int ex)
{
	free_command_tree(var->command_tree);
	minishell_cleanup(var);
	exit ((unsigned char) ex);
}

int	ft_exit(t_var *var, char **params)
{
	write(1, STR_EXIT, ft_strlen(STR_EXIT));
	if (!params[1])
		actual_exit(var, var->exit);
	if (!is_num(params[1]))
		actual_exit(var, 2);
	if (params[2])
		ft_err(EXIT_FAILURE, EXIT, ERR_TOO_MANY_ARGS, 0);
	else
		actual_exit(var, ft_atoi(params[1]));
	actual_exit(var, 1);
	return (EXIT_SUCCESS);
}
