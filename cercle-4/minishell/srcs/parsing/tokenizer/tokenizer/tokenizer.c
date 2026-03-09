/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 03:04:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:24:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Wrap one token object into a list node and append it to the stream.
 * @param tokens Address of the token-list head.
 * @param token Newly allocated token object.
 * @return 1 on success, 0 on allocation failure.
 */
static int	add_token_to_list(t_nodes **tokens, t_token *token)
{
	t_nodes	*new_node;

	new_node = ft_lstnew(token);
	if (!new_node)
	{
		del_token(token);
		return (0);
	}
	ft_lstadd_back(tokens, new_node);
	return (1);
}

/**
 * @brief Check whether a token value contains only decimal digits.
 * @param token Token under inspection.
 * @return 1 when the token is purely numeric, otherwise 0.
 */
static int	is_numeric_token(t_token *token)
{
	int	i;

	i = 0;
	if (!token || !token->value || !token->value[0])
		return (0);
	while (token->value[i])
	{
		if (!ft_isdigit(token->value[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Skip leading spaces and shell comments before tokenization.
 * @param pstr Address of the scan cursor in the input string.
 * @return 1 when the string is exhausted after skipping, otherwise 0.
 */
static int	skip_spaces_and_comments(char **pstr)
{
	char	*s;

	s = *pstr;
	while (1)
	{
		while (*s && ft_isspace(*s))
			s++;
		if (!*s)
			break ;
		if (*s == '#')
		{
			while (*s && *s != '\n')
				s++;
			if (!*s)
				break ;
			continue ;
		}
		break ;
	}
	*pstr = s;
	return (!*s);
}

/**
 * @brief Extract the next token from the current scan position.
 * @param pstr Address of the scan cursor in the input string.
 * @return Newly allocated token, or NULL on failure.
 */
static t_token	*get_next_token(char **pstr)
{
	t_token	*token;
	t_token	*redir;
	char	*tmp;

	if (ft_strchr("|<>()&", **pstr) || **pstr == ';')
		token = handle_separator(pstr);
	else
	{
		token = handle_word(pstr);
		if (token && token->type == TOKEN_WORD && !token->quoted
			&& is_numeric_token(token) && **pstr && ft_strchr("<>", **pstr))
		{
			redir = handle_separator(pstr);
			if (redir)
			{
				tmp = ft_strjoin(token->value, redir->value);
				free(token->value);
				token->value = tmp;
				token->type = redir->type;
				del_token(redir);
			}
		}
	}
	return (token);
}

/**
 * @brief Convert one input string into a linked list of shell tokens.
 * @param str Raw command line to tokenize.
 * @return Token list on success, or NULL on allocation or parse failure.
 */
t_nodes	*tokenizer(char *str)
{
	t_nodes	*tokens;
	t_token	*token;

	tokens = NULL;
	while (*str)
	{
		if (skip_spaces_and_comments(&str))
			break ;
		token = get_next_token(&str);
		if (!token)
		{
			ft_lstclear(&tokens, del_token);
			return (NULL);
		}
		if (!add_token_to_list(&tokens, token))
		{
			ft_lstclear(&tokens, del_token);
			return (NULL);
		}
	}
	return (tokens);
}
