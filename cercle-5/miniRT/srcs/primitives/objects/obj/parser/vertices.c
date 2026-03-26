/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_vertices.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

void	obj_parse_v(t_obj_ctx *ctx, t_parser *p)
{
	t_vec3	v;

	v.w = 1.0;
	v.x = parse_double(p);
	parser_skip_spaces(p);
	v.y = parse_double(p);
	parser_skip_spaces(p);
	v.z = parse_double(p);
	if (!dynarray_ensure((void **)&ctx->temp_v, ctx->v_count, &ctx->v_cap,
			sizeof(t_vec3)))
		return ;
	ctx->temp_v[ctx->v_count++] = v;
	aabb_expand_point(&ctx->bbox, v);
}

void	obj_parse_vt(t_obj_ctx *ctx, t_parser *p)
{
	t_vec2	vt;

	vt.x = parse_double(p);
	parser_skip_spaces(p);
	vt.y = parse_double(p);
	if (!dynarray_ensure((void **)&ctx->temp_vt, ctx->vt_count, &ctx->vt_cap,
			sizeof(t_vec2)))
		return ;
	ctx->temp_vt[ctx->vt_count++] = vt;
}

void	obj_parse_vn(t_obj_ctx *ctx, t_parser *p)
{
	t_vec3	vn;

	vn.w = 0.0;
	vn.x = parse_double(p);
	parser_skip_spaces(p);
	vn.y = parse_double(p);
	parser_skip_spaces(p);
	vn.z = parse_double(p);
	if (!dynarray_ensure((void **)&ctx->temp_vn, ctx->vn_count, &ctx->vn_cap,
			sizeof(t_vec3)))
		return ;
	ctx->temp_vn[ctx->vn_count++] = vn;
}
