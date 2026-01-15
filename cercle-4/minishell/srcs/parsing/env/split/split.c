/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 04:37:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	init_exp_ctx(t_exp_ctx *ctx, char *str, char **envp, int exit_code)
{
	ft_bzero(ctx, sizeof(t_exp_ctx));
	ctx->input.str = str;
	ctx->input.envp = envp;
	ctx->input.exit_code = exit_code;
}

t_nodes	*finalize_expansion(t_exp_ctx *ctx)
{
	if (*ctx->state.curr)
		add_token_node(ctx->lists.head, ctx->lists.tail, *ctx->state.curr,
			*ctx->state.wd_quoted);
	else if (*ctx->state.wd_quoted)
		add_token_node(ctx->lists.head, ctx->lists.tail, ft_strdup(""), 1);
	return (*ctx->lists.head);
}

static void	run_expansion_loop(t_exp_ctx *ctx)
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

t_nodes	*expand_and_split(char *str, char **envp, int exit_code)
{
	t_exp_ctx	ctx;
	t_locals	locals;

	if (!str)
		return (NULL);
	locals.head = NULL;
	locals.tail = NULL;
	locals.curr = NULL;
	locals.i = 0;
	locals.qt[0] = 0;
	locals.qt[1] = 0;
	locals.wd_quoted = 0;
	init_exp_ctx(&ctx, str, envp, exit_code);
	ctx.state.i = &locals.i;
	ctx.state.qt = locals.qt;
	ctx.state.wd_quoted = &locals.wd_quoted;
	ctx.state.curr = &locals.curr;
	ctx.lists.head = &locals.head;
	ctx.lists.tail = &locals.tail;
	run_expansion_loop(&ctx);
	return (finalize_expansion(&ctx));
}
