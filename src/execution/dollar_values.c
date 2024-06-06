#include "minishell.h"

char	*get_value(t_var *var, char *key)
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

char	*get_key(char *word)
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

int	get_key_and_value(char *word, char **key, char **value, t_var *var)
{
	*key = get_key(word);
	if (!*key)
		return (-1);
	*value = get_value(var, *key);
	if (!*value)
	{
		free(*key);
		return (-1);
	}
	return (0);
}
