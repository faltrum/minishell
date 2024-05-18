#include "../../includes/Header.h"

int	redirect_append(t_redirect *redirects)
{
	int	flags;
	int exit;
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

int redirect_output(t_redirect *redirects)
{
	int	flags;
	int exit;
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
			if (dup2(0, redirects->fd) == -1)
				perror("minishell: heredoc error");
		else if (redirects->type == append)
			redirect_append(redirects);
		else if (redirects->type == input_redir)
			redirect_input(redirects);
		else if (redirects->type == output_redir)
			redirect_output(redirects);
		redirects = redirects->next;
		if (!exit)
			break ;
	}
}

void	execute_expansions(t_simple_command *command, t_var *var)
{
	t_word_list	*words;
	t_redirect *redirects;

	words = command->words;
	while (words)
	{
		if (words->type != quoted)
			redirects->word = expansion(var, words->word);
		words = words->next;
	}
	while (redirects)
	{
		if (redirects->type != here_doc) // Es esto necesario? Cuando se deberia hacer?
			redirects->word = expansion(var, redirects->word); // Review expansion function
		redirects = redirects->next;
	}
}

/*void	function_ptr(t_var *var, char **params)
{
	int	i;

	i = 0;
	while (var->act[i].action)
	{
		if (ft_strcmp(params[0], var->act[i].action) == 0)
		{
			(*(var->act[i].function))(var, params);
			break ;
		}
		i++;
	}
	if (!var->act[i].action)
		execute_action(var, params);

		typedef struct s_var
{
	struct s_info_tree	*tree;
	struct s_env		*env;
	struct s_actions	*act; (ARR)
	struct s_actions_op	*op;
}	t_var;
}*/

int	execute_simple_command(t_simple_command	*command, t_var *var)
{
	int		exit;
	char	**args;

	execute_expansions(command, var);
	exit = execute_redirections(command->redirects);
	command->args = arr_to_list(command->words);
	free_word_list(command->words, 1);
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
	int	exit;

	exit = 0;
	if (node->type == cm_simple)
		return (execute_simple_command(node->value.simple), var);
	else if (node->type = cm_connection)
	{
		if (node->value.connection->connector = pipe)
			return (execute_pipeline(node, var));
		exit = execute_commands(node->value.connection->first, var);
		if (exit == EXIT_SUCCESS)
		{
			if (node->value.connection->connector == or_or)
				return (exit);
			return (execute_commands(node->value.connection->second, var));
		}
		else 
		{
			if (node->value.connection->connector == or_or)
				return (execute_commands(node->value.connection->second, var));
			return (exit);
		}
	}
}