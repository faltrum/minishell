/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseus <kseus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:30 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/05 07:06:41 by kseus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*init_struct(char **env)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (var == NULL)
		perror("error\n");
	var->stdfds[0] = dup(STDIN_FILENO);
	if (var->stdfds[0] == -1)
		perror("minishell");
	var->stdfds[1] = dup(STDOUT_FILENO);
	if (var->stdfds[1] == -1)
		perror("minishell");
	save_env(var, env);
	save_actions(var);
	return (var);
}

char	*get_cwd(t_var *var)
{
	char	*name;
	size_t	len;
	char	cwd[PATH_MAX];
	char	*colored_cwd;

	name = find_in_env(var->env, "USER")->value; // What if unset user WOULD CRASH
	len = strlen(GREEN) + ft_strlen(name) + strlen(RESET)
			+ strlen(BLUE) + strlen(getcwd(cwd, sizeof(cwd)))
			+ strlen(RESET) + 4; // What if CWD deleted? Causes a crash.
	colored_cwd = ft_calloc(sizeof(char), len);
	if (!colored_cwd)
		return (NULL);
	//colored_cwd = "prueba";
	ft_strlcat(colored_cwd, GREEN, len);
	ft_strlcat(colored_cwd, name, len);
	ft_strlcat(colored_cwd, RESET, len);
	ft_strlcat(colored_cwd, ":", len);
	ft_strlcat(colored_cwd, BLUE, len);
	ft_strlcat(colored_cwd, getcwd(cwd, sizeof(cwd)), len);
	ft_strlcat(colored_cwd, RESET, len);
	ft_strlcat(colored_cwd, "$", len);
	ft_strlcat(colored_cwd, " ", len);
	return (colored_cwd);
}
