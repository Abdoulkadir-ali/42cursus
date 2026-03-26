/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:16:58 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 09:54:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <math.h>
# include <pthread.h>

/* 1. EXTERNAL DEPENDENCIES */
# include "defines.h"
# include "debug.h"
# include "maths.h"
# include "objects.h"
# include "surface.h"

/* Forward declarations to avoid include cycles */
struct s_scene;

# define MAX_DEPTH 5
# define COLOR_MAX 255.0
# define COLOR_MIN 0.0
# define SHININESS_SCALE 200.0
# define SHININESS_OFFSET 2.0
# define METALLIC_REDUCT 0.5
# define METALLIC_BOOST 0.9
# define REFRACT_MAX_DEG 180.0
# define REFRACT_IOR_SCALE 2.0
# define MAG_EPSILON 1e-6
# define SHADOW_BIAS 1e-4
# define WEIGHT_MIN 0.02
# define SAFE_RCP_MIN 1e-20
# define TRACE_MAX_DIST 1e30

# define ATTENUATION_K 0.05
# define MAX_EMISSIVE_DIST_SQ 2500.0
# define EMISSIVE_SURF_OFF 0.01
# define EMISSIVE_BR_SCALE 3.0
# define EPSILON_MUL 10.0
# define NDOTL_MIN 0.02
# define NDOTH_MIN 0.01
# define HALF_SCALE 0.5
# define LIGHT_ATT(d_sq) (1.0 / (1.0 + ATTENUATION_K * (d_sq)))

struct s_bvh_ref
{
	uint8_t type;
	int index;
};

struct s_bvh_node
{
	t_aabb bbox;
	int left_or_first;
	int count;
};

struct s_bvh_tmp_node {
	t_aabb bbox;
	struct s_bvh_tmp_node *left;
	struct s_bvh_tmp_node *right;
	t_bvh_ref *refs;
	size_t num_refs;
};

struct s_bvh
{
	t_scene *scene;
	t_bvh_node *nodes;
	t_bvh_ref *refs;
	int num_nodes;
	int num_refs;
};

struct s_entry_point {
	t_vec3 p;
	t_vec3 center;
	double radius;
	double height;
	double h;
};

struct s_hit
{
	double t;
	t_bvh_ref ref;
	t_vec3 point;
	t_vec3 normal;
	t_vec3 tangent;
	t_vec3 bitangent;
	double u;
	double v;
};

struct s_shading {
	t_hit *hit;
	t_scene *scene;
	const t_bvh *bvh;
	const t_ray *ray;
	t_material mat;
	t_vec3 albedo;
	t_vec3 aux_v;
};

struct s_build_item {
	t_bvh_ref ref;
	t_aabb bbox;
	t_vec3 centroid;
};

struct s_split_info {
	int axis;
	size_t split;
	double cost;
};

typedef struct s_check_params
{
	const t_ray *ray;
	t_cylinder *cy;
	double t;
	double *tm;
	t_hit *hit;
} t_check_params;

typedef struct s_cap_params
{
	const t_ray *ray;
	t_cylinder *cy;
	double *tm;
	t_hit *hit;
	t_vec3 center;
	double normal_sign;
} t_cap_params;

typedef struct s_box_ctx
{
	t_vec3 ax[3];
	double p[3];
	double d_ax[3];
	double h[3];
	double t_min;
	double t_max;
	int face;
} t_box_ctx;

typedef struct s_rect_ctx
{
	t_vec3 v[2][3];
	double t[2];
	t_vec2 uv[2];
	bool h[2];
} t_rect_ctx;

typedef struct s_cap_ctx
{
	t_vec3 p0;
	t_vec3 p1;
	double t_cyl;
	double t_s0;
	double t_s1;
	int b_type;
	double best;
} t_cap_ctx;

struct s_bvh_stack {
	int *stack;
	double *stack_tmin;
	size_t ptr;
	const t_bvh *bvh;
	const t_ray *ray;
	double hit_t;
};

struct s_occ {
	int *stack;
	int *ptr;
	const t_bvh *bvh;
	const t_ray *ray;
	double max_t;
};

