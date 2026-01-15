/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 04:46:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	**active_res_ptr(t_exp_ctx *ctx)
{
	if (ctx->state.res)
		return (ctx->state.res);
	return (ctx->state.curr);
}

static void	pvs_flush_curr_if_space(t_exp_ctx *ctx)
{
	if (ctx->state.curr && *ctx->state.curr)
	{
		add_token_node(ctx->lists.head, ctx->lists.tail,
			*ctx->state.curr, *ctx->state.wd_quoted);
		*ctx->state.curr = NULL;
		*ctx->state.wd_quoted = 0;
	}
}

static void	pvs_append_char(t_exp_ctx *ctx, char c)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	append_chunk(active_res_ptr(ctx), ft_strdup(buf));
	if (ctx->state.wd_quoted)
		*ctx->state.wd_quoted = 0;
}

void	process_val_split(char *val, t_exp_ctx *ctx)
{
	int	k;

	if (!val || !*val)
		return ;
	k = 0;
	while (val[k])
	{
		if (ft_isspace((unsigned char)val[k]))
			pvs_flush_curr_if_space(ctx);
		else
			pvs_append_char(ctx, val[k]);
		k++;
	}
}
