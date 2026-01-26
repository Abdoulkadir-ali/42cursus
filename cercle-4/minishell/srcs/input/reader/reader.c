/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 06:14:56 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 05:09:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

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
