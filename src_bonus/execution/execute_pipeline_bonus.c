/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:58:25 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/17 11:26:08 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	execute_pipeline_command(t_simple_command *command, \
int fds[2], t_var *var, int islast)
{
	int	exit;

	if (fds[0] != -1 && dup2(fds[0], STDIN_FILENO) == -1)
		perror(PROGRAM_NAME);
	if (fds[0] != -1)
		close(fds[0]);
	if (islast)
	{
		if (dup2(var->fds_list[1], STDOUT_FILENO) == -1)
			perror (PROGRAM_NAME);
		exit = exe_simple_command(command, \
			var, WAIT | RESTOREFD | SUBSHELL);
	}
	else
	{
		if (pipe(fds) == -1)
			perror(PROGRAM_NAME);
		else
			var->fds_list[2] = fds[0];
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			perror(PROGRAM_NAME);
		close(fds[1]);
		exit = exe_simple_command(command, var, SUBSHELL);
	}
	return (exit);
}

int	exe_pipeline(t_command *node, t_var *var)
{
	int	fds[2];

	fds[0] = -1;
	while (node->type == cm_connection)
	{
		execute_pipeline_command(node->value.connection->first->value.simple, \
			fds, var, 0);
		node = node->value.connection->second;
	}
	return (execute_pipeline_command(node->value.simple, fds, var, 1));
}
