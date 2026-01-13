/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:53:32 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 22:54:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	check_syntax_and_consume(t_nodes *tokens, int *exit_code)
{
	if (!check_syntax(tokens))
		return (0);
	consume_heredocs(tokens);
	*exit_code = 2;
	ft_lstclear(&tokens, del_token);
	return (1);
}

t_nodes	*extract_segment(t_nodes *cursor, t_nodes **pnext)
{
	t_nodes	*segment;
	t_nodes	*seg_tail;
	t_nodes	*it;

	initialize_segment_builder(&segment, &seg_tail, &it, cursor);
	build_segment_until_semicolon(&segment, &seg_tail, &it);
	consume_semicolon_if_present(it, pnext);
	return (segment);
}

int	try_handle_assignment_local(t_nodes *segment, char ***envp, int *exit_code)
{
	t_token	*first_tok;
	char	*eq;

	if (!check_if_assignment_candidate(segment, &first_tok, &eq))
		return (0);
	if (!validate_identifier(first_tok->value))
		return (0);
	if (segment->next)
	{
		return (0);
	}
	perform_assignment(first_tok, eq, envp, exit_code);
	ft_lstclear(&segment, del_token);
	return (1);
}
