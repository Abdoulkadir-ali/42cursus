/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:33:54 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 20:46:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H
# define MAX_LEAF_OBJECTS 4
# define BVH_BINS 16
# define MAX_DEPTH 5

# include "scene.h"
# include "thread.h"

typedef struct s_light_calc
{
	t_vec3	ld;
	t_vec3	norm;
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
	double	h[3];
}	t_box_calc;

typedef struct s_cap_calc
{
	t_vec3	p[2];
	double	t[3];
	bool	hit[3];
	double	best;
	int		type;
}	t_cap_calc;

typedef struct s_bvh_trav
{
	size_t			*stack;
	double			*stk_t;
	size_t			*top;
	const t_bvh		*bvh;
	const t_ray		*ray;
}	t_bvh_trav;

typedef struct s_add_task
{
	t_scene			*sc;
	t_build_item	*items;
	size_t			*k;
	int				type;
	size_t			next;
	size_t			start_k;
}	t_add_task;


/* Private sweep context used only by the BVH split implementation */
typedef struct s_sweep
{
    t_aabb  bboxes[BVH_BINS];
    size_t  cnts[BVH_BINS];
    double  lo;
    double  hi;
    double  inv;
    int     axis;
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

/* srcs/raytracing/bvh/bound/ */
t_aabb	aabb_from_ref(t_scene *s, t_bvh_ref ref);
t_aabb	aabb_union(const t_aabb *a, const t_aabb *b);
t_aabb	aabb_create_empty(void);
t_aabb	aabb_transform(t_aabb local, t_transform t);
void	aabb_expand_point(t_aabb *bbox, t_vec3 p);
double	aabb_surface_area(t_aabb bbox);
bool	aabb_intersect_fast(const t_aabb *aabb, const t_ray *ray, double *tmin,
			double *tmax);
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
bool	bvh_occluded(const t_bvh *bvh, const t_ray *ray, double max_t);
bool	bvh_occluded4(const t_bvh *bvh, const t_ray *ray, double max_t);
bool	occlude_cylinder(const t_ray *ray, t_cylinder *cy, double max_t);
bool	occlude_primitive(const t_ray *ray, t_scene *sc, t_bvh_ref ref,
			double max_t);
bool	intersect_object(const t_ray *ray, t_scene *scene, t_bvh_ref ref,
			t_hit *hit);

/* srcs/raytracing/bvh/tree/ */
void	bvh_collapse(t_bvh *bvh);

t_vec3	clamp_color(t_vec3 color);
bool	is_emissive(t_scene *sc, size_t mat_id);

/* srcs/raytracing/trace/ */
void	ray_init(t_ray *ray, t_vec3 origin, t_vec3 direction);
void	ray_normalize_direction(t_ray *ray);
t_vec3	trace_ray(const t_bvh *bvh, const t_ray *ray, t_scene *scene);
t_vec3	trace_ray_ex(const t_bvh *bvh, const t_ray *ray, t_scene *scene, float *out_t);
t_vec3	compute_color(t_hit *hit, t_scene *scene, const t_bvh *bvh,
			const t_ray *ray);
bool	is_in_shadow(const t_bvh *bvh, t_vec3 p, t_vec3 ldir_norm, double dist);
t_vec3	pixel_color(t_vec3 obj, t_vec3 light, double intensity);
void	get_material(t_shading *sha);
void	apply_bump(t_shading *sha);
t_vec3	calc_light(t_shading *sha, t_light light);
void	add_emissive_lighting(t_shading *sha, t_scene *sc, t_vec3 *total);
void	em_vol(t_shading *sha, t_scene *sc, t_vec3 *total, t_emissive_ref ref);
void	em_surf(t_shading *sha, t_scene *sc, t_vec3 *total, t_emissive_ref ref);
void	apply_em(t_shading *sha, t_vec3 *total, t_material *mat, double r);
double	shading_attenuation(double dist_sq);

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

/* 4. IMPLEMENTATION IMPORTS */
# include "scene.h"

#endif
