/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 21:50:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static int	mat_slot(t_scene *sc, t_bvh_ref ref)
{
	if (ref.type == TYPE_SPHERE || ref.type == TYPE_PROXY_SPHERE)
		return (sc->spheres[ref.index].mat_slots[
				sc->spheres[ref.index].active_slot]);
	if (ref.type == TYPE_PLANE)
		return (sc->planes[ref.index].mat_slots[
				sc->planes[ref.index].active_slot]);
	if (ref.type == TYPE_CYLINDER)
		return (sc->cylinders[ref.index].mat_slots[
				sc->cylinders[ref.index].active_slot]);
	if (ref.type == TYPE_CONE)
		return (sc->cones[ref.index].mat_slots[
				sc->cones[ref.index].active_slot]);
	if (ref.type == TYPE_TRI)
		return (sc->tris[ref.index].mat_slots[
				sc->tris[ref.index].active_slot]);
	if (ref.type == TYPE_RECT)
		return (sc->rects[ref.index].mat_slots[
				sc->rects[ref.index].active_slot]);
	return (-1);
}

static int	dispatch_mat(t_shading *sha, t_hit *h)
{
	int	id;

	id = mat_slot(sha->scene, h->ref);
	if (id != -1)
		return (id);
	if (h->ref.type == TYPE_PYRAMID)
		return (sha->scene->pyramids[h->ref.index].mat_slots[
				sha->scene->pyramids[h->ref.index].active_slot]);
	if (h->ref.type == TYPE_BOX)
		return (sha->scene->boxes[h->ref.index].mat_slots[
				sha->scene->boxes[h->ref.index].active_slot]);
	if (h->ref.type == TYPE_CAPSULE)
		return (sha->scene->capsules[h->ref.index].mat_slots[
				sha->scene->capsules[h->ref.index].active_slot]);
	if (h->ref.type == TYPE_MESH)
		return (sha->scene->meshes[h->ref.index].mat_slots[
				sha->scene->meshes[h->ref.index].active_slot]);
	if (h->ref.type == TYPE_ANIM)
		return (sha->scene->animated[h->ref.index].base.mat_slots[
				sha->scene->animated[h->ref.index].base.active_slot]);
	return (0);
}

void	get_material(t_shading *sha)
{
	size_t			mat_id;

	mat_id = dispatch_mat(sha, sha->hit);
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
	vec3_orthonormal_basis(sha->hit->normal,
		&sha->hit->tangent, &sha->hit->bitangent);
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
