/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 14:20:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	expand_to_string(t_exp_params *p, t_exp_quotes *q, t_exp_buffers *b,
		int idx, char next)
{
	char	*val;
	int		is_name_char;

	is_name_char = ft_isalnum((unsigned char)next) || next == '_'
		|| next == '?';
	if (next == '\'' || next == '$' || (!is_var_char(next) && next != '"' && next != '?'))
	{
		append_chunk(&b->expanded, ft_substr(p->str, idx, 1));
		p->pos++;
		return (1);
	}
	if (!q->s_quote && is_name_char)
	{
		val = handle_dollar((char *)p->str, &p->pos, p->env, p->status);
		append_chunk(&b->expanded, val);
		return (1);
	}
	return (0);
}

static int	expand_to_tokens(t_exp_params *p, t_exp_quotes *q, t_exp_buffers *b,
		int idx, char next)
{
	char	*val;
	int		is_bad;

	if ((next == '\'' || next == '"') && !q->s_quote && !q->d_quote)
	{
		p->pos++;
		return (1);
	}
	is_bad = (!is_var_char(next) && next != '?') || q->s_quote || (next == '"'
			&& q->d_quote);
	if (is_bad)
	{
		append_chunk(&b->word, ft_substr(p->str, idx, 1));
		p->pos++;
		return (1);
	}
	val = handle_dollar((char *)p->str, &p->pos, p->env, p->status);
	if (q->d_quote)
	{
		append_chunk(&b->word, val);
		q->was_quoted = 1;
	}
	else
	{
		process_val_split(val, b);
		free(val);
	}
	return (1);
}

int	handle_dollar_split(t_exp_params *p, t_exp_quotes *q, t_exp_buffers *b)
{
	int		idx;
	char	next;

	if (p->str[p->pos] != '$')
		return (0);
	idx = p->pos;
	next = p->str[idx + 1];
	if (b->expanded)
		return (expand_to_string(p, q, b, idx, next));
	return (expand_to_tokens(p, q, b, idx, next));
}
