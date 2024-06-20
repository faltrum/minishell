/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:01:23 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/20 10:49:58 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	ft_env(t_var *var, char **params)
{
	t_env	*tmp;
	int		exit;

	exit = EXIT_SUCCESS;
	if (params[1])
	{
		ft_err(0, ENV, ERR_TOO_MANY_ARGS, 0);
		return (EXIT_FAILURE);
	}
	tmp = var->env;
	while (tmp)
	{
		if (tmp->value)
			if (printf("%s=%s\n", tmp->name, tmp->value) == -1)
				exit = EXIT_FAILURE;
		tmp = tmp->next;
	}
	return (exit);
}
