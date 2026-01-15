/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:36:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 14:36:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_exp_target(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

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

void	exp_push_str(t_exp_output *out, char *s)
{
	if (!s)
		return ;
	if (out->str)
		append_chunk(&out->str, s);
	else
		append_chunk(&out->word, s);
}

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

void	push_literal_dollar(t_exp_input *in, t_exp_output *out, int idx)
{
	exp_push_char(out, in->str[idx]);
	in->pos++;
}
