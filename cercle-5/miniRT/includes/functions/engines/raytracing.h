/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:33:54 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 11:55:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H
# define MAX_LEAF_OBJECTS 4
# define BVH_BINS 16
#define MAX_DEPTH 5
#define LENS_MIN_RS 1.0
#define LENS_G_C2 1e-8
#define LENS_STEP_FAR 0.25
#define LENS_STEP_NEAR 0.04
#define LENS_STEP_FRAC 0.08
#define LENS_MAX_STEPS 3072
#define LENS_INFLUENCE 50.0
#define LENS_MAX_BODIES 32

# include "scene.h"
# include "thread.h"

typedef struct s_light_calc
{
	t_vec3	ld;
	t_vec3	norm;
	t_vec3	target;
	double	dist;
	double	ndotl;
}	t_light_calc;

typedef struct s_ray_query
{
	const t_ray	*ray;
	t_hit		*hit;
	double		*tm;
}	t_ray_query;

typedef struct s_occ_query
{
	const t_bvh	*bvh;
	const t_ray	*ray;
	double		max_t;
}	t_occ_query;

typedef struct s_box_calc
{
	t_vec3	ax[3];
	double	p[3];
	double	d[3];
	double	inv_d[3];
	double	h[3];
	t_ray	ray;
}	t_box_calc;

typedef struct s_stk_entry
{
	uint32_t	idx;
	float		t;
}	t_stk_entry;

typedef struct s_cap_calc
{
	t_vec3	p[2];
	double	t[3];
	bool	hit[3];
	double	best;
	t_index	type;
}	t_cap_calc;

typedef struct s_bvh_trav
{
	t_stk_entry		*stack;
	size_t			*top;
	const t_bvh		*bvh;
	const t_ray		*ray;
}	t_bvh_trav;

typedef struct s_bvh_trav_init
{
	t_stk_entry		*stack;
	size_t			*top;
	const t_bvh		*bvh;
	const t_ray		*ray;
	double			t0;
}	t_bvh_trav_init;

typedef struct s_add_task
{
	t_scene			*sc;
	t_build_item	*items;
	size_t			*k;
	int				type;
	size_t			next;
	size_t			start_k;
	size_t			ki_next;
}	t_add_task;

typedef struct s_lens_body
{
	t_vec3	pos;
	double	mass;
	double	rs;
}	t_lens_body;


/* Private sweep context used only by the BVH split implementation */
typedef struct s_sweep
{
    t_aabb  bboxes[BVH_BINS];
    size_t  cnts[BVH_BINS];
    double  lo;
    double  hi;
    double  inv;
    size_t  axis;
}   t_sweep;




/* 3. FUNCTION PROTOTYPES */
/* srcs/raytracing/bvh/tree/ */
/* Helper functions – internal to the split folder */
void    init_bins(t_sweep *sw);
void    fill_bins(t_sweep *sw, t_build_item *items, size_t count);


t_bvh			*bvh_create(t_scene *scene);
void			bvh_destroy(t_bvh *bvh);
void			node_destroy(t_bvh_tmp_node *node);
void			find_best_split(t_build_item *items, size_t count,
				t_split_info *info, t_aabb *bounds);
t_bvh_tmp_node	*init_leaf_node(t_build_item *items, size_t count);
t_bvh_tmp_node	*build_recursive(t_build_item *items, size_t count);
size_t			collect_objects_worker(t_scene *scene, t_build_item *items);
int				compare_x(const void *a, const void *b);
int				compare_y(const void *a, const void *b);
int				compare_z(const void *a, const void *b);
void			build_emissive_cache(t_scene *sc);
void			cache_secondary_em(t_scene *sc, t_emissive_ref *cache,
					size_t *n);
void			cache_volume_em(t_scene *sc, t_emissive_ref *cache, size_t *n);
t_emissive_ref	init_emissive_ref(t_type type, size_t index);

/* srcs/raytracing/bvh/bound/ */
t_aabb	aabb_from_ref(t_scene *s, t_bvh_ref ref);
t_aabb	aabb_union(const t_aabb *a, const t_aabb *b);
t_aabb	aabb_create_empty(void);
t_aabb	aabb_transform(t_aabb local, t_transform t);
void	aabb_expand_point(t_aabb *bbox, t_vec3 p);
double	aabb_surface_area(t_aabb bbox);
/* aabb_intersect_fast is static inline in maths.h */
t_aabb	sphere_aabb(const t_sphere *sp);
t_aabb	tri_shape_aabb(t_tri_shape *tr);
t_aabb	rect_aabb(t_rect *rc);
t_aabb	pyramid_aabb(t_pyramid *py);
t_aabb	box_aabb(t_box *bx);
t_aabb	capsule_aabb(t_capsule *cap);
t_aabb	plane_aabb(void);
t_aabb	cylinder_aabb(t_cylinder *cy);
t_aabb	cone_aabb(t_cone *co);

