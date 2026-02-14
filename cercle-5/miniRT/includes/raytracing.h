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
# include "objects.h"
# include "surface.h"

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
	t_vec3				p;
	t_vec3				center;
	double				radius;
	double				height;
	double				h;
}						t_entry_point;

struct					s_hit
{
	double				t;
	t_bvh_ref ref; /* Uses forward declared type from types.h */
	t_vec3				point;
	t_vec3				normal;
	t_vec3				tangent;
	t_vec3				bitangent;
	double				u;
	double				v;
};

typedef struct s_shading_ctx
{
	t_hit				*hit;
	t_scene				*scene;
	const t_bvh			*bvh;
	const t_ray			*ray;
	t_material			mat;
	t_vec3				albedo;
}						t_shading_ctx;

typedef struct s_build_item
{
	t_bvh_ref			ref;
	t_aabb				bbox;
	t_vec3				centroid;
}						t_build_item;

typedef struct s_split_info
{
	int					axis;
	size_t				split;
	double				cost;
}						t_split_info;

typedef struct s_check_params
{
	const t_ray			*ray;
	t_cylinder			*cy;
	double				t;
	double				*tm;
	t_hit				*hit;
}						t_check_params;

typedef struct s_cap_params
{
	const t_ray			*ray;
	t_cylinder			*cy;
	double				*tm;
	t_hit				*hit;
	t_vec3				center;
	double				normal_sign;
}						t_cap_params;

/* 3. FUNCTION PROTOTYPES */

/* bvh_destroy */
void					bvh_destroy(t_bvh *bvh);
t_aabb					aabb_union(const t_aabb *a, const t_aabb *b);
void					aabb_expand_point(t_aabb *bbox, t_vec3 p);

void					node_destroy(t_bvh_node *node);
t_split_info			find_best_split(t_build_item *items, size_t count,
							double p_area);
t_bvh_node				*init_leaf_node(t_build_item *items, size_t count);
t_bvh_node				*build_recursive(t_build_item *items, size_t count);

t_bvh					*bvh_create(t_scene *scene);
void					bvh_destroy(t_bvh *bvh);
t_aabb					aabb_from_ref(t_scene *s, t_bvh_ref ref);
t_aabb					aabb_union(const t_aabb *a, const t_aabb *b);
t_aabb					aabb_create_empty(void);

/* srcs/raytracing/bvh/ */
double					aabb_surface_area(t_aabb bbox);
bool					aabb_intersect_fast(const t_aabb *aabb,
							const t_ray *ray, double *tmin, double *tmax);
void					aabb_expand_point(t_aabb *bbox, t_vec3 p);

/* srcs/raytracing/trace/ */
void					ray_init(t_ray *ray, t_vec3 origin, t_vec3 direction);
void					ray_normalize_direction(t_ray *ray);
t_vec3					trace_ray(const t_bvh *bvh, const t_ray *ray,
							t_scene *scene);
t_vec3					compute_color(t_hit *hit, t_scene *scene,
							const t_bvh *bvh, const t_ray *ray);
bool					is_in_shadow(const t_bvh *bvh, t_vec3 p, t_vec3 ldir);
t_vec3					pixel_color(t_vec3 obj, t_vec3 light, double intensity);
void					get_material(t_shading_ctx *ctx);
void					apply_bump(t_shading_ctx *ctx);
t_vec3					calc_light(t_shading_ctx *ctx, t_light light);

/* srcs/raytracing/intersection/ */
bool					intersect_sphere(const t_ray *ray, t_sphere *sp,
							t_hit *hit);
bool					intersect_plane(const t_ray *ray, t_plane *pl,
							t_hit *hit);
bool					intersect_cylinder(const t_ray *ray, t_cylinder *cy,
							t_hit *hit);
bool					intersect_cone(const t_ray *ray, t_cone *co,
							t_hit *hit);
bool					intersect_mesh(const t_ray *ray, t_mesh *mesh,
							t_hit *hit);
bool					intersect_triangle(const t_ray *ray, t_vec3 v[3],
							double *t, t_vec2 *uv);
void					mesh_build_bvh(t_mesh *mesh);
bool					mesh_occluded(const t_ray *ray, t_mesh *mesh,
							double dist);

/* Intersection helpers */
void					get_sphere_uv(t_vec3 normal, double *u, double *v);
void					set_sphere_hit_data(const t_ray *ray, t_sphere *sp,
							t_hit *hit);
void					get_plane_uv(t_vec3 p, t_vec3 n, t_hit *hit);
void					get_cone_uv(t_hit *hit, t_cone *cone, t_vec3 radial,
							double h);
void					fill_hit_record(t_hit *hit, const t_ray *ray,
							t_cone *cone, double t);
bool					check_cone_body(const t_ray *ray, t_cone *cone,
							double *t, double y_cutoff);
void					get_cylinder_uv(t_entry_point pt, t_cylinder *cy,
							t_hit *hit, bool cap);
bool					check_bottom_cap(const t_ray *ray, t_cylinder *cy,
							double *tm, t_hit *hit);
bool					check_top_cap(const t_ray *ray, t_cylinder *cy,
							double *tm, t_hit *hit);
bool					check_body(const t_ray *ray, t_cylinder *cy, double *tm,
							t_hit *hit);

/* srcs/raytracing/bvh/ */
bool					bvh_intersect(const t_bvh *bvh, const t_ray *ray,
							t_hit *hit);
bool					bvh_occluded(const t_bvh *bvh, const t_ray *ray,
							double max_t);
bool					intersect_object(const t_ray *ray, t_scene *scene,
							t_bvh_ref ref, t_hit *hit);
t_aabb					aabb_from_ref(t_scene *scene, t_bvh_ref ref);
t_aabb					aabb_transform(t_aabb local, t_transform t);
t_aabb					aabb_create_empty(void);
t_aabb					aabb_union(const t_aabb *a, const t_aabb *b);
int						compare_x(const void *a, const void *b);
int						compare_y(const void *a, const void *b);
int						compare_z(const void *a, const void *b);
size_t					collect_objects(t_scene *scene, t_build_item *items);

void					process_leaf(const t_bvh_node *node, const t_ray *ray,
							const t_bvh *bvh, t_hit *hit);
void					process_internal_node(t_bvh_node *node,
							t_bvh_node *stack[128], int *ptr, const t_ray *ray);

typedef struct s_child_intersections
{
	t_vec2				left_t;
	t_vec2				right_t;
	bool				h_l;
	bool				h_r;
}						t_child_intersections;

typedef struct s_push_data
{
	t_bvh_node			*left;
	t_bvh_node			*right;
	t_vec2				left_t;
	t_vec2				right_t;
}						t_push_data;

/* srcs/raytracing/bvh/traverse/ */
t_child_intersections	get_child_intersections(const t_bvh_node *node,
							const t_ray *ray);
void					push_both_children(t_bvh_node *stack[128], int *ptr,
							t_push_data *data);
void					push_single_child(t_bvh_node *stack[128], int *ptr,
							t_bvh_node *child);
void					push_children(t_bvh_node *stack[128], int *ptr,
							t_push_data *data, bool h_l, bool h_r);
void					process_internal_node(t_bvh_node *node,
							t_bvh_node *stack[128], int *ptr, const t_ray *ray);

/* 4. IMPLEMENTATION IMPORTS */
# include "scene.h"

#endif
