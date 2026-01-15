/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 04:30:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	**active_res_ptr(t_exp_ctx *ctx)
{
	return (ctx->state.res ? ctx->state.res : ctx->state.curr);
}

void	process_val_split(char *val, t_exp_ctx *ctx)
{
	int		k;
	char	buf[2];

	if (!val || !*val)
		return ;
	k = 0;
	while (val[k])
	{
		if (ft_isspace((unsigned char)val[k]))
		{
			if (ctx->state.curr && *ctx->state.curr)
			{
				add_token_node(ctx->lists.head, ctx->lists.tail,
					*ctx->state.curr, *ctx->state.wd_quoted);
				*ctx->state.curr = NULL;
				*ctx->state.wd_quoted = 0;
			}
		}
		else
		{
			buf[0] = val[k];
			buf[1] = '\0';
			append_chunk(active_res_ptr(ctx), ft_strdup(buf));
			if (ctx->state.wd_quoted)
				*ctx->state.wd_quoted = 0;
		}
		k++;
	}
}