struct s_push_vars {
	int left;
	int right;
	double tl;
	double tr;
	double tl_max;
	double tr_max;
	bool hit_l;
	bool hit_r;
};

struct s_lcalc {
	t_vec3 ld_norm;
	double dist;
	double ndotl;
};

/* srcs/raytracing/postprocess/shading/ */
void	add_emissive_lighting(t_shading *ctx, t_scene *scene, t_vec3 *total);
void	apply_emissive_hit(t_shading *ctx, t_vec3 *total, t_material *m,
		t_vec3 lrad);
void	emissive_primary(t_shading *ctx, t_scene *sc, t_vec3 *tot,
		t_emissive_ref r);
void	emissive_complex(t_shading *ctx, t_scene *sc, t_vec3 *tot,
		t_emissive_ref r);

/* srcs/raytracing/postprocess/shading/material/ */
int	get_sphere_mat(t_shading *ctx);
int	get_plane_mat(t_shading *ctx);
int	get_cylinder_mat(t_shading *ctx);
int	get_cone_mat(t_shading *ctx);
int	get_tri_mat(t_shading *ctx);
int	get_rect_mat(t_shading *ctx);
int	get_pyramid_mat(t_shading *ctx);
int	get_box_mat(t_shading *ctx);
int	get_capsule_mat(t_shading *ctx);
int	get_mesh_mat(t_shading *ctx);
int	get_anim_mat(t_shading *ctx);

t_vec3	clamp_color(t_vec3 color);
t_bvh	*bvh_create(t_scene *scene);
void	bvh_destroy(t_bvh *bvh);
void	node_destroy(t_bvh_tmp_node *node);
void	build_emissive_cache(t_scene *sc);
t_bvh_tmp_node	*build_tmp_tree(t_scene *scene, size_t total, size_t *k);
void	flatten_tmp(t_bvh_tmp_node *node, t_bvh *bvh, int *nc, int *rc);
bool	alloc_flat(t_bvh *bvh, size_t k);
t_split_info	find_best_split(t_build_item *items, size_t count,
		double p_area);
t_bvh_tmp_node	*init_leaf_node(t_build_item *items, size_t count);
t_bvh_tmp_node	*build_recursive(t_build_item *items, size_t count);
size_t	collect_objects(t_scene *scene, t_build_item *items);
int	compare_x(const void *a, const void *b);
int	compare_y(const void *a, const void *b);
int	compare_z(const void *a, const void *b);

/* srcs/raytracing/bvh/bound/ */
t_aabb	aabb_from_ref(t_scene *s, t_bvh_ref ref);
t_aabb	aabb_union(const t_aabb *a, const t_aabb *b);
t_aabb	aabb_create_empty(void);
t_aabb	aabb_transform(t_aabb local, t_transform t);
void	aabb_expand_point(t_aabb *bbox, t_vec3 p);
void	aabb_expand_eps(t_aabb *bbox, double eps);
double	aabb_surface_area(t_aabb bbox);
bool	aabb_intersect_fast(const t_aabb *aabb, const t_ray *ray, double *tmin,
		double *tmax);
t_aabb	sphere_aabb(t_sphere *sp);
t_aabb	tri_shape_aabb(t_tri_shape *tr);
t_aabb	rect_aabb(t_rect *rc);
t_aabb	pyramid_aabb(t_pyramid *py);
t_aabb	box_aabb(t_box *bx);
t_aabb	capsule_aabb(t_capsule *cap);
t_aabb	plane_aabb(t_plane *pl);
t_aabb	cylinder_aabb(t_cylinder *cy);
t_aabb	cone_aabb(t_cone *co);

/* srcs/raytracing/bvh/traverse/ */
bool	bvh_intersect(const t_bvh *bvh, const t_ray *ray, t_hit *hit);
bool	bvh_occluded(const t_bvh *bvh, const t_ray *ray, double max_t);
bool	intersect_object(const t_ray *ray, t_scene *scene, t_bvh_ref ref,
		t_hit *hit);

