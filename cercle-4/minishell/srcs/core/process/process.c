/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:48:17 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 22:55:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int	process_segment_public(t_nodes *segment, char ***envp,
		int *exit_code)
{
	if (expand_and_check_error(&segment, *envp, *exit_code, exit_code))
		return (1);
	execute_ast(segment, envp, exit_code);
	return (0);
}

static t_nodes	*tokenize_and_check(char *line, int *exit_code)
{
	t_nodes	*tokens;

	tokens = tokenizer(line);
	if (!tokens)
	{
		*exit_code = 2;
		return (NULL);
	}
	if (debug_dump_tokens_and_consume(&tokens))
		return (NULL);
	if (check_syntax_and_consume(tokens, exit_code))
		return (NULL);
	return (tokens);
}

static void	process_segments(t_nodes *tokens, char ***envp, int *exit_code)
{
	t_nodes	*cursor;
	t_nodes	*next_cursor;
	t_nodes	*segment;

	cursor = tokens;
	while (cursor)
	{
		next_cursor = NULL;
		segment = extract_segment(cursor, &next_cursor);
		if (segment)
		{
			debug_dump_segment(segment);
			if (try_handle_assignment_public(segment, envp, exit_code)
				|| process_segment_public(segment, envp, exit_code))
			{
				cursor = next_cursor;
				continue ;
			}
		}
		cursor = next_cursor;
	}
}

void	process_input(char *line, char ***envp, int *exit_code)
{
	t_nodes	*tokens;

	if (!*line || is_whitespace_only(line))
		return ;
	add_history(line);
	tokens = tokenize_and_check(line, exit_code);
	if (!tokens)
		return ;
	process_segments(tokens, envp, exit_code);
}
