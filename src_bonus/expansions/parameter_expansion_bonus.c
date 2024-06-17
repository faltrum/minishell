/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:57:07 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/17 11:26:08 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
		ft_err(0, ERR_MALLOC, strerror(errno), 0);
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
		if (is_identifier(word[ind], 1))
			ind ++;
		while (is_identifier(word[ind], 0))
			ind ++;
		str = ft_substr(&word[1], 0, ind - 1);
	}
	if (!str)
		ft_err(0, ERR_MALLOC, strerror(errno), 0);
	return (str);
}

static int	allocate_expanded_string(char **str, \
char *word, char *value, char *key)
{
	if (ft_errloc(ft_strlen(word) + ft_strlen(value) + 1, \
		sizeof(*str), (void **)str) == -1)
	{
		free(value);
		free(key);
		return (-1);
	}
	return (0);
}

static int	expand_parameter(t_var *var, char **word, int *i)
{
	char	*key;
	char	*value;
	char	*expanded_string;

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
	ft_strlcat(expanded_string, *word, *i + 1);
	ft_strlcat(expanded_string, value, ft_strlen(value) + *i + 1);
	ft_strlcat(expanded_string, &(*word)[*i + ft_strlen(key) + 1], \
		ft_strlen(&(*word)[*i + ft_strlen(key) + 1]) \
		+ ft_strlen(expanded_string) + 1);
	free(value);
	free(key);
	free(*word);
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
			update_quote_flag(*str, &i, &flags);
		else if (!(flags & QUOTED) && (*str)[i] == '$' && \
			((*str)[i + 1] == '?' || is_identifier((*str)[i + 1], 1)) && \
			expand_parameter(var, str, &i) == -1)
			return (-1);
		else
			i ++;
	}
	return (0);
}
