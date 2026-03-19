/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 06:14:56 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 05:12:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * @brief Read one raw input line from either readline or standard input.
 * @param prompt Prompt string shown when stdin is interactive.
 * @param state Active shell state, unused in the current implementation.
 * @return Newly allocated input line, or NULL on EOF.
 */
char	*read_raw_input(char *prompt, t_shell_state *state)
{
	(void)state;
	if (isatty(STDIN_FILENO))
		return (readline(prompt));
	return (get_next_line(STDIN_FILENO));
}

/**
 * @brief Read one logical input line, extending it when continuation is needed.
 * @param prompt Prompt string shown for the initial read.
 * @param state Active shell state used by multiline handling.
 * @return Newly allocated complete input line, or NULL on EOF.
 */
char	*read_input(char *prompt, t_shell_state *state)
{
	char	*line;

	line = read_raw_input(prompt, state);
	if (!line)
		return (NULL);
	line = handle_multiline_input(line, state);
	return (line);
}

/**
 * @brief Read the next command line for the shell main loop.
 * @param state Active shell state passed through the reader layer.
 * @return Newly allocated command line, or NULL on EOF.
 */
char	*get_command_line(t_shell_state *state)
{
	char	*line;
	char	*prompt;

	prompt = get_prompt(1);
	line = read_input(prompt, state);
	if (!line)
		return (NULL);
	return (line);
}
