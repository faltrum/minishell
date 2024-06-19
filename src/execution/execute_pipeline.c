/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:58:25 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/19 16:25:21 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	kill_pipeline(t_var *var, int fds[2])
{
	var->kill = 1;
	if (fds[0] > -1)
		close(fds[0]);
	if (fds[1] > -1)
		close(fds[1]);
	if (var->fds_list[2] > -1)
		close(var->fds_list[2]);
	var->fds_list[2] = -1;
	return (EXIT_FAILURE);
}

int	exe_pipeline_command(t_simple_command *command, \
int fds[2], t_var *var, int islast)
{
	int	exit;

	if (fds[0] != -1 && dup2(fds[0], STDIN_FILENO) == -1)
		return (ft_err(-1, strerror(errno), "killing pipeline", 0));
	if (fds[0] != -1)
		close(fds[0]);
	if (islast)
	{
		if (dup2(var->fds_list[1], STDOUT_FILENO) == -1)
			return (ft_err(-1, strerror(errno), "killing pipeline", 0));
		exit = exe_simple_command(command, \
			var, WAIT | RESTOREFD | SUBSHELL);
	}
	else
	{
		if (pipe(fds) == -1)
			return (ft_err(-1, strerror(errno), "killing pipeline", 0));
		else
			var->fds_list[2] = fds[0];
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			return (ft_err(-1, strerror(errno), "killing pipeline", 0));
		close(fds[1]);
		exit = exe_simple_command(command, var, SUBSHELL);
	}
	return (exit);
}

int	exe_pipeline(t_command *node, t_var *var)
{
	int	fds[2];
	int	ret;

	fds[0] = -1;
	fds[1] = -1;
	var->fds_list[2] = -1;
	while (node->type == cm_connection)
	{
		if (exe_pipeline_command(node->value.connection->first->value.simple, \
			fds, var, 0) == -1 || var->kill == 1)
			return (kill_pipeline(var, fds));
		node = node->value.connection->second;
	}
	ret = exe_pipeline_command(node->value.simple, fds, var, 1);
	if (ret == -1)
		return (kill_pipeline(var, fds));
	return (ret);
}
