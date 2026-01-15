/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:49:07 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/14 22:22:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


static t_token	*handle_word(char **str)
{
	t_token	*token;
	char	*acc;
	char	*chunk;
	char	*tmp;
	int		quoted;

	acc = ft_strdup("");
	quoted = 0;
	while (**str)
	{
		if (ft_isspace(**str) || ft_strchr("|<>()", **str) || **str == ';')
			break ;
		if (**str == '$' && ((*str)[1] == '"' || (*str)[1] == '\''))
		{
			(*str)++;
			continue ;
		}
		chunk = get_chunk(str, &quoted);
		if (!chunk)
			return (free(acc), NULL);
		tmp = ft_strjoin(acc, chunk);
		free(acc);
		free(chunk);
		acc = tmp;
	}
	token = malloc(sizeof(t_token));
	if (!token)
		return (free(acc), NULL);
	token->type = TOKEN_WORD;
	token->value = acc;
	token->quoted = quoted;
	token->expanded = 0;
	return (token);
}

static char	*get_chunk(char **str, int *quoted)
{
	char	*chunk;
	int		i;
	char	quote;
	int		closed;

	i = 0;
	if (**str == '\'' || **str == '"')
	{
		quote = **str;
		*quoted = 1;
		i++;
		closed = 0;
		while ((*str)[i])
		{
			if ((*str)[i] == quote)
			{
				closed = 1;
				i++;
				break ;
			}
			if (quote == '"' && (*str)[i] == '\\' && (*str)[i + 1])
				i++;
			i++;
		}
		if (!closed)
		{
			ft_puterror("syntax error: unclosed quote\n");
			return (NULL);
		}
	}
	else
	{
		while ((*str)[i])
		{
			if (ft_isspace((*str)[i]) || ft_strchr("|<>()&", (*str)[i])
				|| (*str)[i] == ';' || (*str)[i] == '\'' || (*str)[i] == '"')
				break ;
			if ((*str)[i] == '\\' && (*str)[i + 1])
				i++;
			i++;
		}
	}
	chunk = ft_substr(*str, 0, i);
	*str += i;
	return (chunk);
}

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

t_nodes	*tokenizer(char *str)
{
	t_nodes	*tokens;
	t_token	*token;
	t_token	*redir;
	char	*tmp;

	tokens = NULL;
	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (!*str)
			break ;
		if (*str == '#')
		{
			while (*str && *str != '\n')
				str++;
			continue ;
		}
		if (ft_strchr("|<>()&", *str) || *str == ';')
			token = handle_separator(&str);
		else
		{
			token = handle_word(&str);
			if (token && token->type == TOKEN_WORD && !token->quoted
				&& is_numeric_token(token) && *str && ft_strchr("<>", *str))
			{
				redir = handle_separator(&str);
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
