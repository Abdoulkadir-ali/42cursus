/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 05:32:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:38:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Handle a word token during command scanning.
 */
static void	process_word_token(t_token *tok, int *seen_word, bool *is_quoted,
		t_cmd *cmd)
{
	if (!*seen_word)
	{
		*seen_word = 1;
		*is_quoted = tok->quoted;
	}
	cmd->count++;
}

/**
 * @brief Handle a prefix token during command scanning.
 */
static void	process_prefix_token(t_token *tok, int seen_word, t_cmd *cmd)
{
	(void)tok;
	if (seen_word)
		cmd->count++;
	else
		cmd->prefix_count++;
}

/**
 * @brief Handle redirection skipping during command scanning.
 */
static t_nodes	*process_sep_tokens(t_nodes *curr)
{
	t_token	*tok;

	tok = (t_token *)curr->content;
	if (is_redirection(tok->type) && curr->next)
		return (curr->next);
	return (curr);
}

/**
 * @brief Scan a token list to count arguments and prefixes for a command.
 * @param tokens Token list starting at the command segment.
 * @param cmd Output structure filled with counts for args and prefixes.
 * @param is_quoted Output flag set when the first word is quoted.
 */
void	scan_command_tokens(t_nodes *tokens, t_cmd *cmd, bool *is_quoted)
{
	t_nodes	*curr;
	int		seen_word;

	cmd->count = 0;
	cmd->prefix_count = 0;
	seen_word = 0;
	curr = tokens;
	while (curr && !cmp_node_type(curr, TOKEN_PIPE))
	{
		if (cmp_tok_type(curr->content, TOKEN_WORD))
			process_word_token(curr->content, &seen_word, is_quoted, cmd);
		else if (cmp_tok_type(curr->content, TOKEN_PREFIX))
			process_prefix_token(curr->content, seen_word, cmd);
		else
			curr = process_sep_tokens(curr);
		curr = curr->next;
	}
}
