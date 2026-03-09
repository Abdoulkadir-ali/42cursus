/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 14:26:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:24:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Validate an opening parenthesis and update nesting depth.
 * @param tok Current token under inspection.
 * @param nxt Next token in the stream, or NULL.
 * @param depth Parenthesis depth updated in place.
 * @return Syntax status code, or 0 when this rule passes.
 */
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

/**
 * @brief Validate a closing parenthesis and update nesting depth.
 * @param tok Current token under inspection.
 * @param nxt Next token in the stream, or NULL.
 * @param depth Parenthesis depth updated in place.
 * @return Syntax status code, or 0 when this rule passes.
 */
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

/**
 * @brief Reject invalid follow-up tokens after pipe and logical operators.
 * @param tok Current token under inspection.
 * @param nxt Next token in the stream, or NULL.
 * @return Syntax status code, or 0 when this rule passes.
 */
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

/**
 * @brief Reject invalid token sequences that follow a semicolon.
 * @param tok Current token under inspection.
 * @param nxt Next token in the stream, or NULL.
 * @return Syntax status code, or 0 when this rule passes.
 */
int	syntax_handle_semicolon(t_token *tok, t_token *nxt)
{
	if (tok->type != TOKEN_SEMICOLON)
		return (0);
	if (nxt && (nxt->type == TOKEN_PIPE || nxt->type == TOKEN_AND
			|| nxt->type == TOKEN_OR || nxt->type == TOKEN_SEMICOLON))
	{
		if (nxt->type == TOKEN_SEMICOLON)
		{
			if (nxt->value && ft_strlen(nxt->value) > 1)
				return (print_syntax_error(nxt->value));
			return (print_syntax_error(";"));
		}
		return (print_syntax_error(nxt->value));
	}
	return (0);
}

/**
 * @brief Ensure a redirection operator is followed by a word token.
 * @param tok Current token under inspection.
 * @param nxt Next token in the stream, or NULL.
 * @return Syntax status code, or 0 when this rule passes.
 */
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
