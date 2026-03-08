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
	t_aabb		other;
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
	p = 0;
	while (p < s->box_count && count < max)
	{
		other = box_aabb(&s->boxes[p]);
		if (aabb_overlap(saabb, other)
			&& collide_sphere_box(sphere, &s->boxes[p], &c[count]))
			count++;
		p++;
	}
	p = 0;
	while (p < s->capsule_count && count < max)
	{
		other = capsule_aabb(&s->capsules[p]);
		if (aabb_overlap(saabb, other)
			&& collide_sphere_capsule(sphere, &s->capsules[p], &c[count]))
			count++;
		p++;
	}
	return (count);
}

static int	query_rect(t_scene *s, int idx, t_contact *c, int count, int max)
{
	t_rect	*rc;
	t_aabb	raabb;
	t_aabb	other;
	int		p;

	rc = &s->rects[idx];
	if (rc->phys.is_static)
		return (count);
	raabb = rect_aabb(rc);
	p = 0;
	while (p < s->plane_count && count < max)
	{
		count += collide_rect_plane(rc, &s->planes[p], &c[count], max - count);
		p++;
	}
	p = 0;
	while (p < s->sphere_count && count < max)
	{
		other = sphere_aabb(&s->spheres[p]);
		if (aabb_overlap(raabb, other))
			count += collide_rect_sphere(rc, &s->spheres[p], &c[count],
					max - count);
		p++;
	}
	p = 0;
	while (p < s->capsule_count && count < max)
	{
		other = capsule_aabb(&s->capsules[p]);
		if (aabb_overlap(raabb, other))
			count += collide_rect_capsule(rc, &s->capsules[p], &c[count],
					max - count);
		p++;
	}
	return (count);
}

static int	query_pyramid(t_scene *s, int idx, t_contact *c, int count, int max)
{
	t_pyramid	*py;
	t_aabb		pyaabb;
	t_aabb		other;
	int			p;

	py = &s->pyramids[idx];
	if (py->phys.is_static)
		return (count);
	pyaabb = pyramid_aabb(py);
	p = 0;
	while (p < s->plane_count && count < max)
	{
		count += collide_pyramid_plane(py, &s->planes[p], &c[count],
				max - count);
		p++;
	}
	p = 0;
	while (p < s->sphere_count && count < max)
	{
		other = sphere_aabb(&s->spheres[p]);
		if (aabb_overlap(pyaabb, other))
			count += collide_pyramid_sphere(py, &s->spheres[p], &c[count],
					max - count);
		p++;
	}
	p = 0;
	while (p < s->capsule_count && count < max)
	{
		other = capsule_aabb(&s->capsules[p]);
		if (aabb_overlap(pyaabb, other))
			count += collide_pyramid_capsule(py, &s->capsules[p], &c[count],
					max - count);
		p++;
	}
	return (count);
}

static int	query_box(t_scene *s, int idx, t_contact *c, int count, int max)
{
	t_box	*bx;
	t_aabb	baabb;
	t_aabb	other;
	int		p;

	bx = &s->boxes[idx];
	if (bx->phys.is_static)
		return (count);
	baabb = box_aabb(bx);
	p = 0;
	while (p < s->plane_count && count < max)
	{
		count += collide_box_plane(bx, &s->planes[p], &c[count], max - count);
		p++;
	}
	p = idx + 1;
	while (p < s->box_count && count < max)
	{
		other = box_aabb(&s->boxes[p]);
		if (aabb_overlap(baabb, other)
			&& collide_box_box(bx, &s->boxes[p], &c[count]))
			count++;
		p++;
	}
	p = 0;
	while (p < s->capsule_count && count < max)
	{
		other = capsule_aabb(&s->capsules[p]);
		if (aabb_overlap(baabb, other)
			&& collide_box_capsule(bx, &s->capsules[p], &c[count]))
			count++;
		p++;
	}
	return (count);
}

