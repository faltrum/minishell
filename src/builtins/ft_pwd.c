#include "minishell.h"

int ft_pwd(t_var *var, char **params)
{
	char	cwd[PATH_MAX];

	(void)params;
	(void)var;
    if (!getcwd(cwd, sizeof(cwd)) || printf("%s\n", cwd) == -1)
        perr(EXIT_FAILURE, 3, "minishell: pwd: ", strerror(errno), "\n");
    return (EXIT_SUCCESS);
}
