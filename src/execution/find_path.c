/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 04:32:05 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/10 06:19:04 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*param_access_check(char *param, int *exit)
{
	if (access(param, F_OK) == -1)
	{
		if (ft_strchr(param, '/'))
			*exit = ft_err(127, param, strerror(errno), 0);
		else
			*exit = ft_err(127, param, "command not found", 0);
		return (NULL);
	}
	if (access(param, X_OK) == -1)
	{
		if (ft_strchr(param, '/'))
			*exit = ft_err(126, param, strerror(errno), 0);
		else
			*exit = ft_err(127, param, "command not found", 0);
		return (NULL);
	}
	return (param);
}

static int	path_access_check(char **path, char *param, int *exit)
{
	if (access(*path, F_OK) == 0)
	{
		if (access(*path, X_OK) == -1)
		{
			if (ft_strchr(param, '/'))
				*exit = ft_err(126, param, strerror(errno), 0);
			else
				*exit = ft_err(127, param, "command not found", 0);
			free(*path);
			*path = NULL;
		}
		return (0);
	}
	return (-1);
}

static char	*get_path_str(char *root, char *param)
{
	char	*path;
	size_t	len;

	len = ft_strlen(root) + ft_strlen(param) + 1;
	if (ft_errloc(len + 1, 1, (void **) &path) == -1)
		return (NULL);
	ft_strlcat(path, root, len + 1);
	ft_strlcat(path, "/", len + 1);
	ft_strlcat(path, param, len + 1);
	return (path);
}

char	*find_path(t_env *env, char *param, int *exit)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	if (!env || !env->value || ft_strchr(param, '/'))
		return	(param_access_check(param, exit));
	paths = ft_split(env->value, ':');
	if (!paths)
		return ((char *) ft_err(0, STR_MEMORY_ERR, 0, 0));
	while (paths[i])
	{
		path = get_path_str(paths[i], param);
		if (!path || path_access_check(&path, param, exit) == 0)
			break ;
		free(path);
		path = NULL;
		i ++;
	}
	free_arr(paths);
	if (path)
		return (path);
	return (param_access_check(param, exit));
}
