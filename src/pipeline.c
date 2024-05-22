#include "../includes/minishell.h"

// Close?? Make a listed link o algo

// For first command: Create pipe, dup output, execute
// For middle command: Dup input, create pipe, dup output, execute
// For last command: Dup input, execute

int execute_pipeline_command(t_simple_command *command, int fds[2], t_var *var, int islast)
{
	int exit;

	if (fds[0] != -1 && dup2(fds[0], STDIN_FILENO) == -1)
		perror("minishell");
	close (fds[0]);
	if (islast)
	{
		if (dup2(var->stdfds[1], STDOUT_FILENO) == -1)
			perror ("minishell");
		exit = execute_simple_command(command, var, 1, 1);
	}
	else
	{	if (pipe(fds) == -1)
			perror("minishell");
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			perror("minishell");
		exit = execute_simple_command(command, var, 0, 0);
	}
	close(fds[1]);
	return (exit);
}

int execute_pipeline(t_command *node, t_var *var)
{
	int fds[2];

	fds[0] = -1;
	while (node->type == cm_connection)
	{
		execute_pipeline_command(node->value.connection->first->value.simple, fds, var, 0);
		node = node->value.connection->second;
	}
	return (execute_pipeline_command(node->value.simple, fds, var, 1));
}