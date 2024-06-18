/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:01:19 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/18 10:59:39 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	too_long(char *str)
{
	int		i;
	char	*max;
	int		len;

	i = 0;
	len = 0;
	while (is_blank(str[i]))
		i ++;
	if (str[i] == '-')
		max = "9223372036854775808";
	else
		max = "9223372036854775807";
	if (str[i] == '-' || str[i] == '+')
		i ++;
	while (str[i] == '0')
		i ++;
	while (ft_isdigit(str[i + len]))
		len++;
	if ((len == 19 && ft_strncmp(str + i, max, len) > 0)
		|| len > 19)
		return (1);
	return (0);
}

static int	is_num(char *str)
{
	while (is_blank(*str))
		str ++;
	if (*str == '+' || *str == '-')
		str ++;
	if (!*str)
		return (0);
	while (ft_isdigit(*str))
		str ++;
	while (is_blank(*str))
		str ++;
	if (*str)
		return (0);
	return (1);
}

static void	actual_exit(t_var *var, int ex)
{
	free_command_tree(var->command_tree);
	minishell_cleanup(var);
	exit ((unsigned char) ex);
}

int	try_numeric_exit(t_var *var, char *str)
{
	ft_err(2, EXIT, str, ERR_NUMERIC_ARG);
	while (is_blank(*str))
		str ++;
	if (*str == '+' || *str == '-')
		str ++;
	while(ft_isdigit(*str))
		str ++;
	while (is_blank(*str))
		str ++;
	if (*str)
		return (2);
	actual_exit(var, 2);
	return (EXIT_SUCCESS);
}

int	ft_exit(t_var *var, char **params)
{
	char *err;

	err = NULL;
	if (isatty(STDERR_FILENO))
		write(2, STR_EXIT, ft_strlen(STR_EXIT));
	if (params[1] && params[2])
		err = ERR_TOO_MANY_ARGS;
	else if (params[1] && (!is_num(params[1]) || too_long(params[1])))
		return (try_numeric_exit(var, params[1]));
	if (!err && params[1])
		actual_exit(var, ft_atol(params[1]));
	else if (!err)
		actual_exit(var, var->exit);
	if (!is_num(params[1]))
	{
		ft_err(2, EXIT, params[1], ERR_NUMERIC_ARG);
		actual_exit(var, 2);
	}
	ft_err(2, EXIT, ERR_TOO_MANY_ARGS, 0);
	return (EXIT_FAILURE);
}

// Many args first not numeric --> Exit, print many args
// Many args first numeric  --> not exit, print many args
