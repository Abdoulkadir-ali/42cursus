/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 14:26:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/14 22:21:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


int	check_syntax(t_nodes *tokens)
{
	t_nodes	*curr;
	t_token	*tok;
	t_token	*nxt;
	int		d;

	curr = tokens;
	d = 0;
	if (check_initial_token(tokens))
		return (2);
	while (curr)
	{
		tok = (t_token *)curr->content;
		nxt = (curr->next) ? (t_token *)curr->next->content : NULL;
		if (handle_lparen(tok, nxt, &d))
			return (2);
		if (handle_rparen(tok, nxt, &d))
			return (2);
		if (handle_pipe_and_logic(tok, nxt))
			return (2);
		if (handle_semicolon(tok, nxt))
			return (2);
		if (handle_redirection(tok, nxt))
			return (2);
		curr = curr->next;
	}
	if (d != 0)
		return (print_syntax_error("newline"));
	return (0);
}
