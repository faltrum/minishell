/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:58:12 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/10 10:01:12 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_append(t_redirect *redirects)
{
	int	flags;
	int	exit;
	int	fd;

	exit = EXIT_SUCCESS;
	flags = O_CREAT | O_WRONLY | O_APPEND;
	fd = open(redirects->word, flags, 0644);
	if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
	{
		exit = EXIT_FAILURE;
		perror("minishell: append");
	}
	if (fd > -1)
		close(fd);
	return (exit);
}

static int	redirect_input(t_redirect *redirects)
{
	int	flags;
	int	exit;
	int	fd;

	exit = EXIT_SUCCESS;
	flags = O_RDONLY;
	fd = open(redirects->word, flags);
	if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
	{
		exit = EXIT_FAILURE;
		perror("minishell: redirect input");
	}
	if (fd > -1)
		close(fd);
	return (exit);
}

static int	redirect_output(t_redirect *redirects)
{
	int	flags;
	int	exit;
	int	fd;

	exit = EXIT_SUCCESS;
	flags = O_CREAT | O_WRONLY | O_TRUNC;
	fd = open(redirects->word, flags, 0644);
	if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
	{
		exit = EXIT_FAILURE;
		perror("minishell: redirect output");
	}
	if (fd > -1)
		close(fd);
	return (exit);
}

static int	set_redirect_word(t_redirect *redirect)
{
	char		*word;
	t_word_list	*words;

	word = NULL;
	words = redirect->expanded;
	while (words)
	{
		if (words->word && word)
			return (-1);
		else if (words->word)
			word = words->word;
		words = words->next;
	}
	if (!word)
		return (-1);
	free(redirect->word);
	redirect->word = word;
	return (0);
}

int	execute_redirections(t_redirect *redirects)
{
	int	exit;

	exit = EXIT_SUCCESS;
	while (exit == EXIT_SUCCESS && redirects)
	{
		if (redirects->type == here_doc && dup2(redirects->fd, 0) == -1){
			exit = ft_err(EXIT_FAILURE, "heredoc error", strerror(errno), 0);}
		else if (redirects->word)
		{
			if (set_redirect_word(redirects) == -1)
				exit = ft_err(EXIT_FAILURE, "ambiguous redirect", 0, 0);
			else if (redirects->type == append)
				exit = redirect_append(redirects);
			else if (redirects->type == input_redir)
				exit = redirect_input(redirects);
			else if (redirects->type == output_redir)
				exit = redirect_output(redirects);
		}
		if (redirects->type == here_doc && exit == EXIT_SUCCESS)
			close (redirects->fd);
		redirects = redirects->next;
	}
	return (exit);
}
