/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:49:07 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 13:21:47 by abdoali          ###   ########.fr       */
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

static t_token	*extract_token_value(char *str, int state)
{
	t_token	*token;
	char	*new;
	int		len;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	new = NULL;
	if (state == STATE_GENERAL)
		new = ft_strldup(str, ft_strmatch(str, "'\" |<>", &str_any));
	else if (state == STATE_SINGLE_QUOTES || state == STATE_DOUBLE_QUOTES)
	{
		len = ft_strchri(str + 1, *str);
		if (len != -1)
			new = ft_strldup(str, len + 2);
	}
	if (!new || !*new)
	{
		free(token);
		if (new)
			free(new);
		return (NULL);
	}
	token->value = new;
	token->type = state;
	return (token);
}

static t_token	*handle_separator(char **str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
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
	int		state;
	t_token	*token;

	state = STATE_GENERAL;
	if (**str == '\'')
		state = STATE_SINGLE_QUOTES;
	else if (**str == '"')
		state = STATE_DOUBLE_QUOTES;
	token = extract_token_value(*str, state);
	if (!token)
		return (NULL);
	token->type = TOKEN_WORD;
	*str += ft_strlen(token->value);
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
