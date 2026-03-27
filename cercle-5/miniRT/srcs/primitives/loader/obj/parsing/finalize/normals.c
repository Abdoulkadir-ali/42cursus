/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize_normals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

static void	add_face_normal(t_obj_ctx *ctx, size_t i)
{
	int		idx[3];
	t_vec3	v[3];
	t_vec3	fn;

	idx[0] = ctx->out_i[i];
	idx[1] = ctx->out_i[i + 1];
	idx[2] = ctx->out_i[i + 2];
	v[0] = ctx->out_v[idx[0]];
	v[1] = ctx->out_v[idx[1]];
	v[2] = ctx->out_v[idx[2]];
	fn = vec3_cross(vec3_sub(v[1], v[0]), vec3_sub(v[2], v[0]));
	ctx->out_vn[idx[0]] = vec3_add(ctx->out_vn[idx[0]], fn);
	ctx->out_vn[idx[1]] = vec3_add(ctx->out_vn[idx[1]], fn);
	ctx->out_vn[idx[2]] = vec3_add(ctx->out_vn[idx[2]], fn);
}

static void	accumulate_normals(t_obj_ctx *ctx)
{
	size_t	i;

	i = 0;
	while (i + 2 < ctx->out_i_count)
	{
		add_face_normal(ctx, i);
		i += 3;
	}
}

static void	normalize_normals(t_obj_ctx *ctx)
{
	size_t	i;

	i = 0;
	while (i < ctx->out_v_count)
	{
		ctx->out_vn[i] = vec3_norm(ctx->out_vn[i]);
		i++;
	}
}

void	obj_generate_normals(t_obj_ctx *ctx)
{
	if (ctx->vn_count != 0)
		return ;
	ctx->out_vn = ft_calloc(ctx->out_v_count, sizeof(t_vec3));
	if (!ctx->out_vn)
		return ;
	accumulate_normals(ctx);
	normalize_normals(ctx);
	ctx->vn_count = ctx->out_v_count;
}
