/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contacts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:31:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "objects.h"
#include "scene.h"
#include "raytracing.h"

static bool	aabb_overlap(t_aabb a, t_aabb b)
{
	if (a.max.x < b.min.x || a.min.x > b.max.x)
		return (false);
	if (a.max.y < b.min.y || a.min.y > b.max.y)
		return (false);
	if (a.max.z < b.min.z || a.min.z > b.max.z)
		return (false);
	return (true);
}

static int	check_leaf_ref(t_scene *s, t_sphere *sphere, int idx,
		t_bvh_ref ref, t_contact *c)
{
	if (ref.type == TYPE_SPHERE && ref.index > idx)
		return (collide_sphere_sphere(sphere,
				&s->spheres[ref.index], c));
	if (ref.type == TYPE_MESH)
		return (collide_sphere_mesh(sphere,
				&s->meshes[ref.index], c));
	return (0);
}

static int	check_leaf(t_scene *s, t_sphere *sp, int idx,
		const t_bvh *bvh, int node_idx, t_contact *c, int count, int max)
{
	const t_bvh_node	*node;
	int					i;
	int					end;

	node = &bvh->nodes[node_idx];
	i = node->left_or_first;
	end = i + node->count;
	while (i < end && count < max)
	{
		if (check_leaf_ref(s, sp, idx, bvh->refs[i], &c[count]))
			count++;
		i++;
	}
	return (count);
}

static int	traverse_bvh_contacts(t_scene *s, int idx, t_sphere *sp,
		t_aabb saabb, t_contact *c, int count, int max)
{
	int					stack[128];
	int					ptr;
	int					i;
	const t_bvh_node	*node;

	ptr = 0;
	if (!s->bvh || s->bvh->num_nodes == 0)
		return (count);
	stack[ptr++] = 0;
	while (ptr > 0 && count < max)
	{
		i = stack[--ptr];
		node = &s->bvh->nodes[i];
		if (!aabb_overlap(node->bbox, saabb))
			continue ;
		if (node->count > 0)
			count = check_leaf(s, sp, idx, s->bvh, i, c, count, max);
		else if (ptr < 126)
		{
			stack[ptr++] = node->left_or_first;
			stack[ptr++] = i + 1;
		}
	}
	return (count);
}

static int	query_sphere(t_scene *s, int idx, t_contact *c, int count,
		int max)
{
	t_sphere	*sphere;
	t_aabb		saabb;
	int			p;

	sphere = &s->spheres[idx];
	if (sphere->phys.is_static)
		return (count);
	saabb = sphere_aabb(sphere);
	count = traverse_bvh_contacts(s, idx, sphere, saabb, c, count, max);
	p = 0;
	while (p < s->plane_count && count < max)
	{
		if (collide_sphere_plane(sphere, &s->planes[p++], &c[count]))
			count++;
	}
	return (count);
}

int	generate_contacts(t_scene *scene, t_contact *contacts, int max_c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < scene->sphere_count)
		count = query_sphere(scene, i++, contacts, count, max_c);
	return (count);
}
