/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_trace_hit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	set_hit_point(t_hit_calc *c)
{
	c->in->hit->point = vec3_add(c->in->ray->origin,
			vec3_scale(c->in->ray->direction, c->in->t));
}

static void	set_hit_normal(t_hit_calc *c)
{
	t_vec3	n[3];
	t_vec3	sh_n;

	if (c->in->mesh->normals)
	{
		n[0] = c->in->mesh->normals[c->idx[0]];
		n[1] = c->in->mesh->normals[c->idx[1]];
		n[2] = c->in->mesh->normals[c->idx[2]];
		sh_n = vec3_add(vec3_scale(n[0], 1.0 - c->in->bary.x - c->in->bary.y),
				vec3_add(vec3_scale(n[1], c->in->bary.x), vec3_scale(n[2],
						c->in->bary.y)));
		c->in->hit->normal = vec3_norm(sh_n);
	}
	else
		c->in->hit->normal = vec3_norm(vec3_cross(vec3_sub(c->v[1], c->v[0]),
					vec3_sub(c->v[2], c->v[0])));
	if (vec3_dot(c->in->ray->direction, c->in->hit->normal) > 0)
		c->in->hit->normal = vec3_scale(c->in->hit->normal, -1.0);
}

static t_vec3	get_face_normal(t_hit_calc *c)
{
	return (vec3_norm(vec3_cross(vec3_sub(c->v[1], c->v[0]),
				vec3_sub(c->v[2], c->v[0]))));
}

static void	set_hit_uv(t_hit_calc *c)
{
	t_vec2	uvs[3];
	t_vec3	raw_n;

	uvs[0] = c->in->mesh->uvs[c->idx[0]];
	uvs[1] = c->in->mesh->uvs[c->idx[1]];
	uvs[2] = c->in->mesh->uvs[c->idx[2]];
	c->in->hit->u = uvs[0].x * (1.0 - c->in->bary.x - c->in->bary.y) + uvs[1].x
		* c->in->bary.x + uvs[2].x * c->in->bary.y;
	c->in->hit->v = uvs[0].y * (1.0 - c->in->bary.x - c->in->bary.y) + uvs[1].y
		* c->in->bary.x + uvs[2].y * c->in->bary.y;
	if (c->in->mesh->normals)
		raw_n = c->in->mesh->normals[c->idx[0]];
	else
		raw_n = get_face_normal(c);
	if (vec3_dot(c->in->ray->direction, raw_n) > 0)
		c->in->hit->u = 1.0 - c->in->hit->u;
}

static void	set_hit_tangent(t_hit_calc *c)
{
	vec3_orthonormal_basis(c->in->hit->normal,
		&c->in->hit->tangent, &c->in->hit->bitangent);
}

void	update_mesh_hit(t_mesh_hit_ctx *ctx)
{
	t_hit_calc	calc;

	calc.in = ctx;
	calc.idx = &ctx->mesh->bvh_indices[ctx->tri * 3];
	calc.v[0] = ctx->mesh->vertices[calc.idx[0]];
	calc.v[1] = ctx->mesh->vertices[calc.idx[1]];
	calc.v[2] = ctx->mesh->vertices[calc.idx[2]];
	ctx->hit->t = ctx->t;
	set_hit_point(&calc);
	set_hit_normal(&calc);
	set_hit_tangent(&calc);
	if (ctx->mesh->uvs)
		set_hit_uv(&calc);
}
