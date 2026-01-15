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

static void	ensure_curr_and_mark_quoted(t_exp_ctx *ctx)
{
	*ctx->state.wd_quoted = 1;
	if (!*ctx->state.curr)
		*ctx->state.curr = ft_strdup("");
}

static int	process_single_quote(t_exp_ctx *ctx, const char c)
{
	if (c != '\'')
		return (0);
	if (ctx->state.qt[1])
		return (0);
	ctx->state.qt[0] = !ctx->state.qt[0];
	if (ctx->state.res == NULL)
		ensure_curr_and_mark_quoted(ctx);
	(*ctx->state.i)++;
	return (1);
}

static int	process_double_quote(t_exp_ctx *ctx, const char c)
{
	if (c != '"')
		return (0);
	if (ctx->state.qt[0])
		return (0);
	ctx->state.qt[1] = !ctx->state.qt[1];
	if (ctx->state.res == NULL)
		ensure_curr_and_mark_quoted(ctx);
	(*ctx->state.i)++;
	return (1);
}

int	handle_quote_split(t_exp_ctx *ctx)
{
	const char	c = ctx->input.str[*ctx->state.i];

	if (process_single_quote(ctx, c))
		return (1);
	if (process_double_quote(ctx, c))
		return (1);
	return (0);
}
