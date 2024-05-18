#include "../../includes/Header.h"

int	redirect_append(t_redirect *redirects)
{
	int	flags;
	int	exit;
	int	fd;

	exit = 1;
	flags = O_CREAT | O_WRONLY | O_APPEND;
	fd = open(redirects->word, flags, 0644);
	if (fd == -1 || dup2(1, fd))
	{
		exit = 0;
		perror("minishell");
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
	if (fd == -1 || dup2(1, fd))
	{
		exit = 0;
		perror("minishell");
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
	if (fd == -1 || dup2(1, fd))
	{
		exit = 0;
		perror("minishell");
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
			if (dup2(0, redirects->fd) == -1)
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
			command->words->word = expansion(var, words->word);
		words = words->next;
	}
	while (redirects)
	{
		if (redirects->type != here_doc) // Es esto necesario? Cuando se deberia hacer?
			redirects->word = expansion(var, redirects->word); // Review expansion function
		redirects = redirects->next;
	}
}

int	execute_simple_command(t_simple_command	*command, t_var *var)
{
	int		exit;
	char	**args;

//	execute_expansions(command, var);
	exit = execute_redirections(command->redirects);
	command->args = list_to_arr(command->words);
	if (!exit || !command->args)
		return (exit);
	function_ptr(var, command->args); // Unless this is not the last of a pipe, wait for the exit status (execute_commands should prob change) // Also function needs to be change for exit value return
	return (exit);
}

int	execute_pipeline(t_connection *command, t_var *var)
{
	// Refer to pipex or implementation
	return (1);
}

int	execute_commands(t_command *node, t_var *var)
{
	int	ext;

	ext = 0;
	if (node->type == cm_simple)
		return (execute_simple_command(node->value.simple, var));
	else if (node->type == cm_connection)
	{
		if (node->value.connection->connector == pipe_con)
			return (execute_pipeline(node->value.connection, var));
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