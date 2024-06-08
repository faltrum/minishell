#include "minishell.h"

int ft_echo(t_var *var, char **params)
{
	int	ind;
    int flag;

    (void) var;
    flag = 0;
    ind = 1;
    if (params[1] && !ft_strcmp(params[1], "-n"))
    {
        flag = 1;
        ind ++;
    }
	while (params[ind])
	{
		if (ind > 1)
			if (printf(" ") == -1)
                return (2);
		if (printf("%s", params[ind]) == -1)
            return (2);
		ind ++;
	}
	if (!flag && printf("\n") == -1)
        return (2);
    return (EXIT_SUCCESS);
}