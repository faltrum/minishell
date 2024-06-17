/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:01:00 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/17 11:26:08 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	ft_pwd(t_var *var, char **params)
{
	char	cwd[PATH_MAX];

	(void)params;
	(void)var;
	if (!getcwd(cwd, sizeof(cwd)) || printf("%s\n", cwd) == -1)
		ft_err(EXIT_FAILURE, PWD, strerror(errno), 0);
	return (EXIT_SUCCESS);
}
