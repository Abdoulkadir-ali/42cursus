/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   occluded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Fast sphere occlusion: solve the quadratic, skip all UV/tangent work.
*/
static bool	occlude_sphere(const t_ray *ray, t_sphere *sp, double max_t)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	disc;
	double	t;

	oc = vec3_sub(ray->origin, sp->transform.pos);
	a = vec3_dot(ray->direction, ray->direction);
	b = 2.0 * vec3_dot(oc, ray->direction);
	disc = b * b - 4.0 * a * (vec3_dot(oc, oc) - sp->radius_sq);
	if (disc < 0.0)
		return (false);
	disc = sqrt(disc);
	t = (-b - disc) / (2.0 * a);
	if (t < EPSILON)
		t = (-b + disc) / (2.0 * a);
	return (t > EPSILON && t < max_t);
}

/*
** Fast cylinder/cone occlusion: reuse intersect_object but skip the UV cost
** by reading only hit.t.  For simplicity we call the full function and rely
** on the compiler to eliminate dead stores of UV/tangent fields.
** Sphere is specially treated above (two transcendental calls avoided).
*/
static bool	occlude_object(const t_ray *ray, t_scene *scene,
		t_bvh_ref ref, double max_t)
{
	t_hit	temp;

	if (ref.type == TYPE_SPHERE)
		return (occlude_sphere(ray, &scene->spheres[ref.index], max_t));
	temp.t = max_t;
	if (intersect_object(ray, scene, ref, &temp))
		return (temp.t > EPSILON && temp.t < max_t);
	return (false);
}

static bool	process_leaf_occluded(const t_bvh *bvh, int node_idx,
			const t_ray *ray, double max_t)
{
	const t_bvh_node	*node;
	int					i;
	int					end;

	node = &bvh->nodes[node_idx];
	i = node->left_or_first;
	end = i + node->count;
	while (i < end)
	{
		if (bvh->refs[i].type == TYPE_MESH)
		{
			if (mesh_occluded(ray, &bvh->scene->meshes[bvh->refs[i].index],
					max_t))
				return (true);
		}
		else if (bvh->refs[i].type == TYPE_ANIM)
		{
			if (mesh_occluded(ray,
					&bvh->scene->animated[bvh->refs[i].index].base, max_t))
				return (true);
		}
		else if (occlude_object(ray, bvh->scene, bvh->refs[i], max_t))
			return (true);
		i++;
	}
	return (false);
}

static void	push_occ_children(int *stack, int *ptr, const t_bvh *bvh,
		const t_ray *ray, int node_idx, double max_t)
{
	int		left;
	int		right;
	double	tl;
	double	tl_max;
	double	tr;
	double	tr_max;

	tl = 0.0;
	tr = 0.0;
	left = bvh->nodes[node_idx].left_or_first;
	right = node_idx + 1;
	if (!aabb_intersect_fast(&bvh->nodes[left].bbox, ray, &tl, &tl_max))
		left = -1;
	if (!aabb_intersect_fast(&bvh->nodes[right].bbox, ray, &tr, &tr_max))
		right = -1;
	if (left >= 0 && tl < 0.0)
		tl = 0.0;
	if (right >= 0 && tr < 0.0)
		tr = 0.0;
	if (left >= 0 && tl >= max_t)
		left = -1;
	if (right >= 0 && tr >= max_t)
		right = -1;
	if (left >= 0 && right >= 0)
	{
		if (tl <= tr)
		{
			stack[(*ptr)++] = right;
			stack[(*ptr)++] = left;
		}
		else
		{
			stack[(*ptr)++] = left;
			stack[(*ptr)++] = right;
		}
	}
	else if (left >= 0)
		stack[(*ptr)++] = left;
	else if (right >= 0)
		stack[(*ptr)++] = right;
}

/*
** Occluded traversal: test each AABB exactly once.
** Root is tested before the loop; all other nodes are tested eagerly by
** push_occ_children before being pushed, so no re-test on pop.
*/
static bool	traverse_bvh_occluded(const t_bvh *bvh, const t_ray *ray,
		double max_t)
{
	int					stack[128];
	int					ptr;
	int					i;
	const t_bvh_node	*node;
	double				tmin;
	double				tmax;

	/* Test root once. */
	tmin = 0.0;
	tmax = MAX_VALUE;
	if (!aabb_intersect_fast(&bvh->nodes[0].bbox, ray, &tmin, &tmax))
		return (false);
	if (tmin < 0.0)
		tmin = 0.0;
	if (tmin > max_t)
		return (false);
	ptr = 0;
	stack[ptr++] = 0;
	while (ptr > 0)
	{
		i = stack[--ptr];
		node = &bvh->nodes[i];
		if (node->count > 0)
		{
			if (process_leaf_occluded(bvh, i, ray, max_t))
				return (true);
		}
		else if (ptr < 126)
			push_occ_children(stack, &ptr, bvh, ray, i, max_t);
	}
	return (false);
}

bool	bvh_occluded(const t_bvh *bvh, const t_ray *ray, double max_t)
{
	if (!bvh || bvh->num_nodes == 0)
		return (false);
	return (traverse_bvh_occluded(bvh, ray, max_t));
}
