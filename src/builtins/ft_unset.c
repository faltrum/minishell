/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:00:55 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/09 04:00:56 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_var *var, char**params)
{
	t_env	*env_name;
	int		ind;

	ind = 0;
	while (params[ind])
	{
		env_name = find_in_env(var->env, params[ind]);
		if (env_name)
			ft_lstdelone_env(&var->env, env_name);
		ind ++;
	}
	return (EXIT_SUCCESS);
}
