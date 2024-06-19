/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 00:33:54 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/19 10:32:01 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	set_prompt(char *prompt, char *name, char *cwd, size_t len)
{
	ft_strlcat(prompt, GREEN, len);
	ft_strlcat(prompt, name, len);
	ft_strlcat(prompt, RESET, len);
	ft_strlcat(prompt, ":", len);
	ft_strlcat(prompt, BLUE, len);
	ft_strlcat(prompt, cwd, len);
	ft_strlcat(prompt, RESET, len);
	ft_strlcat(prompt, PROMPT_END, len);
}

char	*get_cwd(t_var *var)
{
	char	*name;
	size_t	len;
	char	cwd[PATH_MAX];
	char	*prompt;
	t_env	*env;

	env = find_in_env(var->env, "USER");
	if (!env)
		name = "";
	else
		name = env->value;
	getcwd(cwd, sizeof(cwd));
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cwd[0] = 0;
	len = ft_strlen(GREEN) + ft_strlen(name) + ft_strlen(RESET) \
		+ ft_strlen(BLUE) + ft_strlen(cwd) \
		+ ft_strlen(RESET) + 4;
	if (ft_errloc(len, 1, (void **) &prompt) == -1)
		return (NULL);
	set_prompt(prompt, name, cwd, len);
	return (prompt);
}
