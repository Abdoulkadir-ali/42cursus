/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:41:27 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:06:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Main entry point for tokenizing any shell operator.
 * @param str Address of the scan cursor.
 * @return Newly allocated token object or NULL on syntax error or failure.
 */
t_token	*handle_separator(char **str)
{
	t_token	*tok;
	int		rc;
	bool	ok;

	tok = ft_calloc(1, sizeof(t_token));
	if (!tok)
		return (NULL);
	if (**str == '|' || **str == '&')
		rc = check_three_repeated(*str, **str);
	else
		rc = 0;
	ok = false;
	if (rc == 0)
	{
		if (handle_basic_ops(str, tok) || handle_redirs(str, tok))
			ok = true;
		else
			ok = try_handle_punctuation(str, tok);
	}
	if (rc != 0 || !ok || !tok->value)
		return (del_token(tok), NULL);
	return (tok);
}
