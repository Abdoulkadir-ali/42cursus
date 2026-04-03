/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:19:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static int	dispatch_mat(t_shading *sha, t_hit *h)
{
	if (h->ref.type == TYPE_SPHERE)
		return (sha->scene->spheres[h->ref.index].mat_id);
	if (h->ref.type == TYPE_PLANE)
		return (sha->scene->planes[h->ref.index].mat_id);
	if (h->ref.type == TYPE_CYLINDER)
		return (sha->scene->cylinders[h->ref.index].mat_id);
	if (h->ref.type == TYPE_CONE)
		return (sha->scene->cones[h->ref.index].mat_id);
	if (h->ref.type == TYPE_TRI)
		return (sha->scene->tris[h->ref.index].mat_id);
	if (h->ref.type == TYPE_RECT)
		return (sha->scene->rects[h->ref.index].mat_id);
	if (h->ref.type == TYPE_PYRAMID)
		return (sha->scene->pyramids[h->ref.index].mat_id);
	if (h->ref.type == TYPE_BOX)
		return (sha->scene->boxes[h->ref.index].mat_id);
	if (h->ref.type == TYPE_CAPSULE)
		return (sha->scene->capsules[h->ref.index].mat_id);
	if (h->ref.type == TYPE_MESH)
		return (sha->scene->meshes[h->ref.index].mat_id);
	if (h->ref.type == TYPE_ANIM)
		return (sha->scene->animated[h->ref.index].base.mat_id);
	return (0);
}

void	get_material(t_shading *sha)
{
	size_t	mat_id;

	mat_id = (size_t)dispatch_mat(sha, sha->hit);
	if (mat_id >= sha->scene->mat_count)
		mat_id = 0;
	sha->mat = sha->scene->materials[mat_id];
}

void	apply_bump(t_shading *sha)
{
	t_vec3	s;
	t_vec3	m;
	t_vec3	n;

	if (sha->mat.bump_map.type == TEX_SOLID || !sha->mat.bump_map.addr)
		return ;
	s = sample_texture(&sha->mat.bump_map, sha->hit->u, sha->hit->v);
	m.x = (s.x / 255.0) * 2.0 - 1.0;
	m.y = (s.y / 255.0) * 2.0 - 1.0;
	m.z = (s.z / 255.0) * 2.0 - 1.0;
	n.x = sha->hit->tangent.x * m.x + sha->hit->bitangent.x * m.y
		+ sha->hit->normal.x * m.z;
	n.y = sha->hit->tangent.y * m.x + sha->hit->bitangent.y * m.y
		+ sha->hit->normal.y * m.z;
	n.z = sha->hit->tangent.z * m.x + sha->hit->bitangent.z * m.y
		+ sha->hit->normal.z * m.z;
	sha->hit->normal = vec3_norm(n);
}
