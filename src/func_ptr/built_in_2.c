/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:34:25 by oseivane          #+#    #+#             */
/*   Updated: 2024/05/18 20:05:52 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(t_var *var, char **params)
{
	int		index_dash;
	int		index_end;
	char	*flag;
	char	*temp;
	char	*str;

	flag = NULL;
	str = "";
	if (params[1])
	{
		index_dash = ft_strchr_index(params[1], '-');
		index_end = ft_strchr_index(params[1], ' ');
		if (index_end == -1)
			index_end = ft_strlen(params[1]);
		if (index_dash != -1)
		{
			flag = ft_substr(params[1], index_dash, index_end);
			temp = ft_substr(params[1], index_end, ft_strlen(params[1]));
			str = ft_strtrim(temp, " \t");
			printf("%s", str);
			free(str);
			free(temp);
		}
		else
			printf("%s", params[1]);
	}
	if (!params[1] || index_dash == -1 || ft_strcmp(flag, "-n") != 0)
		printf("\n");
	if (flag)
		free(flag);
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
