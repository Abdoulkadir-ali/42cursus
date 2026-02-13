/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Dispatches ray intersection to the correct object type.
*/
static bool	intersect_object(const t_ray *ray, t_scene *scene, t_bvh_ref ref,
		t_hit *hit)
{
	bool	res;

	res = false;
	if (ref.type == TYPE_SPHERE)
		res = intersect_sphere(ray, &scene->spheres[ref.index], hit);
	else if (ref.type == TYPE_PLANE)
		res = intersect_plane(ray, &scene->planes[ref.index], hit);
	else if (ref.type == TYPE_MESH)
		res = intersect_mesh(ray, &scene->meshes[ref.index], hit);
	else if (ref.type == TYPE_ANIM)
		res = intersect_mesh(ray, &scene->animated[ref.index].base, hit);
	else if (ref.type == TYPE_CYLINDER)
		res = intersect_cylinder(ray, &scene->cylinders[ref.index], hit);
	else if (ref.type == TYPE_CONE)
		res = intersect_cone(ray, &scene->cones[ref.index], hit);
	if (res)
		hit->ref = ref;
	return (res);
}

/*
** Iterative traversal for finding the closest intersection.
** Sorts children to visit closer nodes first (Early Z-Culling).
*/
bool	bvh_intersect(const t_bvh *bvh, const t_ray *ray, t_hit *hit)
{
	t_bvh_node	*stack[128];
	int			ptr;
	t_bvh_node	*node;
	double		t_min;
	double		t_max;
	double		t_l;
	double		t_r;
	double		tm_l;
	double		tm_r;
	bool		h_l;
	bool		h_r;
	size_t		i;
	t_hit		temp_hit;

	if (!bvh || !bvh->root)
		return (false);
	hit->t = MAX_VALUE;
	hit->ref.type = TYPE_NONE;
	ptr = 0;
	stack[ptr++] = bvh->root;
	while (ptr > 0)
	{
		node = stack[--ptr];
		if (!aabb_intersect_fast(&node->bbox, ray, &t_min, &t_max)
			|| t_min > hit->t)
			continue ;
		if (node->left || node->right)
		{
			h_l = node->left && aabb_intersect_fast(&node->left->bbox, ray,
					&t_l, &tm_l);
			h_r = node->right && aabb_intersect_fast(&node->right->bbox, ray,
					&t_r, &tm_r);
			if (h_l && h_r)
			{
				if (ptr >= 126)
					continue ;
				/* Push the FURTHER one first, so we pop the CLOSER one first */
				if (t_l > t_r)
				{
					stack[ptr++] = node->left;
					stack[ptr++] = node->right;
				}
				else
				{
					stack[ptr++] = node->right;
					stack[ptr++] = node->left;
				}
			}
			else if (h_l)
			{
				if (ptr >= 127)
					continue ;
				stack[ptr++] = node->left;
			}
			else if (h_r)
			{
				if (ptr >= 127)
					continue ;
				stack[ptr++] = node->right;
			}
		}
		else
		{
			i = 0;
			while (i < node->num_refs)
			{
				temp_hit.t = MAX_VALUE;
				temp_hit.ref.type = TYPE_NONE;
				if (intersect_object(ray, bvh->scene, node->refs[i], &temp_hit)
					&& temp_hit.t < hit->t)
					*hit = temp_hit;
				i++;
			}
		}
	}
	//if (hit->ref.type != TYPE_NONE)
		//printf("DEBUG: BVH HIT: t=%f, type=%d\n",hit->t, hit->ref.type);
	return (hit->ref.type != TYPE_NONE);
}

/*
** Iterative traversal for shadow rays (any hit).
*/
bool	bvh_occluded(const t_bvh *bvh, const t_ray *ray, double max_t)
{
	t_bvh_node	*stack[128];
	int			ptr;
	t_bvh_node	*node;
	double		t_min;
	double		t_max;
	size_t		i;
	t_hit		temp;

	if (!bvh || !bvh->root)
		return (false);
	ptr = 0;
	stack[ptr++] = bvh->root;
	while (ptr > 0)
	{
		node = stack[--ptr];
		if (!aabb_intersect_fast(&node->bbox, ray, &t_min, &t_max)
			|| t_min > max_t)
			continue ;
		if (node->left || node->right)
		{
			if (ptr >= 126)
				continue ; /* Stack safety */
			if (node->right)
				stack[ptr++] = node->right;
			if (node->left)
				stack[ptr++] = node->left;
		}
		else
		{
			i = 0;
			while (i < node->num_refs)
			{
				if (node->refs[i].type == TYPE_MESH)
				{
					if (mesh_occluded(ray,
							&bvh->scene->meshes[node->refs[i].index], max_t))
						return (true);
				}
				else if (node->refs[i].type == TYPE_ANIM)
				{
					if (mesh_occluded(ray,
							&bvh->scene->animated[node->refs[i].index].base,
							max_t))
						return (true);
				}
				else if (intersect_object(ray, bvh->scene, node->refs[i], &temp)
					&& temp.t > EPSILON && temp.t < max_t)
					return (true);
				i++;
			}
		}
	}
	return (false);
}
