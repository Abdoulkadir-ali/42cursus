/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_opt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

void	ascii_load_normals(t_fbx_ascii_ctx *ctx)
{
	char	*temp;

	ctx->rn = NULL;
	temp = find_node(ctx->p, ctx->end, "Normals:");
	if (!temp)
		return ;
	temp = advance_to_data(temp, ctx->end);
	ctx->rn = parse_array(&temp, &ctx->nc, sizeof(t_vec3), f_vec3);
}

void	ascii_load_uvs(t_fbx_ascii_ctx *ctx)
{
	char	*temp;

	ctx->ru = NULL;
	temp = find_node(ctx->p, ctx->end, "UV:");
	if (!temp)
		return ;
	temp = advance_to_data(temp, ctx->end);
	ctx->ru = parse_array(&temp, &ctx->uc, sizeof(t_vec2), f_vec2);
}
