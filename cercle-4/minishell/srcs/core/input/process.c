/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:48:17 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 04:04:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	process_input(char *line, char ***envp, int *exit_code)
{
	t_nodes	*tokens;
	t_nodes	*cursor;
	t_nodes	*next_cursor;
	t_nodes	*segment;

	if (!*line || is_whitespace_only(line))
		return ;
	add_history(line);
	tokens = tokenizer(line);
	if (!tokens)
	{
		*exit_code = 2;
		return ;
	}
	if (debug_dump_tokens_and_consume(&tokens))
		return ;
	if (check_syntax_and_consume(tokens, exit_code))
		return ;
	cursor = tokens;
	while (cursor)
	{
		next_cursor = NULL;
		segment = extract_segment(cursor, &next_cursor);
		if (segment)
		{
			debug_dump_segment(segment);
			if (try_handle_assignment_public(segment, envp, exit_code))
			{
				cursor = next_cursor;
				continue ;
			}
			if (process_segment_public(segment, envp, exit_code))
			{
				cursor = next_cursor;
				continue ;
			}
		}
		cursor = next_cursor;
	}
}
