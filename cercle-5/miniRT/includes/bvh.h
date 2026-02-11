/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

/* 1. EXTERNAL DEPENDENCIES */
# include "maths.h"
# include "types.h"
# include <float.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>

/* 2. CONSTANTS */
# define MAX_LEAF_OBJECTS 4

/* 3. MODULE TYPES */
struct					s_bvh_ref
{
	uint8_t				type;
	int					index;
};

struct					s_bvh_node
{
	t_aabb				bbox;
	struct s_bvh_node	*left;
	struct s_bvh_node	*right;
	t_bvh_ref			*refs;
	size_t				num_refs;
};

struct					s_bvh
{
	t_scene				*scene;
	t_bvh_node			*root;
};

/* srcs/raytracing/bvh/ */
t_bvh					*bvh_create(t_scene *scene);
void					bvh_destroy(t_bvh *bvh);
t_aabb					aabb_from_ref(t_scene *s, t_bvh_ref ref);
t_aabb					aabb_union(const t_aabb *a, const t_aabb *b);
t_aabb					aabb_create_empty(void);

/* 5. IMPLEMENTATION IMPORTS */
# include "scene.h"

static inline double	aabb_surface_area(t_aabb bbox)
{
	t_vec3	d;

	d = vec3_sub(bbox.max, bbox.min);
	return (2.0 * (d.x * d.y + d.y * d.z + d.z * d.x));
}

/*
** Optimized AABB intersection using precomputed inverse ray direction.
*/
static inline bool	aabb_intersect_fast(const t_aabb *aabb, const t_ray *ray,
		double *tmin, double *tmax)
{
	double	t0;
	double	t1;
	double	min;
	double	max;

	t0 = (aabb->min.x - ray->origin.x) * ray->inv_dir.x;
	t1 = (aabb->max.x - ray->origin.x) * ray->inv_dir.x;
	if (ray->sign[0])
	{
		double tmp = t0; t0 = t1; t1 = tmp;
	}
	min = t0;
	max = t1;
	if (min > max) return (false);
	t0 = (aabb->min.y - ray->origin.y) * ray->inv_dir.y;
	t1 = (aabb->max.y - ray->origin.y) * ray->inv_dir.y;
	if (ray->sign[1])
	{
		double tmp = t0; t0 = t1; t1 = tmp;
	}
	min = fmax(min, t0);
	max = fmin(max, t1);
	if (min > max) return (false);
	t0 = (aabb->min.z - ray->origin.z) * ray->inv_dir.z;
	t1 = (aabb->max.z - ray->origin.z) * ray->inv_dir.z;
	if (ray->sign[2])
	{
		double tmp = t0; t0 = t1; t1 = tmp;
	}
	min = fmax(min, t0);
	max = fmin(max, t1);
	if (max < 0 || min > max)
		return (false);
	*tmin = min;
	*tmax = max;
	return (true);
}

/* bvh_destroy */
void	bvh_destroy(t_bvh *bvh);
t_aabb	aabb_union(const t_aabb *a, const t_aabb *b);
void	aabb_expand_point(t_aabb *bbox, t_vec3 p);

#endif
