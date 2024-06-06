/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseus <kseus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:27:12 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/05 22:38:06 by kseus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_actions(t_var *var)
{
	var->act = malloc(sizeof(t_actions) * NUM_ACTIONS + 1);
	var->act[0].action = EXIT;
	var->act[0].function = &ft_exit;
	var->act[1].action = ECHO;
	var->act[1].function = &ft_echo;
	var->act[2].action = PWD;
	var->act[2].function = &ft_pwd;
	var->act[3].action = CD;
	var->act[3].function = &ft_cd;
	var->act[4].action = EXPORT;
	var->act[4].function = &ft_export;
	var->act[5].action = UNSET;
	var->act[5].function = &ft_unset;
	var->act[6].action = ENV;
	var->act[6].function = &ft_env;
	var->act[7].action = HELP;
	var->act[7].function = &ft_help;
	var->act[8].action = NULL;
}

void	restore_fds(int fds[2])
{
	(void) (fds);
	if(dup2(fds[0], STDIN_FILENO) == -1)
		perror("minishell");
	if (dup2(fds[1], STDOUT_FILENO) == -1)
		perror("minishell");
}

int	is_builtin(t_var *var, char *command)
{
	int i;

	i = 0;
	while (var->act[i].action)
	{
		if (ft_strcmp(command, var->act[i].action) == 0)
			return (-1);
		i++;
	}
	return (0);
}
