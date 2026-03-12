/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:18:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Flush the current split word into the output token list.
 * @param exp Expansion context holding state, input, and output buffers.
 * @return This function does not return a value.
 */
static void	flush_token(t_expansion *exp)
{
	if (exp->word && *exp->word)
	{
		add_token_node(&exp->head, &exp->tail, exp->word, false);
		exp->word = NULL;
	}
}

/**
 * @brief Split an expanded value on unquoted whitespace into output tokens.
 * @param val Newly allocated expansion value.
 * @param exp Expansion context holding state, input, and output buffers.
 * @return This function does not return a value.
 */
void	process_val_split(char *val, t_expansion *exp)
{
	size_t	k;

	if (!val || !*val)
		return ;
	k = 0;
	while (val[k])
	{
		if (ft_isspace((unsigned char)val[k]))
			flush_token(exp);
		else
			exp_push_char(exp, val[k]);
		k++;
	}
}