/* occlusion helpers split into files */
bool	occlude_object(const t_ray *ray, t_scene *scene, t_bvh_ref ref,
		double max_t);
double	aabb_hit_time_or_neg1(const t_bvh *bvh, int idx, const t_ray *ray,
		double max_t);
bool	bvh_traverse_loop(const t_bvh *bvh, const t_ray *ray, double max_t);

/* internal traverse helpers */
void	process_leaf_flat(const t_bvh *bvh, int node_idx, const t_ray *ray,
		t_hit *hit);
void	push_children(t_bvh_stack *ctx, int node_idx);
bool	run_traverse_loop(const t_bvh *bvh, const t_ray *ray, t_hit *hit);

t_vec3	clamp_color(t_vec3 color);
t_vec3	refract_ray(t_vec3 incident, t_vec3 normal, float n1, float n2);

/* srcs/raytracing/trace/ */

void	ray_init(t_ray *ray, t_vec3 origin, t_vec3 direction);
void	ray_normalize_direction(t_ray *ray);
t_vec3	trace_ray(const t_bvh *bvh, const t_ray *ray, t_scene *scene);
t_vec3	compute_color(t_hit *hit, t_scene *scene, const t_bvh *bvh,
		const t_ray *ray);
bool	is_in_shadow(const t_bvh *bvh, t_vec3 p, t_vec3 ldir_norm,
		double dist);
t_vec3	pixel_color(t_vec3 obj, t_vec3 light, double intensity);
void	get_material(t_shading *ctx);
void	apply_bump(t_shading *ctx);
t_vec3	calc_light(t_shading *ctx, t_light light);

/* srcs/raytracing/intersection/ */
bool	intersect_sphere(const t_ray *ray, t_sphere *sp, t_hit *hit);
bool	intersect_plane(const t_ray *ray, t_plane *pl, t_hit *hit);
bool	intersect_cylinder(const t_ray *ray, t_cylinder *cy, t_hit *hit);
bool	intersect_cone(const t_ray *ray, t_cone *co, t_hit *hit);
bool	intersect_tri_shape(const t_ray *ray, t_tri_shape *tr, t_hit *hit);
bool	intersect_rect(const t_ray *ray, t_rect *rc, t_hit *hit);
bool	intersect_pyramid(const t_ray *ray, t_pyramid *py, t_hit *hit);
void	pyramid_cache_verts(t_pyramid *py);
bool	intersect_box(const t_ray *ray, t_box *bx, t_hit *hit);
bool	intersect_capsule(const t_ray *ray, t_capsule *cap, t_hit *hit);
bool	intersect_mesh(const t_ray *ray, t_mesh *mesh, t_hit *hit);
bool	intersect_triangle(const t_ray *ray, t_vec3 v[3], double *t,
		t_vec2 *uv);
void	mesh_build_bvh(t_mesh *mesh);
bool	mesh_occluded(const t_ray *ray, t_mesh *mesh, double dist);

/* Intersection helpers */
void	get_sphere_uv(t_vec3 normal, double *u, double *v);
void	set_sphere_hit_data(const t_ray *ray, t_sphere *sp, t_hit *hit);
void	get_plane_uv(t_vec3 p, t_vec3 n, t_hit *hit);
void	get_cone_uv(t_hit *hit, t_cone *cone, t_vec3 radial, double h);
void	fill_hit_record(t_hit *hit, const t_ray *ray, t_cone *cone, double t);
bool	check_cone_body(const t_ray *ray, t_cone *cone, double *t,
		double y_cutoff);
void	get_cylinder_uv(t_entry_point pt, t_cylinder *cy, t_hit *hit,
		bool cap);
bool	check_bottom_cap(const t_ray *ray, t_cylinder *cy, double *tm,
		t_hit *hit);
bool	check_top_cap(const t_ray *ray, t_cylinder *cy, double *tm,
		t_hit *hit);
bool	check_body(const t_ray *ray, t_cylinder *cy, double *tm, t_hit *hit);

/* 4. IMPLEMENTATION IMPORTS */
/* Note: do not include scene.h here to avoid circular includes; use
 * forward-declarations instead. */

#endif
