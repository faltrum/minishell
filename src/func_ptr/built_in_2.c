/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:34:25 by oseivane          #+#    #+#             */
/*   Updated: 2024/05/22 21:50:56 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(t_var *var, char **params)
{
	int	ind;

	ind = 1;
	while (params[ind])
	{
		if (ind > 1)
			printf(" ");
		printf("%s", params[ind]);
		ind ++;
	}
	printf("\n");
}

void	ft_unset(t_var *var, char**params)
{
	t_env	*env_name;
	char	*name;
	int		index;

	if (params[1])
	{
		index = ft_strchr_index(params[1], '=');
		name = ft_substr(params[1], 0, index);
		env_name = find_in_env(var->env, name);
		if (env_name)
			ft_lstdelone_env(&var->env, env_name);
	}
}

void	ft_exit(t_var *var, char **params)
{
	//HACER TODOS LOS FREES
	printf("exit\n");
	func_exit(var);
	exit(0);
    //cambiar 0 por exit code
}
