/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 04:22:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_nodes	*finalize_expansion(t_exp_ctx *ctx)
{
	if (*ctx->state.curr)
		add_token_node(ctx->lists.head, ctx->lists.tail, *ctx->state.curr,
			*ctx->state.wd_quoted);
	else if (*ctx->state.wd_quoted)
		add_token_node(ctx->lists.head, ctx->lists.tail, ft_strdup(""), 1);
	return (*ctx->lists.head);
}
