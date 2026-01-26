/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 06:14:56 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/25 23:48:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

char	*get_command_line(void)
{
	char	*line;
	char	*prompt;
	char	*trimmed;
	char	*handled;

	prompt = get_prompt(1);
	line = read_input(prompt);
	if (!line)
		return (NULL);
	trimmed = ft_strtrim(line, " \t");
	{
		handled = handle_parenthesis(line, trimmed);
		if (handled)
			return (handled);
	}
	return (handle_multiline_input(line));
}
