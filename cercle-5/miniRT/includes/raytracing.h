/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 02:24:07 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/04 02:24:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

# include "bvh.h"
# include "objects/objects.h"
# include "scene.h"
# include <float.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_ray
{
	t_vec3		origin;
	t_vec3		direction;
}				t_ray;

typedef struct s_hit
{
	double		t;
	t_bvh_ref	ref; // Replaces t_object *obj
	t_vec3		point;
	t_vec3		normal;
	t_vec3		tangent;
	t_vec3		bitangent;
	double		u;
	double		v;
}				t_hit;

typedef struct s_scene	t_scene;

// Ray functions
void			ray_init(t_ray *ray, t_vec3 origin, t_vec3 direction);
void			ray_normalize_direction(t_ray *ray);

// Intersection functions
bool			intersect_mesh(const t_ray *ray, t_mesh *mesh, t_hit *hit);
bool			intersect_sphere(const t_ray *ray, t_sphere *sp, t_hit *hit);
bool			intersect_plane(const t_ray *ray, t_plane *pl, t_hit *hit);
bool			intersect_cylinder(const t_ray *ray, t_cylinder *cy, t_hit *hit);
bool			intersect_triangle(const t_ray *ray, t_vec3 v0, t_vec3 v1, t_vec3 v2, double *t);
bool			intersect_object(const t_ray *ray, t_scene *scene, t_bvh_ref ref, t_hit *hit);

// BVH traversal
bool			bvh_intersect(const t_bvh *bvh, const t_ray *ray, t_hit *hit);
bool			bvh_occluded(const t_bvh *bvh, const t_ray *ray, double max_t);

// Ray tracing

t_vec3			trace_ray(const t_bvh *bvh, const t_ray *ray, t_scene *scene);
t_vec3			compute_color(t_hit *hit, t_scene *scene, const t_bvh *bvh,
					const t_ray *ray, int depth);

#endif
