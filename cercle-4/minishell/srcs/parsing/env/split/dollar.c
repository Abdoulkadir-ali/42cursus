/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 04:42:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*substr_one_at(const char *s, int idx)
{
	return (ft_substr(s, idx, 1));
}

static int	dollar_handle_res_case(t_exp_ctx *ctx, int idx, char next)
{
	char	*val;

	if (next == '\'' || next == '$' || (!is_var_char(next) && next != '"'
		&& next != '?'))
	{
		append_chunk(ctx->state.res, substr_one_at(ctx->input.str, idx));
		(*ctx->state.i)++;
		return (1);
	}
	if (!ctx->state.qt[0] && (ft_isalnum((unsigned char)next) || next == '_'
			|| next == '?'))
	{
		val = handle_dollar((char *)ctx->input.str, ctx->state.i,
				ctx->input.envp, ctx->input.exit_code);
		append_chunk(ctx->state.res, val);
		return (1);
	}
	return (0);
}

static int	dollar_handle_no_res_case(t_exp_ctx *ctx, int idx, char next)
{
	char	*val;

	if ((next == '\'' || next == '"') && !ctx->state.qt[0] && !ctx->state.qt[1])
	{
		(*ctx->state.i)++;
		return (1);
	}
	if ((!is_var_char(next) && next != '?') || ctx->state.qt[0] || (next == '"'
			&& ctx->state.qt[1]))
	{
		append_chunk(ctx->state.curr, substr_one_at(ctx->input.str, idx));
		(*ctx->state.i)++;
		return (1);
	}
	val = handle_dollar((char *)ctx->input.str, ctx->state.i, ctx->input.envp,
			ctx->input.exit_code);
	if (ctx->state.qt[1])
	{
		append_chunk(ctx->state.curr, val);
		*ctx->state.wd_quoted = 1;
	}
	else
	{
		process_val_split(val, ctx);
		free(val);
	}
	return (1);
}

int	handle_dollar_split(t_exp_ctx *ctx)
{
	int		idx;
	char	next;

	idx = *ctx->state.i;
	if (ctx->input.str[idx] != '$')
		return (0);
	next = ctx->input.str[idx + 1];
	if (ctx->state.res)
	{
		return (dollar_handle_res_case(ctx, idx, next));
	}
	return (dollar_handle_no_res_case(ctx, idx, next));
}
