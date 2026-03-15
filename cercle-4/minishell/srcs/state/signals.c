/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:32:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/15 07:36:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"

int			g_last_signal = 0;

/**
 * @brief Handle interactive-mode signals while readline owns the terminal.
 * @param sig Signal number delivered to the shell process.
 * @return This function does not return a value.
 * BASH POSIX: SIGINT in interactive mode must show a new empty line
 */
static void	handle_interactive(int sig)
{
	if (sig == SIGINT)
	{
		g_last_signal = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/**
 * @brief Handle heredoc-mode signals during blocking heredoc reads.
 * @param sig Signal number delivered to the shell process.
 * @return This function does not return a value.
 */
static void	handle_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_last_signal = 130;
		write(1, "\n", 1);
	}
}

/**
 * @brief Install one signal-handling mode for the shell process.
 * @param handler SIGINT handler used for the requested runtime mode.
 * @return This function does not return a value.
 * BASH POSIX: SIGQUIT must always be ignored in the main shell process
 */
static void	setup_signal_mode(void (*handler)(int))
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	rl_event_hook = NULL;
}

/**
 * @brief Switch the shell signal behavior to the requested runtime mode.
 * @param mode One of the defined signal modes for interactive, blocking, or
 * heredoc execution.
 * @return This function does not return a value.
 */
void	setup_signals(int mode)
{
	if (mode == SIGNAL_INTERACTIVE)
		setup_signal_mode(handle_interactive);
	else if (mode == SIGNAL_BLOCKING)
		setup_signal_mode(SIG_IGN);
	else if (mode == SIGNAL_HEREDOC)
		setup_signal_mode(handle_heredoc);
}
