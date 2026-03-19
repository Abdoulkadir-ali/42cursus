/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 07:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:32:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_three_repeated(const char *s, char c)
{
	int		count;
	char	rep[3];

	count = 0;
	while (s[count] == c)
		count++;
	if (count < 3)
		return (0);
	rep[0] = c;
	if (count % 2 == 1)
	{
		rep[1] = '\0';
		rep[2] = '\0';
	}
	else
	{
		rep[1] = c;
		rep[2] = '\0';
	}
	return (print_syntax_error(rep));
}

bool	set_token_and_advance(t_token *token, t_token_type type, char **str,
		size_t len)
{
	token->type = type;
	token->value = ft_strldup(*str, len);
	if (!token->value)
		return (false);
	*str += len;
	return (true);
}

bool	handle_basic_ops(char **str, t_token *token)
{
	if (**str == '|')
	{
		if ((*str)[1] == '|')
			return (set_token_and_advance(token, TOKEN_OR, str, 2));
		return (set_token_and_advance(token, TOKEN_PIPE, str, 1));
	}
	if (**str == '&')
	{
		if ((*str)[1] == '&')
			return (set_token_and_advance(token, TOKEN_AND, str, 2));
		return (set_token_and_advance(token, TOKEN_BACKGROUND, str, 1));
	}
	return (false);
}

bool	handle_redirs(char **str, t_token *token)
{
	if (**str == '<')
	{
		if ((*str)[1] == '<')
		{
			if ((*str)[2] == '<')
				return (set_token_and_advance(token, TOKEN_HERESTR, str, 3));
			return (set_token_and_advance(token, TOKEN_HEREDOC, str, 2));
		}
		return (set_token_and_advance(token, TOKEN_RED_IN, str, 1));
	}
	if (**str == '>')
	{
		if ((*str)[1] == '>')
			return (set_token_and_advance(token, TOKEN_APPEND, str, 2));
		if ((*str)[1] == '|')
			return (set_token_and_advance(token, TOKEN_RED_OUT, str, 2));
		return (set_token_and_advance(token, TOKEN_RED_OUT, str, 1));
	}
	return (false);
}

bool	try_handle_punctuation(char **str, t_token *tok)
{
	t_token_type	type;
	size_t			len;

	if (!ft_strchr("();", **str))
		return (false);
	if (**str == '(')
		type = TOKEN_LPAREN;
	else if (**str == ')')
		type = TOKEN_RPAREN;
	else
		type = TOKEN_SEMICOLON;
	len = 1;
	if (**str == ';' && (*str)[1] == ';')
		len = 2;
	return (set_token_and_advance(tok, type, str, len));
}
