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
 * @param out Expansion output buffers and token-list accumulator.
 * @return This function does not return a value.
 */
static void	flush_token(t_exp_output *out)
{
	if (out->word && *out->word)
	{
		add_token_node(&out->head, &out->tail, out->word, 0);
		out->word = NULL;
	}
}

/**
 * @brief Split an expanded value on unquoted whitespace into output tokens.
 * @param val Newly allocated expansion value.
 * @param out Expansion output buffers and token-list accumulator.
 * @return This function does not return a value.
 */
void	process_val_split(char *val, t_exp_output *out)
{
	int	k;

	if (!val || !*val)
		return ;
	k = 0;
	while (val[k])
	{
		if (ft_isspace((unsigned char)val[k]))
			flush_token(out);
		else
			exp_push_char(out, val[k]);
		k++;
	}
}
