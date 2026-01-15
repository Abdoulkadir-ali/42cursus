/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 14:20:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	**get_append_target(t_exp_buffers *b)
{
	if (b->expanded)
		return (&b->expanded);
	return (&b->word);
}

static int	handle_dq_backslash(t_exp_params *p, t_exp_buffers *b)
{
	char	next;
	char	*tmp;

	next = p->str[p->pos + 1];
	if (next != '$' && next != '"' && next != '\\' && next != '\n')
	{
		tmp = ft_substr(p->str, p->pos, 1);
		append_chunk(get_append_target(b), tmp);
		p->pos++;
		return (1);
	}
	return (0);
}

static int	consume_backslash(t_exp_params *p, t_exp_quotes *q,
		t_exp_buffers *b)
{
	char	*tmp;

	p->pos++;
	if (!p->str[p->pos])
		return (1);
	tmp = ft_substr(p->str, p->pos, 1);
	if (b->expanded)
		append_chunk(&b->expanded, tmp);
	else
	{
		append_chunk(&b->word, tmp);
		if (!q->d_quote)
			q->was_quoted = 1;
	}
	p->pos++;
	return (1);
}

int	handle_backslash_split(t_exp_params *p, t_exp_quotes *q, t_exp_buffers *b)
{
	if (p->str[p->pos] != '\\' || q->s_quote)
		return (0);
	if (q->d_quote)
	{
		if (handle_dq_backslash(p, b))
			return (1);
	}
	return (consume_backslash(p, q, b));
}
