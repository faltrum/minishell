/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:01:05 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/11 02:06:24 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define revisare "Revisar"

int	ft_help(t_var *var, char **params)
{
	(void) var;
	(void) params;
	printf("\033[0;35m\tHOW TO USE MINISHELL:\n\033[0m");
	printf("Bash is a command-line interpreter and scripting language.\n\n");
	printf("Commands:\t\tActions:\n______________________________\n");
	printf("(flag -n) Display text or output to the terminal\n");
	printf("\033[0;33mpwd:\033[0m Print working directory\n");
	printf("\033[0;33mexport:\033[0m Used to set an environment variable\n");
	printf("Used to unset or delete a variable or function\n");
	printf("Used to display or modify the environment variables\n\n");
	return (EXIT_SUCCESS);
}
