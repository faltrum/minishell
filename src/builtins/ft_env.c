/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:01:23 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/10 23:14:49 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_var *var, char **params)
{
	t_env	*tmp;
	int		exit;

	exit = EXIT_SUCCESS;
	if (params[1])
	{
		ft_err(0, "env", "too many arguments", 0);
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
