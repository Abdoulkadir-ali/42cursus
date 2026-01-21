/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:48:17 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/21 06:18:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static t_nodes	*tokenize_and_check(char *line, int *exit_code)
{
	t_nodes	*tokens;
	int		status;

	tokens = tokenizer(line);
	if (!tokens)
	{
		*exit_code = 2;
		return (NULL);
	}
	status = check_syntax(tokens);
	if (status != 0)
	{
		*exit_code = status;
		consume_heredocs(tokens);
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

static int	process_segment_internal(t_nodes *segment, char ***envp,
		int *exit_code)
{
	if (expand_and_check_error(&segment, *envp, *exit_code, exit_code))
		return (1);
	execute_ast(segment, envp, exit_code);
	return (0);
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
			if (try_handle_assignment_public(segment, envp, exit_code)
				|| process_segment_internal(segment, envp, exit_code))
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
	{
		if (!g_state.interactive_shell)
			exit(*exit_code);
		return ;
	}
	process_segments(tokens, envp, exit_code);
}
