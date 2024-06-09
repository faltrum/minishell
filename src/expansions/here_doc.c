/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:57:02 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/09 03:57:03 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_cleanup(int fds[2], char  *line)
{
	close(fds[0]);
	close(fds[1]);
	free(line);
	if (g_sigint == SINT_HEREDOC)
		g_sigint = SINT_OFF;
	return (0);
}

int	heredoc_error(int fds[2], char *line)
{
	perror("minishell");
	heredoc_cleanup(fds, line);
	return (-1);
}

char	*get_heredoc_line(t_var *var)
{
	char	*line;
	char	*line_skip;

	line = get_next_line(0);
	if (g_sigint == SINT_ON || !line)
		return (line);
	line_skip = ft_strrchr(line, '\n');
	if (line_skip)
		*line_skip = 0;
	parameter_expansion(var, &line);
	return (line);
}
int	do_here_doc(t_var *var, t_redirect *redir)
{
	int		fds[2];
	char	*line;

	if (pipe(fds) == -1)
		return (heredoc_error(fds, NULL));
	g_sigint = SINT_HEREDOC;
	while (1)
	{
		write(var->stdfds[1], "> ", 2);
		line = get_heredoc_line(var);
		if (!line && g_sigint == SINT_HEREDOC)
			perr(0, 3, "minishell: warning: here-document delimited by end-of-file (wanted `", redir->word, "')\n");
		if (!line || !ft_strcmp(redir->word, line))
			break ;
		if (write(fds[1], line, ft_strlen(line)) == -1 || write(fds[1], "\n", 2) == -1)
			return (heredoc_error(fds, line));
		free(line);
	}
	if (g_sigint == SINT_ON)
		return (heredoc_cleanup(fds, line));
	g_sigint = SINT_OFF;
	close(fds[1]);
	redir->fd = fds[0];
	return (0);
}
