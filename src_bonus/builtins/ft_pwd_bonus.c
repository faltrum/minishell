/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:01:00 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/20 10:49:58 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
