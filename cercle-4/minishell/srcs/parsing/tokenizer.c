/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:49:07 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 16:08:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

static char	*get_chunk(char **str, int *quoted)
{
	char	*chunk;
	int		len;

	if (**str == '\'' || **str == '"')
	{
		*quoted = 1;
		len = ft_strchri(*str + 1, **str);
		if (len == -1)
			len = ft_strlen(*str) - 1;
		chunk = ft_substr(*str, 0, len + 2);
		*str += len + 2;
	}
	else
	{
		len = ft_strmatch(*str, "'\" |<>", &str_any);
		chunk = ft_strldup(*str, len);
		*str += len;
	}
	return (chunk);
}

static t_token	*handle_separator(char **str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->quoted = 0;
	if (**str == '|')
	{
		token->type = TOKEN_PIPE;
		token->value = ft_strldup(*str, 1);
		(*str)++;
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
		else
		{
			token->type = TOKEN_RED_OUT;
			token->value = ft_strldup(*str, 1);
			(*str)++;
		}
	}
	return (token);
}

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
		if (ft_isspace(**str) || ft_strchr("|<>", **str))
			break ;
		chunk = get_chunk(str, &quoted);
		if (!chunk)
			break ;
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
	return (token);
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

t_nodes	*tokenizer(char *str)
{
	t_nodes	*tokens;
	t_token	*token;

	tokens = NULL;
	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (!*str)
			break ;
		if (ft_strchr("|<>", *str))
			token = handle_separator(&str);
		else
			token = handle_word(&str);
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
