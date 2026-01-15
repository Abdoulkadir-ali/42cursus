/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:49:07 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 03:37:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_token	*alloc_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->quoted = 0;
	token->expanded = 0;
	token->value = NULL;
	return (token);
}

static int	dispatch_separator(char **str, t_token *token)
{
	if (**str == '|')
		return (handle_pipe(str, token));
	if (**str == '(')
		return (handle_paren(str, token, 1));
	if (**str == ')')
		return (handle_paren(str, token, 0));
	if (**str == '&')
		return (handle_ampersand(str, token));
	if (**str == '<')
		return (handle_red_in(str, token));
	if (**str == '>')
		return (handle_red_out(str, token));
	if (**str == ';')
		return (handle_semicolon(str, token));
	return (1);
}

t_token	*handle_separator(char **str)
{
	t_token	*token;
	int		rc;

	if (!str || !*str || !**str)
		return (NULL);
	token = alloc_token();
	if (!token)
		return (NULL);
	rc = 0;
	rc = dispatch_separator(str, token);
	if (rc != 0)
	{
		free(token->value);
		free(token);
		return (NULL);
	}
	return (token);
}
