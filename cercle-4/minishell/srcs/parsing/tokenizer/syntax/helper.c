/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 14:26:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 03:33:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	syntax_handle_lparen(t_token *tok, t_token *nxt, int *depth)
{
	if (tok->type != TOKEN_LPAREN)
		return (0);
	(*depth)++;
	if (nxt && (nxt->type == TOKEN_RPAREN || nxt->type == TOKEN_PIPE
			|| nxt->type == TOKEN_AND || nxt->type == TOKEN_OR
			|| nxt->type == TOKEN_SEMICOLON))
		return (print_syntax_error(nxt->value));
	return (0);
}

int	syntax_handle_rparen(t_token *tok, t_token *nxt, int *depth)
{
	if (tok->type != TOKEN_RPAREN)
		return (0);
	if (--(*depth) < 0)
		return (print_syntax_error(")"));
	if (nxt && (nxt->type == TOKEN_WORD || nxt->type == TOKEN_LPAREN))
		return (print_syntax_error(nxt->value));
	return (0);
}

int	syntax_handle_pipe_and_logic(t_token *tok, t_token *nxt)
{
	if (tok->type != TOKEN_PIPE && tok->type != TOKEN_AND
		&& tok->type != TOKEN_OR)
		return (0);
	if (!nxt || nxt->type == TOKEN_PIPE || nxt->type == TOKEN_AND
		|| nxt->type == TOKEN_OR || nxt->type == TOKEN_SEMICOLON
		|| nxt->type == TOKEN_RPAREN)
		return (print_syntax_error(tok->value));
	return (0);
}

int	syntax_handle_semicolon(t_token *tok, t_token *nxt)
{
	if (tok->type != TOKEN_SEMICOLON)
		return (0);
	if (nxt && (nxt->type == TOKEN_PIPE || nxt->type == TOKEN_AND
			|| nxt->type == TOKEN_OR || nxt->type == TOKEN_SEMICOLON))
		return (print_syntax_error(nxt->value));
	return (0);
}

int	syntax_handle_redirection(t_token *tok, t_token *nxt)
{
	if (!is_redirection(tok->type) || tok->expanded)
		return (0);
	if (!nxt || nxt->type != TOKEN_WORD)
	{
		if (nxt)
			return (print_syntax_error(nxt->value));
		return (print_syntax_error("newline"));
	}
	return (0);
}
