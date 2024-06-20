/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command_bonus.C                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:28:30 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/20 10:49:58 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	execute_execve(t_var *var, char **params)
{
	char	*execution_path;
	char	**arr_env;
	int		ex;

	ex = EXIT_FAILURE;
	execution_path = find_path(find_in_env(var->env, "PATH"), \
		params[0], &ex);
	if (!execution_path)
	{
		free_command_tree(var->command_tree);
		minishell_cleanup(var);
		return (ex);
	}
	arr_env = env_to_array(var->env);
	execve(execution_path, params, arr_env);
	if (execution_path && execution_path != params[0])
		free(execution_path);
	if (ft_strchr(*params, '/'))
		ex = ft_err(126, *params, ERR_IS_DIR, 0);
	else
		ex = ft_err(127, *params, ERR_CMD_NOT_FOUND, 0);
	free_arr(arr_env);
	free_command_tree(var->command_tree);
	minishell_cleanup(var);
	return (ex);
}

static int	execute_here(t_var *var, char **params, int flags)
{
	int		i;
	int		ex;

	i = 0;
	if (var->fds_list[2] > 2)
		close(var->fds_list[2]);
	while (var->act && var->act[i].action)
	{
		if (ft_strcmp(params[0], var->act[i].action) == 0)
		{
			ex = (*(var->act[i].function))(var, params);
			if (flags & SUBSHELL)
			{
				free_command_tree(var->command_tree);
				minishell_cleanup(var);
			}
			return (ex);
		}
		i++;
	}
	return (execute_execve(var, params));
}

static int	return_helper(t_var *var, int pid, int status)
{
	waitpid(pid, &status, 0);
	close(1);
	close(0);
	while (waitpid(-1, NULL, 0) != -1)
		;
	restore_fds(var->fds_list);
	set_signal_handler(SIGINT, sint_handler);
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

static int	execute_in_subshell(t_var *var, \
	char **params, int flags, int status)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		var->kill = 1;
		return (ft_err(EXIT_FAILURE, *params, ERR_FORK, strerror(errno)));
	}
	else if (pid == 0)
	{
		set_signal_mode(SIGINT, SIG_DEFAULT);
		set_signal_mode(SIGQUIT, SIG_DEFAULT);
		exit (execute_here(var, params, flags));
	}
	set_signal_mode(SIGINT, SIG_IGNORE);
	if (!(flags & WAIT))
	{
		waitpid(pid, &status, WNOHANG);
		return (EXIT_SUCCESS);
	}
	return (return_helper(var, pid, status));
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
		status = execute_here(var, params, flags);
	return (status);
}
