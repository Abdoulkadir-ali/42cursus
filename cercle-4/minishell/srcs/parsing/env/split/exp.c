/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:36:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:18:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Check whether a character can appear in a dollar expansion target.
 * @param c Character inspected after `$`.
 * @return 1 for valid target characters, otherwise 0.
 */
int	is_exp_target(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

/**
 * @brief Append one character to the active expansion output buffer.
 * @param out Expansion output buffers.
 * @param c Character to append.
 * @return This function does not return a value.
 */
void	exp_push_char(t_exp_output *out, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	if (out->str)
		append_chunk(&out->str, ft_strdup(tmp));
	else
		append_chunk(&out->word, ft_strdup(tmp));
}

/**
 * @brief Append one allocated string chunk to the active output buffer.
 * @param out Expansion output buffers.
 * @param s Newly allocated chunk string.
 * @return This function does not return a value.
 */
void	exp_push_str(t_exp_output *out, char *s)
{
	if (!s)
		return ;
	if (out->str)
		append_chunk(&out->str, s);
	else
		append_chunk(&out->word, s);
}

/**
 * @brief Perform one resolved dollar expansion in the current output mode.
 * @param in Expansion input cursor.
 * @param st Expansion quote state.
 * @param out Expansion output buffers.
 * @return This function does not return a value.
 */
void	perform_expansion(t_exp_input *in, t_exp_state *st, t_exp_output *out)
{
	char	*val;

	val = handle_dollar((char *)in->str, &in->pos, in->env, in->status);
	if (out->str)
		exp_push_str(out, val);
	else if (st->in_d_quote)
	{
		exp_push_str(out, val);
		st->has_quotes = 1;
	}
	else
	{
		process_val_split(val, out);
		free(val);
	}
}

/**
 * @brief Keep a dollar sign literal when no valid expansion target follows.
 * @param in Expansion input cursor.
 * @param out Expansion output buffers.
 * @param idx Position of the literal dollar sign.
 * @return This function does not return a value.
 */
void	push_literal_dollar(t_exp_input *in, t_exp_output *out, int idx)
{
	exp_push_char(out, in->str[idx]);
	in->pos++;
}
