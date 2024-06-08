#include "minishell.h"

int	execute_simple_command(t_simple_command	*command, t_var *var, int flags)
{
	int		exit;

	if (expand_command_lists(command, var) == -1)
		exit = EXIT_FAILURE;
	else
	{
		exit = execute_redirections(command->redirects);
		if (exit == EXIT_SUCCESS)
		{
			if (command->words)
				command->args = list_to_arr(command->words); // What if fails??
			if (command->args)
				exit = try_execution(var, command->args, flags);
			else
				exit = EXIT_FAILURE;
		}
	}
	if (flags & RESTOREFD)
		restore_fds(var->stdfds);
	return (exit);
}

int	execute_command_tree(t_command *node, t_var *var)
{
	int	ext;

	ext = 0;
	if (node->type == cm_simple)
		return (execute_simple_command(node->value.simple, var, RESTOREFD | WAIT));
	else if (node->type == cm_connection)
	{
		if (node->value.connection->connector == pipe_con)
			return (execute_pipeline(node, var));
		ext = execute_command_tree(node->value.connection->first, var);
		if (ext == EXIT_SUCCESS)
		{
			if (node->value.connection->connector == or_or)
				return (ext);
			return (execute_command_tree(node->value.connection->second, var));
		}
		else
		{
			if (node->value.connection->connector == or_or)
				return (execute_command_tree(node->value.connection->second, var));
			return (ext);
		}
	}
	return (ext);
}
