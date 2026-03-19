/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:36:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 06:01:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @param c Character inspected after `$`.
 * @return True for valid target characters, otherwise false.
 */
bool	is_exp_target(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

/**
 * @brief Append one allocated string chunk to the active output buffer.
 * @param exp Expansion context holding state and buffers.
 * @param s Newly allocated chunk string.
 * @return This function does not return a value.
 */
void	exp_push_str(t_expansion *exp, char *s)
{
	if (!s)
		return ;
	if (exp->res_str)
		append_chunk(&exp->res_str, s);
	else
		append_chunk(&exp->word, s);
}

/**
 * @brief Append one character to the active expansion output buffer.
 * @param exp Expansion context holding state and buffers.
 * @param c Character to append.
 * @return This function does not return a value.
 */
void	exp_push_char(t_expansion *exp, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	exp_push_str(exp, ft_strdup(tmp));
}

/**
 * @brief Perform one resolved dollar expansion in the current output mode.
 * @param exp Expansion context holding state, input, and output buffers.
 * @return This function does not return a value.
 */
void	perform_expansion(t_expansion *exp)
{
	char	*val;

	val = handle_dollar((char *)exp->str, &exp->pos, exp->env, exp->status);
	if (exp->res_str)
		exp_push_str(exp, val);
	else if (exp->in_d_quote)
	{
		exp_push_str(exp, val);
		exp->has_quotes = true;
	}
	else
	{
		process_val_split(val, exp);
		free(val);
	}
}
