/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Retrieves material for the hit object.
*/
void	get_material(t_shading_ctx *ctx)
{
	t_hit	*h;
	int		mat_id;

	h = ctx->hit;
	mat_id = 0;
	if (h->ref.type == TYPE_SPHERE && h->ref.index >= 0
		&& h->ref.index < ctx->scene->sphere_count)
		mat_id = ctx->scene->spheres[h->ref.index].mat_id;
	else if (h->ref.type == TYPE_PLANE && h->ref.index >= 0
		&& h->ref.index < ctx->scene->plane_count)
		mat_id = ctx->scene->planes[h->ref.index].mat_id;
	else if (h->ref.type == TYPE_CYLINDER && h->ref.index >= 0
		&& h->ref.index < ctx->scene->cylinder_count)
		mat_id = ctx->scene->cylinders[h->ref.index].mat_id;
	else if (h->ref.type == TYPE_CONE && h->ref.index >= 0
		&& h->ref.index < ctx->scene->cone_count)
		mat_id = ctx->scene->cones[h->ref.index].mat_id;
	else if (h->ref.type == TYPE_TRI && h->ref.index >= 0
		&& h->ref.index < ctx->scene->tri_count)
		mat_id = ctx->scene->tris[h->ref.index].mat_id;
	else if (h->ref.type == TYPE_RECT && h->ref.index >= 0
		&& h->ref.index < ctx->scene->rect_count)
		mat_id = ctx->scene->rects[h->ref.index].mat_id;
	else if (h->ref.type == TYPE_PYRAMID && h->ref.index >= 0
		&& h->ref.index < ctx->scene->pyramid_count)
		mat_id = ctx->scene->pyramids[h->ref.index].mat_id;
	else if (h->ref.type == TYPE_BOX && h->ref.index >= 0
		&& h->ref.index < ctx->scene->box_count)
		mat_id = ctx->scene->boxes[h->ref.index].mat_id;
	else if (h->ref.type == TYPE_CAPSULE && h->ref.index >= 0
		&& h->ref.index < ctx->scene->capsule_count)
		mat_id = ctx->scene->capsules[h->ref.index].mat_id;
	else if (h->ref.type == TYPE_MESH && h->ref.index >= 0
		&& h->ref.index < ctx->scene->mesh_count)
		mat_id = ctx->scene->meshes[h->ref.index].mat_id;
	else if (h->ref.type == TYPE_ANIM && h->ref.index >= 0
		&& h->ref.index < ctx->scene->anim_count)
		mat_id = ctx->scene->animated[h->ref.index].base.mat_id;
	if (mat_id < 0 || mat_id >= ctx->scene->mat_count)
		mat_id = 0;
	ctx->mat = ctx->scene->materials[mat_id];
}

/*
** Applies normal/bump mapping if available.
*/
void	apply_bump(t_shading_ctx *ctx)
{
	t_vec3	s;
	t_vec3	m_n;
	t_vec3	n_n;

	if (ctx->mat.bump_map.type == TEX_SOLID || !ctx->mat.bump_map.addr)
		return ;
	s = sample_texture(&ctx->mat.bump_map, ctx->hit->u, ctx->hit->v);
	m_n.x = (s.x / 255.0) * 2.0 - 1.0;
	m_n.y = (s.y / 255.0) * 2.0 - 1.0;
	m_n.z = (s.z / 255.0) * 2.0 - 1.0;
	m_n.w = 0.0;
	n_n.x = ctx->hit->tangent.x * m_n.x + ctx->hit->bitangent.x * m_n.y
		+ ctx->hit->normal.x * m_n.z;
	n_n.y = ctx->hit->tangent.y * m_n.x + ctx->hit->bitangent.y * m_n.y
		+ ctx->hit->normal.y * m_n.z;
	n_n.z = ctx->hit->tangent.z * m_n.x + ctx->hit->bitangent.z * m_n.y
		+ ctx->hit->normal.z * m_n.z;
	n_n.w = 0.0;
	ctx->hit->normal = vec3_norm(n_n);
}
