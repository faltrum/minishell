#include "minishell.h"

char	*find_path_return_aux(char **paths, char *temp, char *path, int err)
{
	if (paths)
		free_arr(paths);
	if (temp)
		free(temp);
	if (path)
		free(path);
	if (err)
		perr(EXIT_FAILURE, 1, "minishell: memory error\n");
	return (NULL);
}

char	**env_to_array(t_env *env)
{
	t_env	*copy;
	int		i;
	size_t	len;
	char	**arr;

	i = 0;
	copy = env;
	while (env)
	{
		if (env->value)
			i ++;
		env = env->next;
	}
	arr = ft_calloc((i + 1), sizeof(char *));
	if (!arr)
		return ((char **) find_path_return_aux(NULL, NULL, NULL, 1));
	i = 0;
	while (copy)
	{
		if (copy->value)
		{
			len = ft_strlen(copy->value) + ft_strlen(copy->name) + 3;
			arr[i] = ft_calloc(len, sizeof(char));
			if (!arr[i])
				return ((char **) find_path_return_aux(arr, NULL, NULL, 1));
			ft_strlcat(arr[i], copy->name, len);
			ft_strlcat(arr[i], "=", len);
			ft_strlcat(arr[i], copy->value, len);
			i ++;
		}
		copy = copy->next;
	}
	return (arr);
}

char	*find_path(char *env, char *param)
{
	char	*path;
	char	**paths;
	char	*temp;
	int		i;

	if (env)
	{
		paths = ft_split(env, ':');
		if (!paths)
			return (find_path_return_aux(NULL, NULL, NULL, 1));
		i = 0;
		while (paths[i])
		{
			temp = ft_strjoin(paths[i], "/");
			if (!temp)
				return (find_path_return_aux(NULL, NULL, NULL, 1));
			path = ft_strjoin(temp, param);
			if (!path)
				return (find_path_return_aux(NULL, NULL, NULL, 1));
			free(temp);
			if (!access(path, F_OK))
			{
				free_arr(paths);
				return (path);
			}
			free(path);
			i ++;
		}
	}
	free_arr(paths);
	if (!access(param, F_OK))
		return (param);
	return ((char *) perr(0, 3, "minishell: ", param, ": command not found\n"));
}