/* srcs/raytracing/bvh/traverse/ */
bool	bvh_intersect(const t_bvh *bvh, const t_ray *ray, t_hit *hit);
bool	bvh_intersect4(const t_bvh *bvh, const t_ray *ray, t_hit *hit);
void	bvh_push_children(t_bvh_trav *v, size_t idx, double cur_t);
void	bvh_trav_push0(t_bvh_trav *v, t_bvh_trav_init *cfg);
bool	bvh_occluded(const t_bvh *bvh, const t_ray *ray, double max_t);
bool	bvh_occluded4(const t_bvh *bvh, const t_ray *ray, double max_t);
bool	occlude_cylinder(const t_ray *ray, t_cylinder *cy, double max_t);
bool	occlude_primitive(const t_ray *ray, t_scene *sc, t_bvh_ref ref,
			double max_t);
bool	intersect_object(const t_ray *ray, t_scene *scene, t_bvh_ref ref,
			t_hit *hit);

/* srcs/raytracing/bvh/tree/ */
void	bvh_collapse(t_bvh *bvh);

t_vec3	clamp_color(t_vec3 color, const t_raytracer_settings *opts);
bool	is_emissive(t_scene *sc, size_t mat_id);

/* srcs/raytracing/trace/ */
void			ray_init(t_ray *ray, t_vec3 origin, t_vec3 direction);
void			ray_normalize_direction(t_ray *ray);
bool			lens_ray(const t_ray *ray, t_scene *sc, t_ray *out_ray,
					bool *captured);
bool			point_inside_eh(t_vec3 pos, t_scene *sc);
t_vec3			trace_ray(const t_bvh *bvh, const t_ray *ray, t_scene *scene);
t_vec3			trace_ray_ex(const t_bvh *bvh, const t_ray *ray, t_scene *scene,
					float *out_t);
void			check_planes(const t_ray *ray, t_scene *sc, t_hit *hit,
					bool *any);
t_vec3			add_volumetrics(const t_ray *ray, t_scene *sc, double max_t);
t_vec3			compute_color(t_hit *hit, t_scene *scene, const t_bvh *bvh,
					const t_ray *ray);
bool			is_in_shadow(const t_bvh *bvh, t_vec3 p, t_vec3 ldir_norm,
					double dist);
t_vec3			pixel_color(t_vec3 obj, t_vec3 light, double intensity);
void			get_material(t_shading *sha);
void			apply_bump(t_shading *sha);
bool			light_visible(t_shading *sha, t_light light, t_light_calc *c);
double			calc_specular(t_shading *sha, t_vec3 ld_norm);
t_vec3			calc_light(t_shading *sha, t_light light);
void			add_emissive_lighting(t_shading *sha, t_scene *sc,
					t_vec3 *total);
void			em_vol(t_shading *sha, t_scene *sc, t_vec3 *total,
					t_emissive_ref ref);
void			em_surf(t_shading *sha, t_scene *sc, t_vec3 *total,
					t_emissive_ref ref);
void			em_cap(t_shading *sha, t_scene *sc, t_vec3 *total,
					t_emissive_ref ref);
void			em_cylinder_sub(t_shading *sha, t_scene *sc, t_vec3 *total,
					t_emissive_ref ref);
void			em_cone_sub(t_shading *sha, t_scene *sc, t_vec3 *total,
					t_emissive_ref ref);
t_vec3			closest_pt_tri(t_vec3 p, t_vec3 a, t_vec3 b, t_vec3 c);
t_vec3			closest_pt_rect(t_vec3 p, t_vec3 v0, t_vec3 v1, t_vec3 v2);
void			apply_em(t_shading *sha, t_vec3 *total, t_material *mat,
					double r);
double			shading_attenuation(double dist_sq);
uint64_t		rt_next_rand(uint64_t *seed);
double			rt_rand_d(uint64_t *seed);
void			setup_shading(t_shading *sha, t_hit *hit, t_scene *scene,
					const t_bvh *bvh);
