/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 04:40:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	**active_res_ptr(t_exp_ctx *ctx)
{
	if (ctx->state.res)
		return (ctx->state.res);
	return (ctx->state.curr);
}

static int	bs_try_double_quote_case(t_exp_ctx *ctx, int idx)
{
	char	next;
	char	*tmp;

	next = ctx->input.str[idx + 1];
	if (next != '$' && next != '"' && next != '\\' && next != '\n')
	{
		tmp = ft_substr(ctx->input.str, idx, 1);
		append_chunk(active_res_ptr(ctx), tmp);
		(*ctx->state.i)++;
		return (1);
	}
	return (0);
}

static int	bs_consume_escaped_char(t_exp_ctx *ctx)
{
	char	*tmp;

	(*ctx->state.i)++;
	if (!ctx->input.str[*ctx->state.i])
		return (1);
	tmp = ft_substr(ctx->input.str, *ctx->state.i, 1);
	if (ctx->state.res)
		append_chunk(ctx->state.res, tmp);
	else
	{
		append_chunk(ctx->state.curr, tmp);
		if (ctx->state.wd_quoted)
			*ctx->state.wd_quoted = 1;
	}
	(*ctx->state.i)++;
	return (1);
}

int		handle_backslash_split(t_exp_ctx *ctx)
{
	int	idx;

	idx = *ctx->state.i;
	if (ctx->input.str[idx] != '\\')
		return (0);
	if (ctx->state.qt[0])
		return (0);
	if (ctx->state.qt[1])
	{
		if (bs_try_double_quote_case(ctx, idx))
			return (1);
	}
	return (bs_consume_escaped_char(ctx));
}

