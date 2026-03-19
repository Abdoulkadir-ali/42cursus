/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 01:36:43 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:41:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Process a token while collecting command arguments.
 * @param pcurr Address of the current token-list node pointer; may be
 * advanced when a redirection consumes the next token.
 * @param args Destination array receiving duplicated argument strings.
 * @param pi Address of the current insert index in `args`.
 * @param pseen_word Address of the seen-word flag used to distinguish
 * prefixes from arguments.
 * @return Always returns 0 (compatibility with callers).
 */
static int	process_token_for_args(t_nodes **pcurr, char **args, size_t *pi,
		int *pseen_word)
{
	t_token	*tok;
	t_nodes	*curr;

	curr = *pcurr;
	tok = (t_token *)curr->content;
	if (cmp_tok_type(tok, TOKEN_WORD))
	{
		*pseen_word = 1;
		if (args)
			args[(*pi)++] = ft_strdup(tok->value);
	}
	else if (cmp_tok_type(tok, TOKEN_PREFIX) && *pseen_word)
	{
		if (args)
			args[(*pi)++] = ft_strdup(tok->value);
	}
	else if (is_redirection(tok->type) && curr->next)
		*pcurr = curr->next;
	return (0);
}

/**
 * @brief Fill the argv array with tokens until a pipe or list end.
 * @param tokens Token list for the command segment.
 * @param args Preallocated array to receive duplicated strings.
 */
static void	fill_cmd_args(t_nodes *tokens, char **args)
{
	t_nodes	*curr;
	size_t	i;
	int		seen_word;

	i = 0;
	seen_word = 0;
	curr = tokens;
	while (curr && !cmp_node_type(curr, TOKEN_PIPE))
	{
		process_token_for_args(&curr, args, &i, &seen_word);
		curr = curr->next;
	}
	if (args)
		args[i] = NULL;
}

/**
 * @brief Build an argv-style array from tokens for a single command.
 * @param tokens Token list representing the command segment.
 * @param count Number of arguments expected (allocated size).
 * @return Newly allocated NULL-terminated array of strings, or NULL.
 */
char	**build_args_from_tokens(t_nodes *tokens, size_t count)
{
	char	**args;

	args = ft_calloc(count + 1, sizeof(char *));
	if (!args)
		return (NULL);
	fill_cmd_args(tokens, args);
	return (args);
}

/**
 * @brief Collect leading assignment prefixes from a token list.
 * @param tokens Token list to scan for prefix tokens.
 * @param count Maximum number of prefixes expected.
 * @return Newly allocated NULL-terminated array of prefix strings.
 */
char	**collect_prefixes(t_nodes *tokens, size_t count)
{
	char	**arr;
	size_t	i;
	t_nodes	*curr;
	t_token	*tok;

	arr = ft_calloc(count + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	curr = tokens;
	while (curr && i < count)
	{
		tok = (t_token *)curr->content;
		if (cmp_tok_type(tok, TOKEN_PREFIX))
			arr[i++] = ft_strdup(tok->value);
		else if (is_redirection(tok->type) && curr->next)
			curr = curr->next;
		else if (tok->type == TOKEN_WORD)
			break ;
		curr = curr->next;
	}
	arr[i] = NULL;
	return (arr);
}
