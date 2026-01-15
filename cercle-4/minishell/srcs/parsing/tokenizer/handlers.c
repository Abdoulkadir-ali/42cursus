/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:49:07 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/14 22:21:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


static t_token	*handle_separator(char **str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->quoted = 0;
	if (**str == '|')
	{
		if (*(*str + 1) == '|')
		{
			token->type = TOKEN_OR;
			token->value = ft_strldup(*str, 2);
			(*str) += 2;
		}
		else
		{
			token->type = TOKEN_PIPE;
			token->value = ft_strldup(*str, 1);
			(*str)++;
		}
	}
	else if (**str == '(')
	{
		token->type = TOKEN_LPAREN;
		token->value = ft_strldup(*str, 1);
		(*str)++;
	}
	else if (**str == ')')
	{
		token->type = TOKEN_RPAREN;
		token->value = ft_strldup(*str, 1);
		(*str)++;
	}
	else if (**str == '&')
	{
		if (*(*str + 1) == '&')
		{
			token->type = TOKEN_AND;
			token->value = ft_strldup(*str, 2);
			(*str) += 2;
		}
		else
		{
			token->type = TOKEN_WORD;
			token->value = ft_strldup(*str, 1);
			(*str)++;
		}
	}
	else if (**str == '<')
	{
		if (*(*str + 1) == '<')
		{
			token->type = TOKEN_HEREDOC;
			token->value = ft_strldup(*str, 2);
			(*str) += 2;
		}
		else
		{
			token->type = TOKEN_RED_IN;
			token->value = ft_strldup(*str, 1);
			(*str)++;
		}
	}
	else if (**str == '>')
	{
		if (*(*str + 1) == '>')
		{
			token->type = TOKEN_APPEND;
			token->value = ft_strldup(*str, 2);
			(*str) += 2;
		}
		else if (*(*str + 1) == '|')
		{
			token->type = TOKEN_RED_OUT;
			token->value = ft_strldup(*str, 2);
			(*str) += 2;
		}
		else
		{
			token->type = TOKEN_RED_OUT;
			token->value = ft_strldup(*str, 1);
			(*str)++;
		}
	}
	else if (**str == ';')
	{
		token->type = TOKEN_SEMICOLON;
		token->value = ft_strldup(*str, 1);
		(*str)++;
	}
	token->expanded = 0;
	return (token);
}
