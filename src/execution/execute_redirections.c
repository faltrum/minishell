#include "minishell.h"

int	redirect_append(t_redirect *redirects)
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
	close(fd);
	return (exit);
}

int	redirect_input(t_redirect *redirects)
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
	close(fd);
	return (exit);
}

int	redirect_output(t_redirect *redirects)
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
	close(fd);
	return (exit);
}

int	execute_redirections(t_redirect *redirects)
{
	int	exit;

	exit = EXIT_SUCCESS;
	while (redirects)
	{
		if (redirects->type == here_doc && dup2(redirects->fd, 0) == -1)
				exit = perr(EXIT_FAILURE, 3, "minishell: heredoc error: ", strerror(errno) ,"\n");
		else if (redirects->word)
		{
			if (redirects->type == append)
				exit = redirect_append(redirects);
			else if (redirects->type == input_redir)
				exit = redirect_input(redirects);
			else if (redirects->type == output_redir)
				exit = redirect_output(redirects);
		}
		if (exit == EXIT_FAILURE)
			break ;
		redirects = redirects->next;
	}
	return (exit);
}
