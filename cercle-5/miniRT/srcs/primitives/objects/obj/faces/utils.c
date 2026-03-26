/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   faces_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

int	obj_fix_index(int idx, int count)
{
	if (idx == 0)
		return (-1);
	if (idx < 0)
		return (count + idx);
	return (idx - 1);
}

void	obj_set_out_vertex(t_obj_ctx *ctx, int vi, int vti, int vni)
{
	if (vi >= 0 && vi < (int)ctx->v_count)
		ctx->out_v[ctx->out_v_count] = ctx->temp_v[vi];
	else
		ctx->out_v[ctx->out_v_count] = (t_vec3){0, 0, 0, 1.0};
	if (vti >= 0 && vti < (int)ctx->vt_count)
		ctx->out_vt[ctx->out_v_count] = ctx->temp_vt[vti];
	else
		ctx->out_vt[ctx->out_v_count] = (t_vec2){0, 0};
	if (vni >= 0 && vni < (int)ctx->vn_count)
		ctx->out_vn[ctx->out_v_count] = ctx->temp_vn[vni];
	else
		ctx->out_vn[ctx->out_v_count] = (t_vec3){0, 1, 0, 0};
}

void	obj_ensure_out_capacity(t_obj_ctx *ctx)
{
	size_t	cap;

	if (ctx->out_v_count < ctx->out_v_cap)
		return ;
	cap = ctx->out_v_cap;
	if (!dynarray_ensure((void **)&ctx->out_v, ctx->out_v_count, &cap,
			sizeof(t_vec3)))
		return ;
	cap = ctx->out_v_cap;
	if (!dynarray_ensure((void **)&ctx->out_vt, ctx->out_v_count, &cap,
			sizeof(t_vec2)))
		return ;
	cap = ctx->out_v_cap;
	if (!dynarray_ensure((void **)&ctx->out_vn, ctx->out_v_count, &cap,
			sizeof(t_vec3)))
		return ;
	ctx->out_v_cap = cap;
}

void	obj_add_vert(t_obj_ctx *ctx, int vi, int vti, int vni)
{
	obj_ensure_out_capacity(ctx);
	vi = obj_fix_index(vi, (int)ctx->v_count);
	vti = obj_fix_index(vti, (int)ctx->vt_count);
	vni = obj_fix_index(vni, (int)ctx->vn_count);
	obj_set_out_vertex(ctx, vi, vti, vni);
	if (!dynarray_ensure((void **)&ctx->out_i, ctx->out_i_count,
			&ctx->out_i_cap, sizeof(int)))
		return ;
	ctx->out_i[ctx->out_i_count++] = ctx->out_v_count++;
}
