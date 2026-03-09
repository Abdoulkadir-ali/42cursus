/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 14:26:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:24:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Reject unmatched opening parentheses after the scan completes.
 * @param d Final parenthesis depth after the full syntax pass.
 * @return Syntax status code.
 */
static int	check_remaining_depth(int d)
{
	if (d != 0)
		return (print_syntax_error("newline"));
	return (0);
}

/**
 * @brief Validate that the first token can legally start a command stream.
 * @param tokens Token list produced by the tokenizer.
 * @return Syntax status code, or 0 when the first token is valid.
 */
static int	check_initial_token(t_nodes *tokens)
{
	t_token	*tok;

	if (!tokens)
		return (0);
	tok = (t_token *)tokens->content;
	if (tok->type == TOKEN_PIPE || tok->type == TOKEN_SEMICOLON
		|| tok->type == TOKEN_AND || tok->type == TOKEN_OR)
		return (print_syntax_error(tok->value));
	return (0);
}

/**
 * @brief Run every per-token syntax rule against one token-list node.
 * @param curr Current node in the token list.
 * @param d Parenthesis depth updated in place.
 * @return 1 when a syntax error is detected, otherwise 0.
 */
static int	process_node(t_nodes *curr, int *d)
{
	t_token	*tok;
	t_token	*nxt;

	tok = (t_token *)curr->content;
	if (curr->next)
		nxt = (t_token *)curr->next->content;
	else
		nxt = NULL;
	if (syntax_handle_lparen(tok, nxt, d))
		return (1);
	if (syntax_handle_rparen(tok, nxt, d))
		return (1);
	if (syntax_handle_pipe_and_logic(tok, nxt))
		return (1);
	if (syntax_handle_semicolon(tok, nxt))
		return (1);
	if (syntax_handle_redirection(tok, nxt))
		return (1);
	return (0);
}

/**
 * @brief Scan the full token list and validate final trailing-token rules.
 * @param tokens Token list produced by the tokenizer.
 * @param d Initial parenthesis depth.
 * @return Syntax status code.
 */
static int	check_syntax_loop_and_last(t_nodes *tokens, int d)
{
	t_nodes	*curr;
	t_nodes	*last;
	t_token	*tok;

	curr = tokens;
	while (curr)
	{
		if (process_node(curr, &d))
			return (2);
		curr = curr->next;
	}
	if (tokens)
	{
		last = tokens;
		while (last->next)
			last = last->next;
		tok = (t_token *)last->content;
		if (tok->type == TOKEN_AND || tok->type == TOKEN_OR
			|| tok->type == TOKEN_PIPE)
		{
			print_syntax_error("newline");
			return (2);
		}
	}
	return (check_remaining_depth(d));
}

/**
 * @brief Validate the tokenizer output against shell syntax rules.
 * @param tokens Token list produced from one input line.
 * @return 0 when syntax is valid, otherwise the shell syntax error status.
 */
int	check_syntax(t_nodes *tokens)
{
	int	d;

	d = 0;
	if (check_initial_token(tokens))
		return (2);
	return (check_syntax_loop_and_last(tokens, d));
}
