/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:02:01 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 02:12:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Check whether the previous token is a heredoc operator.
 * @param prev Previous token-list node in the expansion stream.
 * @return 1 when the previous token is `TOKEN_HEREDOC`, otherwise 0.
 */
bool	is_prev_heredoc(t_nodes *prev)
{
	if (!prev)
		return (false);
	return (cmp_node_type(prev, TOKEN_HEREDOC));
}

/**
 * @brief Apply tilde expansion to a token when shell rules allow it.
 * @param tok Token being expanded in place.
 * @param envp Environment array used to resolve `HOME`.
 * @return This function does not return a value.
 */
void	apply_tilde_expansion(t_token *tok, char **envp)
{
	char	*home;
	char	*new_val;

	if (!tok || !tok->value)
		return ;
	if (!tok->quoted && tok->value[0] == '~' && (tok->value[1] == '\0'
			|| tok->value[1] == '/'))
	{
		home = get_env_value("HOME", envp);
		new_val = ft_strjoin(home, tok->value + 1);
		free(home);
		free(tok->value);
		tok->value = new_val;
	}
}

/**
 * @brief Append one token-list node to the rebuilt output stream.
 * @param head Address of the rebuilt token-list head.
 * @param tail Address of the rebuilt token-list tail.
 * @param node Token-list node to append.
 * @return This function does not return a value.
 */
void	append_node(t_nodes **head, t_nodes **tail, t_nodes *node)
{
	if (!node)
		return ;
	node->next = NULL;
	if (!*head)
		*head = node;
	else
		(*tail)->next = node;
	*tail = node;
}

/**
 * @brief Convert one wildcard match string into a word token node.
 * @param match Matched path string.
 * @return Newly allocated token-list node, or NULL on allocation failure.
 */
t_nodes	*create_token_node_from_match(char *match)
{
	t_token	*new_tok;

	new_tok = malloc(sizeof(t_token));
	if (!new_tok)
		return (NULL);
	new_tok->type = TOKEN_WORD;
	new_tok->value = ft_strdup(match);
	new_tok->quoted = 0;
	new_tok->expanded = 1;
	return (ft_lstnew(new_tok));
}

/**
 * @brief Append one allocated chunk string to a growing result string.
 * @param res Address of the accumulated result string.
 * @param chunk Newly allocated chunk to append.
 * @return This function does not return a value.
 */
void	append_chunk(char **res, char *chunk)
{
	char	*tmp;

	if (!chunk)
		return ;
	if (!*res)
		*res = chunk;
	else
	{
		tmp = ft_strjoin(*res, chunk);
		free(*res);
		free(chunk);
		*res = tmp;
	}
}
