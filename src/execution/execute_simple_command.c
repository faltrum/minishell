/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseus <kseus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:28:30 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/09 00:22:09 by kseus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_execve(t_var *var, char **params)
{
	char	*execution_path;
	char	**arr_env;
	t_env	*env;

	env = find_in_env(var->env, "PATH");
	if (env)
		execution_path = find_path(env->value, params[0]);
	else
		execution_path = params[0];
	if (!execution_path)
		return (EXIT_FAILURE);
	arr_env = env_to_array(var->env);
	execve(execution_path, params, arr_env);
	// RUN VALGRIND --TRACK-CHILD TO KNOW WHAT TO FREE HERE
	return (perr(EXIT_FAILURE, 5, "minishell: ", *params, ": ", strerror(errno), "\n"));
}

int	execute_here(t_var *var, char **params)
{
	int		i;

	i = 0;
	while (var->act && var->act[i].action)
	{
		if (ft_strcmp(params[0], var->act[i].action) == 0)
			return ((*(var->act[i].function))(var, params));
		i++;
	}
	return (execute_execve(var, params));
}

int	execute_in_subshell(t_var *var, char **params, int flags, int status)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perr(EXIT_FAILURE, 3, "minishell:", *params, ": fork error\n"));
	else if (pid == 0)
		exit (execute_here(var, params));
	if (!(flags & WAIT))
	{
		waitpid(pid, &status, WNOHANG);
		return (EXIT_SUCCESS);
	}
	set_signal_ignore(SIGINT);
	waitpid(pid, &status, 0);
	set_signal_handler(SIGINT, sint_handler);
	if (WIFSIGNALED(status))
		return (130);
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	try_execution(t_var *var, char **params, int flags)
{
	int	status;

	if (!params || !params[0])
		return (EXIT_SUCCESS);
	status = EXIT_FAILURE;
	if (flags & SUBSHELL || !is_builtin(var, params[0]))
		status = execute_in_subshell(var, params, flags, status);
	else
		status = execute_here(var, params);
	return (status);
}
