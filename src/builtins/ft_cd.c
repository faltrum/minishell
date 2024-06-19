/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:01:31 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/19 09:56:46 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_print(t_env *pwd, int print)
{
	if (print && pwd && pwd->value)
		printf("%s\n", pwd->value);
	return (EXIT_SUCCESS);
}

static int	change_dir(t_var *var, char *dir, int print)
{
	char	new[PATH_MAX];
	t_env	*oldpwd;
	t_env	*pwd;

	pwd = find_in_env(var->env, "PWD");
	oldpwd = find_in_env(var->env, "OLDPWD");
	if (!dir)
		return (EXIT_FAILURE);
	if (chdir(dir) == -1)
		return (ft_err(EXIT_FAILURE, CD, dir, strerror(errno)));
	if (getcwd(new, PATH_MAX) == NULL)
		return (ft_err(EXIT_FAILURE, CD, dir, strerror(errno)));
	if (oldpwd)
	{
		if (pwd)
			replace_or_set_env(var, "OLDPWD", pwd->value);
		else
		{
			free(oldpwd->value);
			oldpwd->value = NULL;
		}
	}
	if (pwd)
		replace_or_set_env(var, "PWD", new);
	return (cd_print(pwd, print));
}

static int	next_options(t_var *var, t_env *env, char **params, char *dir)
{
	int	print;

	print = 0;
	if (!ft_strcmp(params[1], "/"))
		dir = "/";
	else if (!ft_strcmp(params[1], "-"))
	{
		env = find_in_env(var->env, "OLDPWD");
		if (!env)
			ft_err(0, "OLDPWD not set", 0, 0);
		else
			dir = env->value;
		print = 1;
	}
	else
		dir = params[1];
	return (change_dir(var, dir, print));
}

int	ft_cd(t_var *var, char **params)
{
	char	*dir;
	t_env	*env;

	dir = NULL;
	env = NULL;
	if (params[1] && params[2])
		ft_err(0, CD, ERR_TOO_MANY_ARGS, 0);
	else if (params[1] && params[1][0] == 0)
		return (EXIT_SUCCESS);
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
	return (change_dir(var, dir, 0));
}
