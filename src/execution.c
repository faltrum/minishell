/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:42:47 by oseivane          #+#    #+#             */
/*   Updated: 2024/05/23 12:45:21 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect_append(t_redirect *redirects)
{
	int	flags;
	int	exit;
	int	fd;

	exit = 1;
	flags = O_CREAT | O_WRONLY | O_APPEND;
	fd = open(redirects->word, flags, 0644);
	if (fd == -1 || dup2(fd, 1) == -1)
	{
		exit = 0;
		perror("minishell append");
	}
	close(fd);
	return (exit);
}

int	redirect_input(t_redirect *redirects)
{
	int	flags;
	int	exit;
	int	fd;

	exit = 1;
	flags = O_RDONLY;
	fd = open(redirects->word, flags);
	if (fd == -1 || dup2(fd, 1) == -1)
	{
		exit = 0;
		perror("minishell redirect input");
	}
	close(fd);
	return (exit);
}

int	redirect_output(t_redirect *redirects)
{
	int	flags;
	int	exit;
	int	fd;

	exit = 1;
	flags = O_CREAT | O_WRONLY | O_TRUNC;
	fd = open(redirects->word, flags, 0644);
	if (fd == -1 || dup2(fd, 1) == -1)
	{
		exit = 0;
		perror("minishell redirect output");
	}
	close(fd);
	return (exit);
}

int	execute_redirections(t_redirect *redirects)
{
	int	exit;

	while (redirects)
	{
		exit = 0;
		if (redirects->type == here_doc)
		{
			if (dup2(redirects->fd, 0) == -1)
				perror("minishell: heredoc error");
			else
				exit = 1;
		}
		else if (redirects->type == append)
			exit = redirect_append(redirects);
		else if (redirects->type == input_redir)
			exit = redirect_input(redirects);
		else if (redirects->type == output_redir)
			exit = redirect_output(redirects);
		redirects = redirects->next;
		if (!exit)
			break ;
	}
	return (exit);
}

void	execute_expansions(t_simple_command *command, t_var *var)
{
	t_word_list	*words;
	t_redirect	*redirects;

	words = command->words;
	redirects = command->redirects;
	while (words)
	{
		if (words->type != quoted)
			words->word = expansion(var, ft_strdup(words->word));
		words = words->next;
	}
	while (redirects)
	{
		if (redirects->type != here_doc)
			redirects->word = expansion(var, ft_strdup(redirects->word));
	}
}

void	restore_fds(int fds[2])
{
	if (dup2(fds[0], STDIN_FILENO) == -1)
		perror("minishell");
	if (dup2(fds[1], STDOUT_FILENO) == -1)
		perror("minishell");
}

int	execute_simple_command(t_simple_command	*command,
	t_var *var, int wait, int restore)
{
	int		exit;
	char	**args;

	execute_expansions(command, var);
	exit = execute_redirections(command->redirects);
	if (command->words)
		command->args = list_to_arr(command->words);
	if (exit == EXIT_SUCCESS || command->args)
		exit = function_ptr(var, command->args, wait);
	if (restore)
		restore_fds(var->stdfds);
	return (exit);
}

int	execute_commands(t_command *node, t_var *var)
{
	int	ext;

	ext = 0;
	if (node->type == cm_simple)
		return (execute_simple_command(node->value.simple, var, 1, 1));
	else if (node->type == cm_connection)
	{
		if (node->value.connection->connector == pipe_con)
			return (execute_pipeline(node, var));
		ext = execute_commands(node->value.connection->first, var);
		if (ext == EXIT_SUCCESS)
		{
			if (node->value.connection->connector == or_or)
				return (ext);
			return (execute_commands(node->value.connection->second, var));
		}
		else
		{
			if (node->value.connection->connector == or_or)
				return (execute_commands(node->value.connection->second, var));
			return (ext);
		}
	}
	return (ext);
}
