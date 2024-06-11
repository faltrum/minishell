/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:57:02 by kseligma          #+#    #+#             */
/*   Updated: 2024/06/11 01:38:01 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_cleanup(int fds[2], char *line)
{
	close(fds[0]);
	close(fds[1]);
	free(line);
	return (-1);
}

static int	heredoc_error(int fds[2], char *line)
{
	ft_err(0, ERR_HEREDOC, strerror(errno), 0);
	return (heredoc_cleanup(fds, line));
}

static char	*get_heredoc_line(t_var *var)
{
	char	*line;
	char	*line_skip;

	line = get_next_line(0);
	if (line)
	{
		line_skip = ft_strrchr(line, '\n');
		if (line_skip)
			*line_skip = 0;
	}
	if (g_sigint == SINT_ON || !line)
		return (line);
	parameter_expansion(var, &line);
	return (line);
}

int	do_here_doc(t_var *var, t_redirect *redir)
{
	int		fds[2];
	char	*line;

	if (pipe(fds) == -1)
		return (heredoc_error(fds, NULL));
	while (1)
	{
		write(var->fds_list[1], "> ", 2);
		line = get_heredoc_line(var);
		if (!line && g_sigint == SINT_HEREDOC)
			ft_err_here_doc(0, WAR_HERE_EOF, redir->word, WAR_HERE_EOF2);
		if (!line || !ft_strcmp(redir->word, line))
			break ;
		if (write(fds[1], line, ft_strlen(line)) \
			== -1 || write(fds[1], \
			END_OF_LINE, ft_strlen(END_OF_LINE)) == -1)
			return (heredoc_error(fds, line));
		free(line);
	}
	if (g_sigint == SINT_ON)
		return (heredoc_cleanup(fds, line));
	close(fds[1]);
	redir->fd = fds[0];
	return (0);
}
