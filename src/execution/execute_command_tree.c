/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_tree.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:59:45 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/11 06:42:26 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_word_list *words)
{
	int	count;

	count = 0;
	while (words)
	{
		if (words->word)
			count ++;
		words = words->next;
	}
	return (count);
}

static char	**list_to_arr(t_word_list *words)
{
	int		count;
	char	**arr;

	arr = 0;
	if (ft_errloc(sizeof(*arr), count_args(words) + 1, (void **) &arr) == -1)
		return (NULL);
	count = 0;
	while (words)
	{
		if (words->word)
		{
			arr[count] = words->word;
			count++;
		}
		words = words->next;
	}
	arr[count] = NULL;
	return (arr);
}

int	exe_simple_command(t_simple_command	*command, t_var *var, int flags)
{
	int		exit;

	if (expand_command_list(command, var) == -1)
		exit = EXIT_FAILURE;
	else
	{
		exit = execute_redirections(command->redirects);
		if (exit == EXIT_SUCCESS)
		{
			if (command->words)
				command->args = list_to_arr(command->words);
			if (command->args)
				exit = try_execution(var, command->args, flags);
			else
				exit = EXIT_FAILURE;
		}
	}
	if (flags & RESTOREFD)
		restore_fds(var->fds_list);
	return (exit);
}

int	exe_command_tree(t_command *node, t_var *var)
{
	int	ext;

	ext = 0;
	if (node->type == cm_simple)
		return (exe_simple_command(node->value.simple, var, RESTOREFD | WAIT));
	else if (node->type == cm_connection)
	{
		if (node->value.connection->connector == pipe_con)
			return (exe_pipeline(node, var));
		ext = exe_command_tree(node->value.connection->first, var);
		if (ext == EXIT_SUCCESS)
		{
			if (node->value.connection->connector == or_or)
				return (ext);
			return (exe_command_tree(node->value.connection->second, var));
		}
		else
		{
			if (node->value.connection->connector == or_or)
				return (exe_command_tree(node->value.connection->second, \
					var));
			return (ext);
		}
	}
	return (ext);
}
