/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 04:22:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	run_expansion_loop(t_exp_ctx *ctx)
{
	while (ctx->input.str[*ctx->state.i])
	{
		if (handle_quote_split(ctx))
			continue ;
		if (handle_backslash_split(ctx))
			continue ;
		if (handle_dollar_split(ctx))
			continue ;
		append_chunk(ctx->state.curr, ft_substr(ctx->input.str, *ctx->state.i,
				1));
		if (!ctx->state.qt[0] && !ctx->state.qt[1])
			*ctx->state.wd_quoted = 0;
		(*ctx->state.i)++;
	}
}
