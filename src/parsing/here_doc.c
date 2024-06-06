#include "minishell.h"

int	heredoc_error(int fds[2], char *line)
{
	perror("minishell");
	close(fds[0]);
	close(fds[1]);
	free(line);
	return (0);
}

int	do_here_doc(t_redirect *redir)
{
	int		fds[2];
	char	*line;

	if (pipe(fds) == -1)
		return (heredoc_error(fds, NULL));
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			perr(0, 3, "minishell: warning: here-document delimited by end-of-file (wanted `", redir->word, "')\n");
			break ;
		}
		if (!ft_strcmp(redir->word, line))
			break ;
		if (write(fds[1], line, ft_strlen(line)) == -1)
			return (heredoc_error(fds, line));
		if (write(fds[1], "\n", 1) == -1)
			return (heredoc_error(fds, line));
		free(line);
	}
	close(fds[1]);
	redir->fd = fds[0];
	return (1);
}
