/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:01:48 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:09:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Remove internal escape markers left by glob preparation.
 * @param s Expanded token string modified in place.
 * @return This function does not return a value.
 */
static void	strip_glob_escapes(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\001')
		{
			i++;
			continue ;
		}
		s[j++] = s[i++];
	}
	s[j] = '\0';
}

/**
 * @brief Finalize one expanded token, including wildcard expansion when needed.
 * @param exp Token-expansion context being rebuilt.
 * @param exp_tok Expanded token content under consideration.
 * @param exp_curr Token-list node currently being processed.
 * @return This function does not return a value.
 */
static void	process_expanded_token(t_token_expansion *exp, t_token *exp_tok,
		t_nodes *exp_curr)
{
	t_nodes	*matches;

	exp_tok->type = TOKEN_WORD;
	if (!exp_tok->quoted && is_wildcard(exp_tok->value))
	{
		matches = expand_wildcard(exp_tok->value);
		if (matches)
			process_matches_or_literal(exp, matches, exp_tok, exp_curr);
		else
		{
			strip_glob_escapes(exp_tok->value);
			append_node(&exp->head, &exp->tail, exp_curr);
		}
	}
	else
	{
		strip_glob_escapes(exp_tok->value);
		append_node(&exp->head, &exp->tail, exp_curr);
	}
}

/**
 * @brief Consume every token produced by word expansion and split.
 * @param exp Token-expansion context being rebuilt.
 * @param expanded_list Token list produced by `expand_and_split`.
 * @return This function does not return a value.
 */
static void	process_expanded_list(t_token_expansion *exp,
		t_nodes *expanded_list)
{
	t_nodes	*exp_curr;
	t_nodes	*exp_next;
	t_token	*exp_tok;

	exp_curr = expanded_list;
	while (exp_curr)
	{
		exp_next = exp_curr->next;
		exp_tok = (t_token *)exp_curr->content;
		process_expanded_token(exp, exp_tok, exp_curr);
		exp_curr = exp_next;
	}
}

/**
 * @brief Expand one word token unless it belongs to a heredoc delimiter.
 * @param exp Token-expansion context being rebuilt.
 * @param curr Current token-list node.
 * @param env Environment array used for variable and tilde expansion.
 * @param status Last shell exit status used during expansion.
 * @return This function does not return a value.
 */
static void	handle_word_node(t_token_expansion *exp, t_nodes *curr, char **env,
		int status)
{
	t_token	*tok;
	t_nodes	*expanded_list;

	tok = (t_token *)curr->content;
	if (is_prev_heredoc(exp->prev))
	{
		append_node(&exp->head, &exp->tail, curr);
		exp->prev = exp->tail;
		return ;
	}
	apply_tilde_expansion(tok, env);
	expanded_list = expand_and_split(tok->value, env, status);
	process_expanded_list(exp, expanded_list);
	del_token(curr->content);
	free(curr);
}

/**
 * @brief Expand every word token in a token list and rebuild the stream.
 * @param tokens Address of the token list that must be rewritten.
 * @param env Environment array used for expansion.
 * @param status Last shell exit status used during expansion.
 * @return Non-zero when expansion reported an error, otherwise 0.
 */
int	expand_tokens(t_nodes **tokens, char **env, int status)
{
	t_token_expansion	exp;
	t_nodes				*curr;
	t_nodes				*next;

	ft_bzero(&exp, sizeof(exp));
	curr = *tokens;
	while (curr)
	{
		next = curr->next;
		if (((t_token *)curr->content)->type == TOKEN_WORD)
			handle_word_node(&exp, curr, env, status);
		else
		{
			append_node(&exp.head, &exp.tail, curr);
			exp.prev = exp.tail;
		}
		curr = next;
		if (exp.prev == NULL && exp.tail)
			exp.prev = exp.tail;
	}
	*tokens = exp.head;
	return (exp.expansion_error);
}
