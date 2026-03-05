/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:48:17 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 23:01:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static t_nodes	*tokenize_and_check(char *line, t_shell_state *state)
{
	t_nodes	*tokens;
	int		status;

	tokens = tokenizer(line);
	if (!tokens)
	{
		state->exit_code = 2;
		return (NULL);
	}
	status = check_syntax(tokens);
	if (status != 0)
	{
		state->exit_code = status;
		consume_heredocs(tokens, state);
		ft_lstclear(&tokens, del_token);
		return (NULL);
	}
	return (tokens);
}

static t_nodes	*extract_segment(t_nodes *cursor, t_nodes **pnext)
{
	t_nodes	*segment;
	t_nodes	*seg_tail;
	t_nodes	*it;

	segment = NULL;
	seg_tail = NULL;
	it = cursor;
	build_segment_until_semicolon(&segment, &seg_tail, &it);
	consume_semicolon_if_present(it, pnext);
	return (segment);
}

static int	process_segment_internal(t_nodes *segment, t_shell_state *state)
{
	if (expand_and_check_error(&segment, state, &state->exit_code))
		return (1);
	execute_ast(segment, state);
	return (0);
}

static void	process_segments(t_nodes *tokens, t_shell_state *state)
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
			if (try_handle_assignment_public(segment, state)
				|| process_segment_internal(segment, state))
			{
				cursor = next_cursor;
				continue ;
			}
		}
		cursor = next_cursor;
	}
}

void	process_input(char *line, t_shell_state *state)
{
	t_nodes	*tokens;

	if (!*line || is_whitespace_only(line))
		return ;
	if (state->interactive_shell)
		add_history(line);
	tokens = tokenize_and_check(line, state);
	if (!tokens)
	{
		if (!state->interactive_shell)
			exit(state->exit_code);
		return ;
	}
	process_segments(tokens, state);
}