static int	query_capsule(t_scene *s, int idx, t_contact *c, int count, int max)
{
	t_capsule	*cap;
	t_aabb		caabb;
	t_aabb		other;
	int			p;

	cap = &s->capsules[idx];
	if (cap->phys.is_static)
		return (count);
	caabb = capsule_aabb(cap);
	p = 0;
	while (p < s->plane_count && count < max)
	{
		count += collide_capsule_plane(cap, &s->planes[p], &c[count], max - count);
		p++;
	}
	p = idx + 1;
	while (p < s->capsule_count && count < max)
	{
		other = capsule_aabb(&s->capsules[p]);
		if (aabb_overlap(caabb, other)
			&& collide_capsule_capsule(cap, &s->capsules[p], &c[count]))
			count++;
		p++;
	}
	p = 0;
	while (p < s->box_count && count < max)
	{
		other = box_aabb(&s->boxes[p]);
		if (aabb_overlap(caabb, other)
			&& collide_box_capsule(&s->boxes[p], cap, &c[count]))
			count++;
		p++;
	}
	return (count);
}

static int	query_tri(t_scene *s, int idx, t_contact *c, int count, int max)
{
	t_tri_shape	*tr;
	t_aabb		taabb;
	t_aabb		other;
	int			p;

	tr = &s->tris[idx];
	if (tr->phys.is_static)
		return (count);
	taabb = tri_shape_aabb(tr);
	p = 0;
	while (p < s->plane_count && count < max)
	{
		count += collide_tri_plane(tr, &s->planes[p], &c[count], max - count);
		p++;
	}
	p = 0;
	while (p < s->sphere_count && count < max)
	{
		other = sphere_aabb(&s->spheres[p]);
		if (aabb_overlap(taabb, other))
			count += collide_tri_sphere(tr, &s->spheres[p], &c[count],
					max - count);
		p++;
	}
	p = 0;
	while (p < s->capsule_count && count < max)
	{
		other = capsule_aabb(&s->capsules[p]);
		if (aabb_overlap(taabb, other))
			count += collide_tri_capsule(tr, &s->capsules[p], &c[count],
					max - count);
		p++;
	}
	return (count);
}

static int	query_cylinder(t_scene *s, int idx, t_contact *c, int count,
		int max)
{
	t_cylinder	*cy;
	t_aabb		cyaabb;
	t_aabb		other;
	int			p;

	cy = &s->cylinders[idx];
	if (cy->phys.is_static)
		return (count);
	cyaabb = cylinder_aabb(cy);
	p = 0;
	while (p < s->plane_count && count < max)
	{
		count += collide_cylinder_plane(cy, &s->planes[p], &c[count],
				max - count);
		p++;
	}
	p = 0;
	while (p < s->sphere_count && count < max)
	{
		other = sphere_aabb(&s->spheres[p]);
		if (aabb_overlap(cyaabb, other)
			&& collide_cylinder_sphere(cy, &s->spheres[p], &c[count]))
			count++;
		p++;
	}
	p = 0;
	while (p < s->capsule_count && count < max)
	{
		other = capsule_aabb(&s->capsules[p]);
		if (aabb_overlap(cyaabb, other)
			&& collide_cylinder_capsule(cy, &s->capsules[p], &c[count]))
			count++;
		p++;
	}
	p = 0;
	while (p < s->box_count && count < max)
	{
		other = box_aabb(&s->boxes[p]);
		if (aabb_overlap(cyaabb, other)
			&& collide_cylinder_box(cy, &s->boxes[p], &c[count]))
			count++;
		p++;
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
	i = 0;
	while (i < scene->rect_count)
		count = query_rect(scene, i++, contacts, count, max_c);
	i = 0;
	while (i < scene->pyramid_count)
		count = query_pyramid(scene, i++, contacts, count, max_c);
	i = 0;
	while (i < scene->box_count)
		count = query_box(scene, i++, contacts, count, max_c);
	i = 0;
	while (i < scene->capsule_count)
		count = query_capsule(scene, i++, contacts, count, max_c);
	i = 0;
	while (i < scene->tri_count)
		count = query_tri(scene, i++, contacts, count, max_c);
	i = 0;
	while (i < scene->cylinder_count)
		count = query_cylinder(scene, i++, contacts, count, max_c);
	return (count);
}
