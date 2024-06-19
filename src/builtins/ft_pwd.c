/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:01:00 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/19 10:26:36 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_var *var, char **params)
{
	char	cwd[PATH_MAX];
	t_env	*pwd;

	(void)params;
	(void)var;
	if (!getcwd(cwd, sizeof(cwd)))
	{
		pwd = find_in_env(var->env, "PWD");
		if (pwd && pwd->value && printf("%s\n", pwd->value) == -1)
			ft_err(EXIT_FAILURE, PWD, strerror(errno), 0);
	}
	else if (printf("%s\n", cwd) == -1)
		ft_err(EXIT_FAILURE, PWD, strerror(errno), 0);
	return (EXIT_SUCCESS);
}
