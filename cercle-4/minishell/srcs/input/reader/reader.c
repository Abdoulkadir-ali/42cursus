/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 06:14:56 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 14:19:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*read_input(char *prompt, t_shell_state *state)
{
	char	*line;

	if (isatty(STDIN_FILENO))
		line = readline(prompt);
	else
		line = get_next_line(STDIN_FILENO);
	if (!line)
		return (NULL);
	line = handle_multiline_input(line, state);
	return (line);
}

char	*get_command_line(t_shell_state *state)
{
	char	*line;
	char	*prompt;
	char	*trimmed;
	char	*handled;

	prompt = get_prompt(1);
	line = read_input(prompt, state);
	if (!line)
		return (NULL);
	trimmed = ft_strtrim(line, " \t");
	{
		handled = handle_parenthesis(line, trimmed, state);
		if (handled)
			return (handled);
	}
	return (handle_multiline_input(line, state));
}
