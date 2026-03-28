
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:16:58 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 10:00:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

# include <math.h>
# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

/* 1. EXTERNAL DEPENDENCIES */
# include "scene.h"
# include "stb_image.h"
# include "dod.h"

/* 2. ENGINE DATA STRUCTURES */

typedef struct s_rt_settings
{
	int					width;
	int					height;
	double				inv_w;
	double				inv_h;
	double				fov;
	double				fov_scale;
	double				aspect_ratio;
	int					samples_per_pixel;
	int					max_depth;
	double				gamma;
	double				shadow_bias;
	t_vec3				void_color;
	bool				use_skybox;
	int					thread_count;
	bool				show_debug_bvh;
}						t_rt_settings;

typedef struct s_rt_material
{
	t_vec3				color;
	double				specular;
	double				shininess;
	double				roughness;
	double				metallic;
	t_vec3				emission;
	double				transparency;
	double				reflectivity;
	double				refract_index;
	int					albedo_tex_idx; /* -1 if none */
	int					normal_map_idx; /* -1 if none */
}						t_rt_material;

typedef struct s_lcalc
{
	double				dist;
	t_vec3				ld_norm;
	double				ndotl;
}						t_lcalc;

typedef struct s_bvh_node
{
	t_aabb				bbox;
	int					left_or_first;
	int					count;
} __attribute__((aligned(32))) t_bvh_node;

typedef struct s_bvh
{
	t_scene				*scene;
	t_bvh_node			*nodes;
	t_prim_ref			*refs;
	int					num_nodes;
	int					num_refs;
}						t_bvh;

typedef struct s_rt_engine
{
	t_scene				*scene;
	t_bvh				*bvh;
	t_emissive_ref		*emissive_cache;
	int					emissive_n;
	void				*mlx;
	void				*win;
	uint32_t			baked_version;
	t_rt_material		*rt_materials;
	unsigned char		**texture_pool;
	t_vec2i				*texture_dims;
	int					texture_count;
	int					texture_cap;
	t_rt_settings		settings;
}						t_rt_engine;

/**
 * @brief THE UNIFIED DOD HIT CONTRACT
 */
typedef struct s_hit
{
	double				t;
	t_vec3				point;
	t_vec3				normal;
	t_vec3				tangent;
	t_vec3				bitangent;
	double				u;
	double				v;
	int					mat_idx;
	t_type type;   // keep for backward compat
	t_bvh_ref ref; // DOD: full reference (type + index)
}						t_hit;

typedef struct s_shading
{
	t_hit				*hit;
	const struct s_rt_engine	*rt;
	const t_ray			*ray;
	const t_rt_material	*mat;
	t_vec3				albedo;
	t_vec3				aux_v;
}						t_shading;

/* -------------------------------------------------------------------------- */
/*                                3. PROTOTYPES                               */
/* -------------------------------------------------------------------------- */

/* --- BAKING & SYNC --- */
void					bake_materials(t_rt_engine *rt, t_scene *scene);
void					raytrace_engine_sync(t_rt_engine *rt, t_scene *scene,
							int w, int h);
int						engine_pool_add_texture(t_rt_engine *rt,
							const char *path);
void					engine_texture_pool_destroy(t_rt_engine *rt);
void					rt_engine_cleanup(t_rt_engine *rt);

/* --- TRACING --- */
void					ray_init(t_ray *ray, t_vec3 origin, t_vec3 direction);
t_vec3					trace_ray(t_rt_engine *rt, const t_ray *ray);
t_vec3					compute_color(t_hit *hit, t_rt_engine *rt,
							const t_ray *ray);
bool					bvh_intersect(const t_bvh *bvh, t_ray *ray,
							t_hit *hit);
bool					is_in_shadow(const t_bvh *bvh, t_vec3 p,
							t_vec3 ldir_norm, double dist);
bool					bvh_occluded(const t_bvh *bvh, const t_ray *ray,
							double max_dist);
