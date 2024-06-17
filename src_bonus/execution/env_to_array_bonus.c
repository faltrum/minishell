/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:57:53 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/11 02:04:16 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->value)
			i ++;
		env = env->next;
	}
	return (i);
}

char	**env_to_array(t_env *env)
{
	int		i;
	size_t	len;
	char	**arr;

	arr = NULL;
	if (ft_errloc(sizeof(*arr), count_env(env) + 1, (void **) &arr) == -1)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value)
		{
			len = ft_strlen(env->value) + ft_strlen(env->name) + 3;
			arr[i] = ft_calloc(len, sizeof(char));
			if (!arr[i])
				return (NULL);
			ft_strlcat(arr[i], env->name, len);
			ft_strlcat(arr[i], "=", len);
			ft_strlcat(arr[i], env->value, len);
			i ++;
		}
		env = env->next;
	}
	return (arr);
}
