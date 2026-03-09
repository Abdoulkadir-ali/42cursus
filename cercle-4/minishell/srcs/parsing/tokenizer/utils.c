/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 03:04:43 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:24:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Print a shell-style syntax error message for one token string.
 * @param token Token text reported in the syntax error message.
 * @return Shell syntax error status 2.
 */
int	print_syntax_error(char *token)
{
	ft_puterror("syntax error near unexpected token `%s'\n", token);
	return (2);
}

/**
 * @brief Release one token object and its owned value string.
 * @param content Token object passed through generic list cleanup helpers.
 * @return This function does not return a value.
 */
void	del_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (token)
	{
		if (token->value)
			free(token->value);
		free(token);
	}
}

/**
 * @brief Check whether a token type is one of the shell redirection operators.
 * @param type Token type under inspection.
 * @return 1 for redirection token types, otherwise 0.
 */
int	is_redirection(t_token_type type)
{
	return (type == TOKEN_RED_IN || type == TOKEN_RED_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC
		|| type == TOKEN_HERESTR);
}