void					get_sphere_uv(t_vec3 normal, double *u, double *v);
void					get_plane_uv(t_vec3 p, t_vec3 normal, t_hit *hit);
void					get_cone_uv(t_hit *hit, t_primitive_array *p, int idx,
							t_vec3 radial, double h);

/* --- INTERSECTION (100% DOD) --- */
bool					intersect_sphere(const t_ray *ray, t_primitive_array *p,
							int i, t_hit *h);
bool					intersect_plane(const t_ray *ray, t_primitive_array *p,
							int i, t_hit *h);
bool					intersect_cylinder(const t_ray *ray,
							t_primitive_array *p, int i, t_hit *h);
bool					intersect_cone(const t_ray *ray, t_primitive_array *p,
							int i, t_hit *h);
bool					intersect_tri_soa(const t_ray *ray, t_tri_array *t,
							int i, t_hit *h);
bool					intersect_triangle_fast(const t_ray *ray, t_vec3 tr[3],
							double *t, t_vec2 *uv);
bool					intersect_rect(const t_ray *ray, t_primitive_array *p,
							int i, t_hit *h);
bool					intersect_pyramid(const t_ray *ray,
							t_primitive_array *p, int i, t_hit *h);
bool					intersect_box(const t_ray *ray, t_primitive_array *p,
							int i, t_hit *h);
bool					intersect_capsule(const t_ray *ray,
							t_primitive_array *p, int i, t_hit *h);
bool					intersect_object(const t_ray *ray, t_scene *scene,
							t_bvh_ref ref, t_hit *hit);

/* --- SHADING --- */
t_vec3					calc_light(t_shading *sha, const t_rt_engine *rt, t_light light);
void					add_emissive_lighting(t_shading *sha, const t_rt_engine *rt,
							t_vec3 *total);
void					apply_emissive_hit(t_shading *sha,
						t_vec3 *total, t_material *m, t_vec3 lrad);
void					emissive_primary(t_shading *sha, const t_rt_engine *rt,
						t_vec3 *tot, t_emissive_ref r);
void					emissive_complex(t_shading *sha, const t_rt_engine *rt,
						t_vec3 *tot, t_emissive_ref r);
void					apply_bump(t_shading *sha);
t_vec3					pixel_color(t_vec3 obj, t_vec3 light, double intensity);
t_vec3					clamp_color(t_vec3 color);
void					get_shading_material(t_shading *sha);
t_vec3					sample_texture_pool(t_shading *sha, int idx,
							double u, double v);

/* --- BVH (Acceleration Structure) --- */
t_bvh					*bvh_build_global(t_scene *scene);
void					bvh_destroy(t_bvh *bvh);
void					build_emissive_cache(t_scene *sc);
bool					aabb_intersect_fast(const t_aabb *aabb, const t_ray *ray,
						double *tmin, double *tmax);
double					aabb_hit_time_or_neg1(const t_bvh *bvh, int idx,
						const t_ray *ray, double max_t);
void					process_leaf_flat(const t_bvh *bvh, int node_idx,
						const t_ray *ray, t_hit *hit);
bool					run_traverse_loop(const t_bvh *bvh, const t_ray *ray,
						t_hit *hit);
bool					bvh_traverse_loop(const t_bvh *bvh, const t_ray *ray,
						double max_t);
bool					occlude_object(const t_ray *ray, t_scene *scene,
						t_bvh_ref ref, double max_t);

/* ---- Internal intersection UV / helper prototypes ---- */

void				get_sphere_uv(t_vec3 normal, double *u, double *v);
void				set_sphere_hit_data(const t_ray *ray, t_sphere *sp,
						t_hit *hit);
void				get_plane_uv(t_vec3 p, t_vec3 n, t_hit *hit);
bool				intersect_triangle_fast(const t_ray *ray, t_vec3 tri[3],
						double *t, t_vec2 *uv);
void				pyramid_cache_verts(t_pyramid *py);

#endif
