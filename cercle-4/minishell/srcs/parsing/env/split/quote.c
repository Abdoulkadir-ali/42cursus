/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 04:45:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	mark_as_quoted(t_exp_quotes *q, t_exp_buffers *b)
{
	q->was_quoted = 1;
	if (b->expanded == NULL && b->word == NULL)
		b->word = ft_strdup("");
}

static int	toggle_single_quote(t_exp_params *p, t_exp_quotes *q, t_exp_buffers *b)
{
	if (q->d_quote)
		return (0);
	q->s_quote = !q->s_quote;
	mark_as_quoted(q, b);
	p->pos++;
	return (1);
}

static int	toggle_double_quote(t_exp_params *p, t_exp_quotes *q, t_exp_buffers *b)
{
	if (q->s_quote)
		return (0);
	q->d_quote = !q->d_quote;
	mark_as_quoted(q, b);
	p->pos++;
	return (1);
}

int	handle_quote_split(t_exp_params *p, t_exp_quotes *q, t_exp_buffers *b)
{
	const char	c = p->str[p->pos];

	if (c == '\'')
		return (toggle_single_quote(p, q, b));
	if (c == '\"')
		return (toggle_double_quote(p, q, b));
	return (0);
}
