/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 14:26:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/14 17:47:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_redirection(t_token_type type)
{
	return (type == TOKEN_RED_IN || type == TOKEN_RED_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

static int	print_syntax_error(char *token)
{
	ft_puterror("syntax error near unexpected token `%s'\n", token);
	return (2);
}

int	check_syntax(t_nodes *tokens)
{
	t_nodes	*curr;
	t_token	*tok;
	t_token	*nxt;
	int		d;

	curr = tokens;
	d = 0;
	if (!curr)
		return (0);
	tok = (t_token *)curr->content;
	if (tok->type == TOKEN_PIPE || tok->type == TOKEN_SEMICOLON
		|| tok->type == TOKEN_AND || tok->type == TOKEN_OR)
		return (print_syntax_error(tok->value));
	while (curr)
	{
		tok = (t_token *)curr->content;
		nxt = (curr->next) ? (t_token *)curr->next->content : NULL;
		if (tok->type == TOKEN_LPAREN)
		{
			d++;
			if (nxt && (nxt->type == TOKEN_RPAREN || nxt->type == TOKEN_PIPE
					|| nxt->type == TOKEN_AND || nxt->type == TOKEN_OR
					|| nxt->type == TOKEN_SEMICOLON))
				return (print_syntax_error(nxt->value));
		}
		else if (tok->type == TOKEN_RPAREN)
		{
			if (--d < 0)
				return (print_syntax_error(")"));
			if (nxt && (nxt->type == TOKEN_WORD || nxt->type == TOKEN_LPAREN))
				return (print_syntax_error(nxt->value));
		}
		else if (tok->type == TOKEN_PIPE || tok->type == TOKEN_AND
			|| tok->type == TOKEN_OR)
		{
			if (!nxt || nxt->type == TOKEN_PIPE || nxt->type == TOKEN_AND
				|| nxt->type == TOKEN_OR || nxt->type == TOKEN_SEMICOLON
				|| nxt->type == TOKEN_RPAREN)
				return (print_syntax_error(tok->value));
		}
		else if (tok->type == TOKEN_SEMICOLON)
		{
			if (nxt && (nxt->type == TOKEN_PIPE || nxt->type == TOKEN_AND
				|| nxt->type == TOKEN_OR || nxt->type == TOKEN_SEMICOLON))
				return (print_syntax_error(nxt->value));
		}
		else if (is_redirection(tok->type) && !tok->expanded)
		{
			if (!nxt || nxt->type != TOKEN_WORD)
				return (print_syntax_error(nxt ? nxt->value : "newline"));
		}
		curr = curr->next;
	}
	if (d != 0)
		return (print_syntax_error("newline"));
	return (0);
}
