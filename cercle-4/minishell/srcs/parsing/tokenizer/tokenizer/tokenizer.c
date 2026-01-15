/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 03:04:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 03:35:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
