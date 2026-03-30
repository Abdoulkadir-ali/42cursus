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
void	get_material(t_shading *sha)
{
	t_hit	*h;
	int		mat_id;

	h = sha->hit;
	mat_id = 0;
	if (h->ref.type == TYPE_SPHERE && h->ref.index >= 0
		&& h->ref.index < sha->scene->sphere_count)
		mat_id = sha->scene->spheres[h->ref.index].mat_id;
	else if (h->ref.type == TYPE_PLANE && h->ref.index >= 0
		&& h->ref.index < sha->scene->plane_count)
		mat_id = sha->scene->planes[h->ref.index].mat_id;
	else if (h->ref.type == TYPE_CYLINDER && h->ref.index >= 0
		&& h->ref.index < sha->scene->cylinder_count)
		mat_id = sha->scene->cylinders[h->ref.index].mat_id;
	else if (h->ref.type == TYPE_CONE && h->ref.index >= 0
		&& h->ref.index < sha->scene->cone_count)
		mat_id = sha->scene->cones[h->ref.index].mat_id;
	else if (h->ref.type == TYPE_TRI && h->ref.index >= 0
		&& h->ref.index < sha->scene->tri_count)
		mat_id = sha->scene->tris[h->ref.index].mat_id;
	else if (h->ref.type == TYPE_RECT && h->ref.index >= 0
		&& h->ref.index < sha->scene->rect_count)
		mat_id = sha->scene->rects[h->ref.index].mat_id;
	else if (h->ref.type == TYPE_PYRAMID && h->ref.index >= 0
		&& h->ref.index < sha->scene->pyramid_count)
		mat_id = sha->scene->pyramids[h->ref.index].mat_id;
	else if (h->ref.type == TYPE_BOX && h->ref.index >= 0
		&& h->ref.index < sha->scene->box_count)
		mat_id = sha->scene->boxes[h->ref.index].mat_id;
	else if (h->ref.type == TYPE_CAPSULE && h->ref.index >= 0
		&& h->ref.index < sha->scene->capsule_count)
		mat_id = sha->scene->capsules[h->ref.index].mat_id;
	else if (h->ref.type == TYPE_MESH && h->ref.index >= 0
		&& h->ref.index < sha->scene->mesh_count)
		mat_id = sha->scene->meshes[h->ref.index].mat_id;
	else if (h->ref.type == TYPE_ANIM && h->ref.index >= 0
		&& h->ref.index < sha->scene->anim_count)
		mat_id = sha->scene->animated[h->ref.index].base.mat_id;
	if (mat_id < 0 || mat_id >= sha->scene->mat_count)
		mat_id = 0;
	sha->mat = sha->scene->materials[mat_id];
}

/*
** Applies normal/bump mapping if available.
*/
void	apply_bump(t_shading *sha)
{
	t_vec3	s;
	t_vec3	m_n;
	t_vec3	n_n;

	if (sha->mat.bump_map.type == TEX_SOLID || !sha->mat.bump_map.addr)
		return ;
	s = sample_texture(&sha->mat.bump_map, sha->hit->u, sha->hit->v);
	m_n.x = (s.x / 255.0) * 2.0 - 1.0;
	m_n.y = (s.y / 255.0) * 2.0 - 1.0;
	m_n.z = (s.z / 255.0) * 2.0 - 1.0;
	m_n.w = 0.0;
	n_n.x = sha->hit->tangent.x * m_n.x + sha->hit->bitangent.x * m_n.y
		+ sha->hit->normal.x * m_n.z;
	n_n.y = sha->hit->tangent.y * m_n.x + sha->hit->bitangent.y * m_n.y
		+ sha->hit->normal.y * m_n.z;
	n_n.z = sha->hit->tangent.z * m_n.x + sha->hit->bitangent.z * m_n.y
		+ sha->hit->normal.z * m_n.z;
	n_n.w = 0.0;
	sha->hit->normal = vec3_norm(n_n);
}
