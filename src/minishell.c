/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:38 by oseivane          #+#    #+#             */
/*   Updated: 2024/05/18 20:06:15 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/Header.h"

char	*get_line(char **argv, t_var *var, int fd, char *previous_str)
{
	char	*line;
	char	*line_cleaned;
	char	*path;

	if (fd)
		return (get_next_line(fd));
	else
	{
		line_cleaned = NULL;
		path = get_cwd(var);
		line = readline(path);
		if (line && line[0] != '\0')
		{
			line_cleaned = ft_strtrim(line, " \t\n");
			manage_history(line_cleaned, &previous_str);
		}
		free(path);
		return (line_cleaned);
	}
}

int	init_loop(char **argv, char **env, int fd)
{
	char	*line;
	char	*previous_str;
	t_var	*var;
	t_command *head;

	(void)argv;
	line = NULL;
	var = init_struct(env);
	previous_str = NULL;
	while (1)
	{
		line = get_line(argv, var, fd, previous_str);
		init_signals(READ);
		update_signal(var->env);
		update_signal(var->env);
		head = NULL;
		head = temp_name_additions(line); // ADDITIONS
		if (fd && line == NULL)
			break ;
		if (!head)
			continue ;
//		printf_commands(head);
		execute_commands(head, var);
//		free_command(head);
		//make_binnary_tree(var, line_cleaned);
		//ft_printall(var);
		//toString_t_var(var);
//		free(line);
	}
	if (previous_str)
		free(previous_str);
	rl_clear_history();
//	func_exit(var);
	return (EXIT_SUCCESS);
}

int	get_fd(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	main(int argc, char **argv, char **env)
{
	int	fd;

	fd = 0;
//	printf("esto esta funcionando?????\n");
	//g_exit_sig = 0;
	if (argv[1] != NULL)
		fd = get_fd(argv[1]);
	init_loop(argv, env, fd);
//	printf("salee\n");
	return (EXIT_SUCCESS);
}