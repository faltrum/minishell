#include "minishell.h"

int ft_env(t_var *var, char **params)
{
    t_env	*tmp;
    int     exit;

    exit = EXIT_SUCCESS;
    if (params[1])
    {
        perr(0, 1, "minishell: env: too many arguments\n");
        return (EXIT_FAILURE);
    }
    tmp = var->env;
	while (tmp)
	{
        if (tmp->value)
		    if (printf("%s=%s\n", tmp->name, tmp->value) == -1)
                exit = EXIT_FAILURE;
		tmp = tmp->next;
	}
    return (exit);
}
