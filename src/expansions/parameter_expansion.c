/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:57:07 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/09 04:06:52 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_value(t_var *var, char *key)
{
	char	*expanded;
	t_env	*env;

	if (*key == '?')
		expanded = ft_itoa(var->exit);
	else
	{
		env = find_in_env(var->env, key);
		if (env)
			expanded = ft_strdup(env->value);
		else
			expanded = ft_strdup("");
	}
	if (!expanded)
		perr(0, 1, "minishell: expansion: memory error\n");
	return (expanded);
}

static char	*get_key(char *word)
{
	char	*str;
	size_t	ind;

	ind = 1;
	if (word[ind] == '?')
		str = ft_strdup("?");
	else
	{
		if (word[ind] == '_' || ft_isalpha(word[ind]))
			ind ++;
		while (word[ind] == '_' || ft_isalnum(word[ind]))
			ind ++;
		str = ft_substr(&word[1], 0, ind - 1);
	}
	if (!str)
		perr(0, 1, "minishell: expansion: memory error\n");
	return (str);
}

static int	allocate_expanded_string(char **str, char *word, char *value, char *key)
{
	*str = ft_calloc(sizeof(char), 1 + ft_strlen(word) + ft_strlen(value));
	if (!*str)
	{
		free(value);
		free(key);
		return (perr(-1, 1, "minishell: expansion: memory error\n"));
	}
	return (0);
}

static int	expand_parameter(t_var *var, char **word, int *i)
{
	char	*key;
	char	*value;
	char	*expanded_string;
	int		key_len;

	key = get_key(*word + *i);
	if (!key)
		return (-1);
	value = get_value(var, key);
	if (!value)
	{
		free(key);
		return (-1);
	}
	if (allocate_expanded_string(&expanded_string, *word, value, key) == -1)
		return (-1);
	key_len = ft_strlen(key);
	ft_strlcat(expanded_string, *word, *i + 1);
	ft_strlcat(expanded_string, value, ft_strlen(value) + *i + 1);
	ft_strlcat(expanded_string, &(*word)[*i + key_len + 1], ft_strlen(&(*word)[*i + key_len + 1]) + ft_strlen(expanded_string) + 1);
	free(value);
	free(key);
//	free(*word);
	*word = expanded_string;
	return (0);
}
int	parameter_expansion(t_var *var, char **str)
{
	int	i;
	int	flags;

	i = 0;
	flags = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == QUOTE || (*str)[i] == DQUOTE)
			update_quote_flag(*str , &i, &flags);
		else if (!(flags & QUOTED) && (*str)[i] == '$' && \
			(ft_isalpha((*str)[i + 1]) ||(*str)[i + 1] == '?' || (*str)[i + 1] == '_') && \
			expand_parameter(var, str, &i) == -1)
	return (-1);
		else
			i ++;
	}
	return (0);
}
