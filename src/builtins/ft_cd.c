/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:01:31 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/10 23:22:32 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_dir(t_var *var, char *dir)
{
	char	str[PATH_MAX];

	if(!dir)
		return (EXIT_FAILURE);
	if (getcwd(str, PATH_MAX) == NULL || chdir(dir) == -1)
		return (ft_err(EXIT_FAILURE, "cd", dir, strerror(errno)));
	replace_or_set_env(var, "OLDPWD", str);
	replace_or_set_env(var, "PWD", str);
	return (EXIT_SUCCESS);
}
static int	next_options(t_var *var, t_env *env, char **params, char *dir)
{
	if (params[1][0] == '\0')
		ft_err(0, "cd", "null directory", 0);
	else if (!ft_strcmp(params[1], "/"))
		dir = "/";
	else if (!ft_strcmp(params[1], "-"))
	{
		env = find_in_env(var->env, "OLDPWD");
		if (!env)
			ft_err(0, "OLDPWD not set", 0, 0);
		else
			dir = env->value;
	}
	else
		dir = params[1];
	return (change_dir(var, dir));
}

int	ft_cd(t_var *var, char **params)
{
	char	*dir;
	t_env	*env;

	dir = NULL;
	env = NULL;
	if (params[1] && params[2])
		perr(0, 1, "minishell: cd: too many arguments\n");
	else if (!params[1] || !ft_strcmp(params[1], "~"))
	{
		env = find_in_env(var->env, "HOME");
		if (!env)
			ft_err(0, "HOME not set", 0, 0);
		else
			dir = env->value;
	}
	else
		return (next_options(var, env, params, dir));
	return (change_dir(var, dir));
}