double			compute_ao(const t_shading *sha);
t_vec3			compute_indirect(t_shading *sha, const t_ray *ray);
t_vec3			compute_refraction(t_shading *sha, const t_ray *ray,
					double *kr, double next_w);
t_vec3			compute_reflection(t_shading *sha, const t_ray *ray,
					double next_w);
void			rt_build_onb(t_vec3 n, t_vec3 *v1, t_vec3 *v2);
t_vec3			rt_random_on_sphere(uint64_t *seed);
t_vec3			rt_random_on_hemisphere(t_vec3 normal, uint64_t *seed);
t_vec3			rt_random_cosine_weighted(t_vec3 normal, uint64_t *seed);
t_vec3			rt_random_on_cone(t_vec3 axis, double cos_theta_max,
					uint64_t *seed);
t_vec3			rt_kelvin_to_rgb(double kelvin);
void			apply_blackbody_to_mat(t_material *mat);
double			rt_halton(size_t i, size_t base);

/* Lens helpers */
double			schwarzschild_r(double mass);
size_t			build_lens_bodies(t_scene *sc,
					t_lens_body bodies[LENS_MAX_BODIES]);
bool			ray_near_black_hole(const t_ray *ray,
					const t_lens_body *bodies, size_t nb);
double			min_dist_to_body(t_vec3 pos, const t_lens_body *bodies,
					size_t nb);
bool			march_ray(t_ray *bent, const t_lens_body *bodies, size_t nb);

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
void	cylinder_precompute(t_cylinder *cy);
void	get_cylinder_uv(t_entry_point pt, t_cylinder *cy, t_hit *hit,
			bool cap);
bool	check_bottom_cap(const t_ray *ray, t_cylinder *cy, double *tm,
			t_hit *hit);
bool	check_top_cap(const t_ray *ray, t_cylinder *cy, double *tm,
			t_hit *hit);
bool	check_body(const t_ray *ray, t_cylinder *cy, double *tm, t_hit *hit);
static inline __attribute__((always_inline))
bool	near_sphere_t(const t_ray *ray, t_vec3 center, double radius,
			double *t_out)
{
	t_vec3	oc;
	double	b;
	double	c;
	double	disc;

	oc = vec3_sub(ray->origin, center);
	b = vec3_dot(oc, ray->direction);
	c = vec3_dot(oc, oc) - radius * radius;
	disc = b * b - c;
	if (disc < 0.0)
		return (false);
	disc = __builtin_sqrt(disc);
	*t_out = -b - disc;
	if (*t_out < 1e-6)
		*t_out = -b + disc;
	return (*t_out > 1e-6);
}

static inline __attribute__((always_inline))
bool	cylinder_body_t(const t_ray *ray, t_capsule *cap, double *t_out)
{
	t_vec3	oc;
	t_vec3	perp[2];
	double	abc[4];

	oc = vec3_sub(ray->origin, cap->transform.pos);
	perp[0] = vec3_sub(ray->direction,
			vec3_scale(cap->axis, vec3_dot(ray->direction, cap->axis)));
	perp[1] = vec3_sub(oc, vec3_scale(cap->axis, vec3_dot(oc, cap->axis)));
	abc[0] = vec3_dot(perp[0], perp[0]);
	if (abc[0] < 1e-10)
		return (false);
	abc[1] = 2.0 * vec3_dot(perp[0], perp[1]);
	abc[2] = vec3_dot(perp[1], perp[1]) - cap->radius * cap->radius;
	abc[3] = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if (abc[3] < 0.0)
		return (false);
	{
		double	sq = __builtin_sqrt(abc[3]);
		double	inv2a = 1.0 / (2.0 * abc[0]);
		*t_out = (-abc[1] - sq) * inv2a;
		if (*t_out < 1e-6)
			*t_out = (-abc[1] + sq) * inv2a;
	}
	abc[3] = vec3_dot(vec3_sub(vec3_add(ray->origin,
					vec3_scale(ray->direction, *t_out)),
			cap->transform.pos), cap->axis);
	return (*t_out > 1e-6 && __builtin_fabs(abc[3]) <= cap->half_height);
}
void	update_capsule_hit(t_capsule *cp, t_hit *h, t_cap_calc *c,
			const t_ray *r);

/* 4. IMPLEMENTATION IMPORTS */
# include "scene.h"

#endif
