/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:01:48 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 04:43:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	process_expanded_list(t_expand_tokens_args *ctx)
{
	ctx->exp_curr = ctx->expanded_list;
	ctx->exp_next = NULL;
	ctx->exp_tok = NULL;
	ctx->matches = NULL;
	while (ctx->exp_curr)
	{
		ctx->exp_next = ctx->exp_curr->next;
		ctx->exp_tok = (t_token *)ctx->exp_curr->content;
		ctx->exp_tok->type = TOKEN_WORD;
		if (!ctx->exp_tok->quoted && ft_strchr(ctx->exp_tok->value, '*'))
		{
			ctx->matches = expand_wildcard(ctx->exp_tok->value);
			if (ctx->matches)
				process_matches_or_literal(ctx);
			else
				append_node(&ctx->new_head, &ctx->new_tail, ctx->exp_curr);
		}
		else
			append_node(&ctx->new_head, &ctx->new_tail, ctx->exp_curr);
		ctx->exp_curr = ctx->exp_next;
	}
}

static void	handle_word_node(t_expand_tokens_args *ctx, char **envp,
		int exit_code)
{
	if (is_prev_heredoc(ctx->prev))
	{
		append_node(&ctx->new_head, &ctx->new_tail, ctx->curr);
		ctx->prev = ctx->new_tail;
		ctx->curr = ctx->next_node;
		return ;
	}
	apply_tilde_expansion(ctx->tok, envp);
	ctx->expanded_list = expand_and_split(ctx->tok->value, envp, exit_code);
	process_expanded_list(ctx);
	del_token(ctx->curr->content);
	free(ctx->curr);
}

void	expand_tokens(t_nodes **tokens, char **envp, int exit_code)
{
	t_expand_tokens_args	ctx;

	ft_bzero(&ctx, sizeof(ctx));
	ctx.new_head = NULL;
	ctx.new_tail = NULL;
	ctx.curr = *tokens;
	ctx.next_node = NULL;
	ctx.tok = NULL;
	ctx.prev = NULL;
	ctx.expanded_list = NULL;
	dump_tokens_list(*tokens, "before_expand_tokens");
	while (ctx.curr)
	{
		ctx.next_node = ctx.curr->next;
		ctx.tok = (t_token *)ctx.curr->content;
		if (ctx.tok->type == TOKEN_WORD)
			handle_word_node(&ctx, envp, exit_code);
		else
		{
			append_node(&ctx.new_head, &ctx.new_tail, ctx.curr);
			ctx.prev = ctx.new_tail;
		}
		ctx.curr = ctx.next_node;
		if (ctx.prev == NULL && ctx.new_tail)
			ctx.prev = ctx.new_tail;
	}
	*tokens = ctx.new_head;
}
