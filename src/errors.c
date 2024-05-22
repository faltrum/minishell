/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:08 by oseivane          #+#    #+#             */
/*   Updated: 2024/05/20 21:04:30 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_error(char *command, char *error_msg)
{
	int	fd;

	fd = dup(1);
	dup2(2, 1);
	printf("%s: %s", command, error_msg);
	dup2(fd, 1);
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
