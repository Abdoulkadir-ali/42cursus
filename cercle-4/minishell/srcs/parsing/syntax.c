/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 14:26:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/12 02:37:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_redirection(t_token_type type)
{
	return (type == TOKEN_RED_IN || type == TOKEN_RED_OUT ||
			type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

static int	print_syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
	return (2); // Standard bash syntax error code
}

int	check_syntax(t_nodes *tokens)
{
	t_nodes	*curr;
	t_token	*tok;
	t_token	*next_tok;

	curr = tokens;
	if (!curr)
		return (0);
	  // Check first token: Cannot be PIPE/SEMICOLON/AND/OR
	  tok = (t_token *)curr->content;
	  if (tok->type == TOKEN_PIPE)
		  return (print_syntax_error("|"));
	  if (tok->type == TOKEN_SEMICOLON)
		  return (print_syntax_error(";"));
	  if (tok->type == TOKEN_AND || tok->type == TOKEN_OR)
		  return (print_syntax_error(tok->value));
	
	while (curr)
	{
		tok = (t_token *)curr->content;
		if (curr->next)
			next_tok = (t_token *)curr->next->content;
		else
			next_tok = NULL;

		  if (tok->type == TOKEN_PIPE)
		{
			if (!next_tok) // Trailing Pipe
				return (print_syntax_error("|")); // Or "newline" if implementing multi-line
			if (next_tok->type == TOKEN_PIPE) // Double Pipe
				return (print_syntax_error("|"));
			if (next_tok->type == TOKEN_SEMICOLON)
				return (print_syntax_error(";"));
		}
		  else if (tok->type == TOKEN_AND || tok->type == TOKEN_OR)
		  {
			  if (!next_tok)
				  return (print_syntax_error(tok->value));
			  if (next_tok->type == TOKEN_SEMICOLON)
				  return (print_syntax_error(";"));
			  if (next_tok->type == TOKEN_PIPE)
				  return (print_syntax_error("|"));
			  if (next_tok->type == TOKEN_AND || next_tok->type == TOKEN_OR)
				  return (print_syntax_error(tok->value));
		  }
		else if (tok->type == TOKEN_SEMICOLON)
		{
			if (next_tok && next_tok->type == TOKEN_SEMICOLON)
				return (print_syntax_error(";"));
			if (next_tok && next_tok->type == TOKEN_PIPE)
				return (print_syntax_error("|"));
		}
		else if (is_redirection(tok->type) && (!tok->expanded))
		{
			if (!next_tok) // Trailing Redirection
				return (print_syntax_error("newline"));
			if (next_tok->type != TOKEN_WORD) // Redir followed by non-word
				return (print_syntax_error(next_tok->value));
		}
		curr = curr->next;
	}
	return (0);
}
