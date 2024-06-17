/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:34:19 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/17 11:26:08 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	get_key_and_value_export(char **key, char **value, char *param)
{
	int	eq;

	eq = ft_strchr_index(param, '=');
	if (eq == -1)
	{
		*key = ft_strdup(param);
		*value = NULL;
	}
	else
	{
		*key = ft_substr(param, 0, eq);
		*value = ft_substr(param, eq + 1, ft_strlen(param) - eq - 1);
	}
	if (!*key || (!*value && eq != -1))
	{
		free(*key);
		free(*value);
		ft_err(0, ERR_MALLOC, 0, 0);
		return (-1);
	}
	return (0);
}

static int	get_add_var_env(t_var *var, char *param)
{
	char	*key;
	char	*value;
	t_env	*env;

	if (get_key_and_value_export(&key, &value, param) == -1)
		return (-1);
	env = find_in_env(var->env, key);
	if (!env)
		add_in_env(var, key, value);
	else
	{
		free(key);
		free(env->value);
		env->value = value;
	}
	return (0);
}

static int	valid_identifier(char *str, int *exit)
{
	char	*s0;

	s0 = str;
	if (!str)
		return (-1);
	if (!is_identifier(*str, 1))
	{
		*exit = EXIT_FAILURE;
		return (ft_err_here_doc(-1, EXPORT, s0, ERR_VALID_IDENTIFIER));
	}
	while (*str && is_identifier(*str, 0))
		str ++;
	if (!*str || *str == '=')
		return (0);
	*exit = EXIT_FAILURE;
	return (ft_err(-1, EXPORT, s0, ERR_VALID_IDENTIFIER));
}

static int	print_export(t_env *env)
{
	int	exit;

	exit = EXIT_SUCCESS;
	while (env)
	{
		if (env->value)
		{
			if (printf("declare -x %s=\"%s\"\n", env->name, env->value) == -1)
				exit = EXIT_FAILURE;
		}
		else if (printf("declare -x %s\n", env->name) == -1)
			exit = EXIT_FAILURE;
		env = env->next;
	}
	return (exit);
}

int	ft_export(t_var *var, char **params)
{
	int	exit;

	exit = EXIT_SUCCESS;
	if (!params)
		return (EXIT_FAILURE);
	if (!params[1])
		return (print_export(var->env));
	else
	{
		params ++;
		while (*params)
		{
			if (valid_identifier(*params, &exit) == 0)
				if (get_add_var_env(var, *params) == -1)
					exit = EXIT_FAILURE;
			params ++;
		}
	}
	return (exit);
}
