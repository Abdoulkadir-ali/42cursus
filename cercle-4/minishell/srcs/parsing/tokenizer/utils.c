/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@local>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:00:00 by copilot           #+#    #+#             */
/*   Updated: 2026/01/14 20:00:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_redirection(t_token_type type)
{
    return (type == TOKEN_RED_IN || type == TOKEN_RED_OUT
        || type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

int	print_syntax_error(char *token)
{
    ft_puterror("syntax error near unexpected token `%s'\n", token);
    return (2);
}

int	check_initial_token(t_nodes *tokens)
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


