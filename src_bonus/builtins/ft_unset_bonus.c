/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:00:55 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/20 10:49:58 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	ft_unset(t_var *var, char**params)
{
	t_env	*env_name;
	int		ind;

	ind = 0;
	while (params && params[ind])
	{
		env_name = find_in_env(var->env, params[ind]);
		if (env_name)
			ft_lstdelone_env(&var->env, env_name);
		ind ++;
	}
	return (EXIT_SUCCESS);
}
