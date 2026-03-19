/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:49:07 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:05:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Initialize word collection and call the main loop.
 * @param str Address of the scan cursor.
 * @param quoted Pointer to boolean to set if any part is quoted.
 * @return Allocated word string or NULL on failure.
 */
char	*collect_word(char **str, bool *quoted)
{
	char	*acc;

	acc = ft_strdup("");
	if (!acc)
		return (NULL);
	*quoted = false;
	return (collect_word_loop(str, quoted, acc));
}

/**
 * @brief Main entry point for tokenizing a shell word.
 * @param str Address of the scan cursor.
 * @return Newly allocated token object or NULL on failure.
 */
t_token	*handle_word(char **str)
{
	t_token	*token;
	char	*acc;
	bool	quoted;

	acc = collect_word(str, &quoted);
	if (!acc)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (free(acc), NULL);
	if (!quoted && is_assignment_prefix(acc))
		token->type = TOKEN_PREFIX;
	else
		token->type = TOKEN_WORD;
	token->value = acc;
	token->quoted = quoted;
	token->expanded = false;
	return (token);
}
