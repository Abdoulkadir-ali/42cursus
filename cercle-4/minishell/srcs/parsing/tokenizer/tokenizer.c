/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 03:04:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:18:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Determine if a token consists of purely digits for IO redirection.
 * @param token Token to inspect.
 * @return true if the token value is numeric, otherwise false.
 */
static bool	is_numeric_token(t_token *token)
{
	size_t	i;

	if (!token || !token->value || !token->value[0])
		return (false);
	i = 0;
	while (token->value[i])
	{
		if (!ft_isdigit(token->value[i]))
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Consume any spaces and shell comments up to the next token.
 * @param pstr Address of current scan cursor.
 * @return true if string is exhausted after skip, otherwise false.
 */
static bool	skip_spaces_and_comments(char **pstr)
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
 * @brief Combine a leading numeric token with a redirection (e.g. 2>).
 * @param pstr Address of current scan cursor.
 * @param token Leading word token to check for digit-status.
 * @return Final token object after potential merge.
 */
static t_token	*handle_numeric_redirections(char **pstr, t_token *token)
{
	t_token	*redir;
	char	*tmp;

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
	return (token);
}

/**
 * @brief Fetch the next token from the input, handling word vs operator logic.
 * @param pstr Address of current scan cursor.
 * @return Newly allocated token or NULL on error.
 */
static t_token	*get_next_token(char **pstr)
{
	if (ft_strchr("|<>()&", **pstr) || **pstr == ';')
		return (handle_separator(pstr));
	return (handle_numeric_redirections(pstr, handle_word(pstr)));
}

/**
 * @brief Convert input command string into a linked list of tokens.
 * @param str Input raw string.
 * @return List of tokens, or NULL on error.
 */
t_nodes	*tokenizer(char *str)
{
	t_nodes	*tokens;
	t_nodes	*new_node;
	t_token	*token;

	tokens = NULL;
	while (*str)
	{
		if (skip_spaces_and_comments(&str))
			break ;
		token = get_next_token(&str);
		if (!token)
			return (ft_lstclear(&tokens, del_token), NULL);
		new_node = ft_lstnew(token);
		if (!new_node)
		{
			del_token(token);
			return (ft_lstclear(&tokens, del_token), NULL);
		}
		ft_lstadd_back(&tokens, new_node);
	}
	return (tokens);
}
