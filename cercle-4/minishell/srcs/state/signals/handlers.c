/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 02:49:01 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:30:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"

/**
 * @brief Handle interactive-mode signals while readline owns the terminal.
 * @param sig Signal number delivered to the shell process.
 * BASH POSIX: SIGINT in interactive mode must show a new empty line
 */
void	handle_interactive(int sig)
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
 */
void	handle_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_last_signal = 130;
		write(1, "\n", 1);
	}
}

/**
 * @brief Handle delivery of SIGTERM by recording it.
 * @param sig Signal number (unused).
 * @return This function does not return a value.
 */
void	handle_sigterm(int sig)
{
	(void)sig;
	g_last_signal = SIGTERM;
}

/**
 * @brief Readline event hook that terminates the loop on SIGTERM.
 * @return 0 for compatibility with the readline hook API.
 */
int	event_hook(void)
{
	if (g_last_signal == SIGTERM)
		rl_done = 1;
	return (0);
}

/**
 * @brief Install one signal-handling mode for the shell process.
 * @param handler SIGINT handler used for the requested runtime mode.
 * BASH POSIX: SIGQUIT must always be ignored in the main shell process
 */
void	setup_signal_mode(void (*handler)(int))
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_handler = handle_sigterm;
	sigaction(SIGTERM, &sa, NULL);
	if (handler == handle_interactive)
		rl_event_hook = event_hook;
	else
		rl_event_hook = NULL;
}
