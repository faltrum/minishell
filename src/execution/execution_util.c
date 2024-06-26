/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:27:12 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/11 01:40:57 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_fds(int fds[2])
{
	if (dup2(fds[0], STDIN_FILENO) == -1)
		perror(ERR_STDIN_PERROR);
	if (dup2(fds[1], STDOUT_FILENO) == -1)
		perror(ERR_STDOUT_PERROR);
}

int	is_builtin(t_var *var, char *command)
{
	int	i;

	i = 0;
	while (var->act && var->act[i].action)
	{
		if (ft_strcmp(command, var->act[i].action) == 0)
			return (1);
		i++;
	}
	return (0);
}
