#include "minishell.h"

int change_dir(t_var *var, char *dir)
{
    char    str[PATH_MAX];

    if(!dir)
        return (EXIT_FAILURE);
    getcwd(str, PATH_MAX);
    if (chdir(dir) == -1)
        return (perr(EXIT_FAILURE, 5, "minishell: cd: ", dir, ": ", strerror(errno), "\n"));
    replace_or_set_env(var, "OLDPWD", str);
    getcwd(str, PATH_MAX);
    replace_or_set_env(var, "PWD", str);
    return (EXIT_SUCCESS);
}

int ft_cd(t_var *var, char **params)
{
    char    *dir;
    t_env   *env;

    dir = NULL;
    if (params[1] && params[2])
        perr(0, 1, "minishell: cd: too many arguments\n");
    else if (!params[1] || !ft_strcmp(params[1], "~"))
    {
        env = find_in_env(var->env, "HOME");
        if (!env)
            perr(0, 1, "minishell: HOME not set\n");
        else
            dir = env->value;
    }
    else if (params[1][0] == '\0')
        perr(0, 1, "minishell: cd: null directory\n");
    else if (!ft_strcmp(params[1], "/"))
        dir = "/";
    else if (!ft_strcmp(params[1], "-"))
    {
        env = find_in_env(var->env, "OLDPWD");
        if (!env)
            perr(0, 1, "minishell: OLDPWD not set\n");
        else
            dir = env->value;
    }
    else
        dir = params[1];
    return (change_dir(var, dir));
}
