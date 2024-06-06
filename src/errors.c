/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseus <kseus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:08 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/03 06:56:23 by kseus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	perr(int return_value, int argc, ...)
{
	int		i;
	va_list	ap;
	char	*str;

	va_start(ap, argc);
	i = 0;
	while (i < argc)
	{
		str = va_arg(ap, char *);
		write(2, str, ft_strlen(str));
		i ++;
	}
	va_end(ap);
	return (return_value);
}

int	exec_error(char *command, char *error_msg)
{
	write(2, command, ft_strlen(command));
	write(2, ": ", 2);
	write(2, error_msg, ft_strlen(error_msg));
	return (EXIT_FAILURE);
}

void	stx_error(char *error_msg)
{
	int	fd;

	fd = dup(1);
	dup2(2, 1);
	printf("%s", error_msg);
	dup2(fd, 1);
}

void	stx_error_op(char *error_msg, char op)
{
	int	fd;

	fd = dup(1);
	dup2(2, 1);
	printf("%s '%c'\n", error_msg, op);
	dup2(fd, 1);
}
