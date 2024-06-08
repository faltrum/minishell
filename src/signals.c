/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseus <kseus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:51 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/07 15:09:34 by kseus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ^C gets printed

int g_sigint = SINT_OFF; // REVISAR

void	sint_handler(int signal)
{
	(void) signal;
	write(1, "\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_sigint != SINT_HEREDOC)
		rl_redisplay();
	g_sigint = SINT_ON;
}

void	reset_signal(t_var *var)
{
	if (g_sigint)
		var->exit = 130;
	g_sigint = 0;
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

void	init_signals(void)
{
	set_signal_ignore(SIGQUIT);
	set_signal_handler(SIGINT, sint_handler);
}
