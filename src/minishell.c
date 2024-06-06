/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseus <kseus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:38 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/06 06:29:15 by kseus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_line(char **l, t_var *var)
{
	char	*line;
	char	*path;

	path = get_cwd(var);
	line = readline(path);
	free(path);
	if (!line)
		return (-1);
	else if (empty_line(line))
	{
		free(line);
		line = NULL;
	}
	else
		add_history(line);
	*l = line;
	return (0);
}

void	minishell(t_var *var)
{
	char		*line;
	t_command	*command_tree;

	line = NULL;
	init_signals();
	while (1)
	{
		reset_signal(var);
		if (get_line(&line, var) == -1)
			break ;
		command_tree = parser(var, line);
		if (command_tree)
			var->exit = execute_command_tree(command_tree, var);
//		free_command_tree(command_tree);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_var	*var;
	int		exit;

	(void) argc;
	(void) argv;
	var = init_struct(env); // What if fails
	var->exit = EXIT_SUCCESS;
	minishell(var);
	exit = var->exit;
	rl_clear_history();
	func_exit(var);
	printf("exit\n");
	return (exit);
}
