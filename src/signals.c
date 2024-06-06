/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseus <kseus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:35:51 by oseivane          #+#    #+#             */
/*   Updated: 2024/06/06 08:30:43 by kseus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

// Things to do:
// ^C gets printed
// Behaviour with subshells

int g_quit = IDLE; // REVISAR

void	sint_handler(int signal)
{
	(void) signal;
	if (g_quit == IDLE)
	{
		write(1, "\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	reset_signal(t_var *var)
{
	(void) var;
	g_quit = IDLE;
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
