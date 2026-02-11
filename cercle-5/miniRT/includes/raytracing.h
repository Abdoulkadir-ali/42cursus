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
# include "core.h"
# include "debug.h"
# include "maths.h"
# include "surface.h"
# include "objects.h"

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

typedef struct s_entry_point
{
	t_vec3	p;
	t_vec3	center;
	double	radius;
	double	height;
	double	h;
}	t_entry_point;

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

/* bvh_destroy */
void	bvh_destroy(t_bvh *bvh);
t_aabb	aabb_union(const t_aabb *a, const t_aabb *b);
void	aabb_expand_point(t_aabb *bbox, t_vec3 p);

t_bvh					*bvh_create(t_scene *scene);
void					bvh_destroy(t_bvh *bvh);
t_aabb					aabb_from_ref(t_scene *s, t_bvh_ref ref);
t_aabb					aabb_union(const t_aabb *a, const t_aabb *b);
t_aabb					aabb_create_empty(void);

/* srcs/raytracing/bvh/ */
double					aabb_surface_area(t_aabb bbox);
bool					aabb_intersect_fast(const t_aabb *aabb, const t_ray *ray,
							double *tmin, double *tmax);
void					aabb_expand_point(t_aabb *bbox, t_vec3 p);

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
bool		intersect_triangle(const t_ray *ray, t_vec3 v[3], double *t, t_vec2 *uv);
void		mesh_build_bvh(t_mesh *mesh);
bool		mesh_occluded(const t_ray *ray, t_mesh *mesh, double dist);

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
