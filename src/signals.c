/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:51 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/11 03:28:21 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define norminetterror "FIXME ^"

int	g_sigint;

void	sint_handler_heredoc(int signal)
{
	write(1, "\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	g_sigint = signal;
}

void	sint_handler(int signal)
{
	write(1, "\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_sigint = signal;
}

void	set_signal_ignore(int signal)
{
	struct sigaction	sigs;

	sigs.sa_flags = 0;
	sigs.sa_handler = SIG_IGN;
	sigemptyset(&sigs.sa_mask);
	sigaction(signal, &sigs, NULL);
}

void	set_signal_handler(int signal, void (*handler))
{
	struct sigaction	sigs;

	sigs.sa_flags = 0;
	sigs.sa_handler = handler;
	sigemptyset(&sigs.sa_mask);
	sigaction(signal, &sigs, NULL);
}
