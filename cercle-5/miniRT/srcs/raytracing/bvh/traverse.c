/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:30:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Dispatches ray intersection to the correct object type.
*/
static bool	intersect_object(const t_ray *ray, t_scene *scene,
		t_bvh_ref ref, t_hit *hit)
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
** Computes intersection between a ray and an Axis-Aligned Bounding Box.
*/
static bool	aabb_ray_intersect(const t_aabb *aabb, const t_ray *ray,
		double *tmin, double *tmax)
{
	double	t[2];
	double	tm[2];

	tm[0] = -1e30;
	tm[1] = 1e30;
	/* X */
	t[0] = (aabb->min.x - ray->origin.x) / ray->direction.x;
	t[1] = (aabb->max.x - ray->origin.x) / ray->direction.x;
	tm[0] = fmax(tm[0], fmin(t[0], t[1]));
	tm[1] = fmin(tm[1], fmax(t[0], t[1]));
	/* Y */
	t[0] = (aabb->min.y - ray->origin.y) / ray->direction.y;
	t[1] = (aabb->max.y - ray->origin.y) / ray->direction.y;
	tm[0] = fmax(tm[0], fmin(t[0], t[1]));
	tm[1] = fmin(tm[1], fmax(t[0], t[1]));
	/* Z */
	t[0] = (aabb->min.z - ray->origin.z) / ray->direction.z;
	t[1] = (aabb->max.z - ray->origin.z) / ray->direction.z;
	tm[0] = fmax(tm[0], fmin(t[0], t[1]));
	tm[1] = fmin(tm[1], fmax(t[0], t[1]));
	*tmin = tm[0];
	*tmax = tm[1];
	return (tm[1] >= tm[0] && tm[1] > EPSILON);
}

/*
** Checks intersections within a leaf node of the BVH.
*/
static void	traverse_leaf(const t_bvh *bvh, const t_bvh_node *node,
		const t_ray *ray, t_hit *hit)
{
	t_hit	temp_hit;
	size_t	i;

	i = 0;
	while (i < node->num_refs)
	{
		if (intersect_object(ray, bvh->scene, node->refs[i], &temp_hit)
			&& temp_hit.t < hit->t)
			*hit = temp_hit;
		i++;
	}
}

/*
** Recursive traversal function for BVH intersection.
*/
static void	bvh_traverse(const t_bvh *bvh, const t_bvh_node *node,
		const t_ray *ray, t_hit *hit)
{
	double	t[2];

	if (!node)
		return ;
	if (!aabb_ray_intersect(&node->bbox, ray, &t[0], &t[1])
		|| t[1] < 0 || t[0] > hit->t)
		return ;
	if (node->left || node->right)
	{
		bvh_traverse(bvh, node->left, ray, hit);
		bvh_traverse(bvh, node->right, ray, hit);
	}
	else
		traverse_leaf(bvh, node, ray, hit);
}

/*
** Main entry point for BVH-ray intersection test.
*/
bool	bvh_intersect(const t_bvh *bvh, const t_ray *ray, t_hit *hit)
{
	if (!bvh || !bvh->root)
		return (false);
	hit->t = 1e30;
	hit->ref.type = TYPE_NONE;
	bvh_traverse(bvh, bvh->root, ray, hit);
	return (hit->ref.type != TYPE_NONE);
}

/*
** Checks if a ray is occluded between origin and max_t (shadow test).
*/
bool	bvh_occluded(const t_bvh *bvh, const t_ray *ray, double max_t)
{
	double		t[2];
	t_hit		temp;
	size_t		i;
	t_bvh_node	*node;

	node = bvh->root;
	if (!bvh || !node)
		return (false);
	if (!aabb_ray_intersect(&node->bbox, ray, &t[0], &t[1])
		|| t[1] < 0 || t[0] > max_t)
		return (false);
	if (node->left || node->right)
	{
		if (bvh_occluded(&(t_bvh){bvh->scene, node->left}, ray, max_t))
			return (true);
		return (bvh_occluded(&(t_bvh){bvh->scene, node->right}, ray, max_t));
	}
	i = 0;
	while (i < node->num_refs)
	{
		if (intersect_object(ray, bvh->scene, node->refs[i], &temp)
			&& temp.t > EPSILON && temp.t < max_t)
			return (true);
		i++;
	}
	return (false);
}

