/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 02:24:07 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

/* 1. EXTERNAL DEPENDENCIES */
# include "bvh.h"
# include "libft.h"
# include "maths.h"
# include "types.h"
# include <float.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>

# define EPSILON 0.001

/* 2. MODULE TYPES */



struct		s_hit
{
	double	t;
	t_bvh_ref ref; /* Uses forward declared type from types.h */
	t_vec3	point;
	t_vec3	normal;
	t_vec3	tangent;
	t_vec3	bitangent;
	double	u;
	double	v;
};

typedef struct s_shading_ctx
{
	t_hit			*hit;
	t_scene			*scene;
	const t_bvh		*bvh;
	const t_ray		*ray;
	t_material		mat;
	t_vec3			albedo;
}	t_shading_ctx;

typedef struct s_build_item
{
	t_bvh_ref	ref;
	t_aabb		bbox;
	t_vec3		centroid;
}	t_build_item;

/* 3. FUNCTION PROTOTYPES */

/* srcs/raytracing/trace/ */
void		ray_init(t_ray *ray, t_vec3 origin, t_vec3 direction);
void		ray_normalize_direction(t_ray *ray);
t_vec3		trace_ray(const t_bvh *bvh, const t_ray *ray, t_scene *scene);
t_vec3		compute_color(t_hit *hit, t_scene *scene, const t_bvh *bvh,
				const t_ray *ray, int depth);

/* srcs/raytracing/intersection/ */
bool		intersect_sphere(const t_ray *ray, t_sphere *sp, t_hit *hit);
bool		intersect_plane(const t_ray *ray, t_plane *pl, t_hit *hit);
bool		intersect_cylinder(const t_ray *ray, t_cylinder *cy, t_hit *hit);
bool		intersect_cone(const t_ray *ray, t_cone *co, t_hit *hit);
bool		intersect_mesh(const t_ray *ray, t_mesh *mesh, t_hit *hit);

/* srcs/raytracing/bvh/ */
bool		bvh_intersect(const t_bvh *bvh, const t_ray *ray, t_hit *hit);
bool		bvh_occluded(const t_bvh *bvh, const t_ray *ray, double max_t);
t_aabb		aabb_from_ref(t_scene *scene, t_bvh_ref ref);
t_aabb		aabb_transform(t_aabb local, t_transform t);
t_aabb		aabb_create_empty(void);
t_aabb		aabb_union(const t_aabb *a, const t_aabb *b);

/* 4. IMPLEMENTATION IMPORTS */
# include "scene.h"

#endif
