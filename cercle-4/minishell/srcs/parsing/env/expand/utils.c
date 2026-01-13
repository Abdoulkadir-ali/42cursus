/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:02:01 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 02:26:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_prev_heredoc(t_nodes *prev)
{
	if (!prev)
		return (0);
	return (((t_token *)prev->content)->type == TOKEN_HEREDOC);
}

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

