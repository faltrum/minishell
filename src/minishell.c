/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:38 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/19 10:29:02 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_line(char **l, t_var *var)
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

static void	minishell(t_var *var)
{
	char		*line;
	t_command	*command_tree;

	line = NULL;
	while (1)
	{
		if (get_line(&line, var) == -1)
			break ;
		if (!line)
			continue ;
		if (g_sigint)
			var->exit = 130;
		command_tree = parser(var, line);
		if (command_tree)
			var->exit = exe_command_tree(command_tree, var);
		free_command_tree(command_tree);
		g_sigint = 0;
	}
}

int	main(int argc, char **argv, char **env)
{
	static t_var	var;
	int				exit;

	(void) argc;
	(void) argv;
	init_minishell(env, &var);
	minishell(&var);
	rl_clear_history();
	exit = var.exit;
	minishell_cleanup(&var);
	if (isatty(STDIN_FILENO))
		write(STDERR_FILENO, STR_EXIT, ft_strlen(STR_EXIT));
	return (exit);
}
