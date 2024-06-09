/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:58:25 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/09 03:59:27 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pipeline_command(t_simple_command *command, \
int fds[2], t_var *var, int islast)
{
	int	exit;

	if (fds[0] != -1 && dup2(fds[0], STDIN_FILENO) == -1)
		perror("minishell");
	if (fds[0] != -1)
		close (fds[0]);
	if (islast)
	{
		if (dup2(var->stdfds[1], STDOUT_FILENO) == -1)
			perror ("minishell");
		exit = execute_simple_command(command, \
			var, WAIT | RESTOREFD | SUBSHELL);
	}
	else
	{
		if (pipe(fds) == -1)
			perror("minishell");
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			perror("minishell");
		exit = execute_simple_command(command, var, SUBSHELL);
		close(fds[1]);
	}
	return (exit);
}

int	execute_pipeline(t_command *node, t_var *var)
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
