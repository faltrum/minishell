/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:30 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/17 11:26:07 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	save_actions(t_var *var)
{
	if (ft_errloc(sizeof(*(var->act)), \
		NUM_ACTIONS + 1, (void **) &(var->act)) == -1)
	{
		var->act = NULL;
		ft_err(-1, WAR_BUILTIN_MEMORY, 0, 0);
		return ;
	}
	var->act[0].action = EXIT;
	var->act[0].function = &ft_exit;
	var->act[1].action = ECHO;
	var->act[1].function = &ft_echo;
	var->act[2].action = PWD;
	var->act[2].function = &ft_pwd;
	var->act[3].action = CD;
	var->act[3].function = &ft_cd;
	var->act[4].action = EXPORT;
	var->act[4].function = &ft_export;
	var->act[5].action = UNSET;
	var->act[5].function = &ft_unset;
	var->act[6].action = ENV;
	var->act[6].function = &ft_env;
	var->act[7].action = NULL;
}

static int	env_str_to_node(int eq_ind, char *str, char **key, char **value)
{
	*key = ft_substr(str, 0, eq_ind);
	if (!*key)
		return (ft_err(-1, ERR_MALLOC, strerror(errno), 0));
	*value = ft_substr(str, eq_ind + 1, ft_strlen(str));
	if (!*value)
	{
		free(*key);
		return (ft_err(-1, ERR_MALLOC, strerror(errno), 0));
	}
	return (0);
}

static void	save_env(t_var *var, char **env)
{
	int		eq_ind;
	t_env	*new;
	char	*key;
	char	*value;

	var->env = NULL;
	while (*env)
	{
		eq_ind = ft_strchr_index(*env, '=');
		if (env_str_to_node(eq_ind, *env, &key, &value) == -1)
			continue ;
		new = ft_lstnew_env(key, value);
		if (!new)
		{
			free(key);
			free(value);
		}
		else
			ft_lstadd_back_env(&var->env, new);
		env ++;
	}
}

void	init_signals(void)
{
	g_sigint = 0;
	rl_catch_signals = 0;
	set_signal_handler(SIGQUIT, squit_handler);
	set_signal_handler(SIGINT, sint_handler);
}

void	init_minishell(char **env, t_var *var)
{
	init_signals();
	var->fds_list[0] = dup(STDIN_FILENO);
	if (var->fds_list[0] == -1)
		ft_err(0, "dup", strerror(errno), WAR_BROKE_STDIN);
	var->fds_list[1] = dup(STDOUT_FILENO);
	if (var->fds_list[1] == -1)
		ft_err(0, "dup", strerror(errno), WAR_BROKE_STDOUT);
	var->fds_list[2] = -1;
	save_env(var, env);
	save_actions(var);
	var->exit = EXIT_SUCCESS;
}
