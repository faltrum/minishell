/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 00:33:54 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/09 00:54:57 by kseligma         ###   ########.fr       */
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
	ft_strlcat(prompt, "$", len);
	ft_strlcat(prompt, " ", len);
}

char	*get_cwd(t_var *var)
{
	char	*name;
	size_t	len;
	char	cwd[PATH_MAX];
	char	*prompt;
	t_env	*env_user;

	env_user = find_in_env(var->env, "USER");
	if (!env_user)
		name = "";
	else
		name = env_user->value;
	getcwd(cwd, sizeof(cwd));
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cwd[0] = 0;
	len = strlen(GREEN) + ft_strlen(name) + strlen(RESET) \
		+ strlen(BLUE) + strlen(cwd) \
		+ strlen(RESET) + 4;
	if (ft_errloc(len, 1, (void **) &prompt) == -1)
		return (NULL);
	set_prompt(prompt, name, cwd, len);
	return (prompt);
}
