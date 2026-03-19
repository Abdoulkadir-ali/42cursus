/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:48:17 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 05:46:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * @brief Tokenize one input line and reject it on syntax failure.
 * @param line Raw command line received from the input layer.
 * @param state Active shell state used for status propagation.
 * @return Token list on success, or NULL on tokenization or syntax failure.
 */
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

/**
 * @brief Detach one semicolon-delimited segment from the token stream.
 * @param cursor Current token node where segment extraction starts.
 * @param pnext Output slot receiving the next segment start.
 * @return Head of the extracted segment token list.
 */
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

/**
 * @brief Iterate over all semicolon-separated segments in one token list.
 * @param tokens Token list produced from one input line.
 * @param state Active shell state used during segment handling.
 * @return This function does not return a value.
 */
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
			if (!try_handle_assignment_public(segment, state))
				execute_ast(segment, state);
		}
		cursor = next_cursor;
	}
}

/**
 * @brief Process one raw command line through tokenization and execution.
 * @param line Raw command line from the input reader.
 * @param state Active shell state shared across the shell session.
 * @return This function does not return a value.
 */
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
