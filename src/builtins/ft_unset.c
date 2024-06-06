#include "minishell.h"

int	ft_unset(t_var *var, char**params)
{
	t_env	*env_name;
	int		ind;

	ind = 0;
	while (params[ind])
	{
		env_name = find_in_env(var->env, params[ind]);
		if (env_name)
			ft_lstdelone_env(&var->env, env_name);
		ind ++;
	}
	return (EXIT_SUCCESS);
}
