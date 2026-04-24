/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_raytracing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:26:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 15:23:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_ENGINE_RAYTRACING_H
# define TYPES_ENGINE_RAYTRACING_H

# include "maths.h"

typedef struct s_entry_point
{
	t_vec3	p;
	t_vec3	center;
	double	radius;
	double	height;
	double	h;
}	t_entry_point;

typedef struct s_bvh_ref
{
	uint8_t				type;
	size_t				index;
}						t_bvh_ref;

typedef struct s_hit
{
	bool				hit;
	double				t;
	t_vec3				point;
	t_vec3				normal;
	t_vec3				tangent;
	t_vec3				bitangent;
	t_bvh_ref			ref;
	void				*mesh;
	size_t				tri_idx;
	t_vec3				bary;
	double				u;
	double				v;	bool				back_face;}						t_hit;

typedef struct s_trace
{
	t_hit				*hit;
	const struct s_mesh	*mesh;
	const t_ray			*ray;
	double				dist;
	size_t				stack[64];
	size_t				top;
	size_t				node_idx;
	t_index				best_tri;
	double				best_t;
	t_vec2				best_uv;
	size_t				node_count;
	size_t				tri_count;
}						t_trace;

typedef struct s_bvh_node
{
	t_aabb				bbox;
	size_t				left_or_first;
	size_t				count;
}						t_bvh_node;

typedef struct s_bvh_tmp_node
{
	t_aabb				bbox;
	struct s_bvh_tmp_node	*left;
	struct s_bvh_tmp_node	*right;
	t_bvh_ref			*refs;
	size_t				num_refs;
}						t_bvh_tmp_node;

typedef struct s_bvh_node4
{
	float				min_x[4];
	float				min_y[4];
	float				min_z[4];
	float				max_x[4];
	float				max_y[4];
	float				max_z[4];
	size_t				child[4];
	size_t				count[4];
	size_t				n_children;
}						t_bvh_node4;

typedef struct s_bvh
{
	struct s_scene		*scene;
	t_bvh_node			*nodes;
	t_bvh_ref			*refs;
	size_t				num_nodes;
	size_t				num_refs;
	t_bvh_node4			*nodes4;
	size_t				num_nodes4;
}						t_bvh;

typedef struct s_mbvh_stk
{
	size_t				st[64];
	size_t				top;
	bool				any;
}						t_mbvh_stk;

typedef enum e_rt_preset
{
	RT_PRESET_CUSTOM,
	RT_PRESET_NATURAL,
	RT_PRESET_VIVID,
	RT_PRESET_CINEMATIC,
	RT_PRESET_COUNT
}	t_rt_preset;

typedef struct s_raytracer_settings
{
	bool	blinn_phong;      /* correct pow() specular (vs Ward approx)  */
	double	brightness;       /* +/- additive: 50=neutral, 0=black, 100=white */
	double	contrast;         /* 50=neutral, 0=flat, 100=high contrast    */
	double	saturation;       /* 50=neutral, 0=greyscale, 100=vivid       */
	double	gamma;            /* 50=neutral (gamma 1.0), 100=gamma 2.2    */
	bool	bloom_enabled;
	double	bloom_threshold;
	double	bloom_intensity;
	double	bloom_radius;
	bool	dof_enabled;
	double	dof_aperture;     /* lens radius in world units              */
	double	dof_focal_dist;   /* distance to focus plane                */
	/* Visual effects */
	bool	ao_enabled;       /* ambient occlusion                       */
	int		ao_samples;       /* rays per pixel (2-16)                   */
	double	ao_radius;        /* max occlusion reach in world units      */
	double	ao_strength;      /* darkening factor 0..1                   */
	bool	fresnel_enabled;  /* Schlick edge reflections                */
	bool	gi_enabled;       /* one-bounce indirect diffuse GI          */
	double	gi_strength;      /* GI contribution scale 0..1             */
	bool	aces_enabled;     /* ACES filmic tonemapping                 */
	bool	beer_enabled;     /* Beer's law atmospheric absorption       */
	double	beer_density;     /* absorption coefficient (e.g. 0.0..0.2) */
	bool	chroma_enabled;   /* chromatic aberration on refraction      */
	double	chroma_dispersion;/* per-channel IOR split 0..0.1           */
	bool	stochastic_lights; /* area-light soft shadows via cone sampling */
	bool	draft_mode;        /* set when camera is moving — skip GI+stoch */
	bool	lights_on_bounces; /* run lights/emissive at all depths (quality mode) */
	t_rt_preset	preset;           /* RT_PRESET_CUSTOM .. RT_PRESET_CINEMATIC  */
}						t_raytracer_settings;

typedef struct s_raytracer_stats
{
	size_t		frame_count;	  /* total frames rendered              */
	size_t		rays_frame;		  /* primary rays cast last frame       */
	size_t		rays_total;		  /* cumulative primary rays            */
	double		last_render_ms;   /* wall-clock of last frame (ms)      */
}					t_raytracer_stats;

typedef struct s_raytracer_cache
{
	double		half_h;			  /* tan(fov/2) at last cache          */
	double		fov;			  /* FOV (degrees) at last cache       */
	t_vec2s		res;			  /* render resolution at last cache   */
}					t_raytracer_cache;

typedef struct s_raytracer_engine
{
	t_raytracer_settings	settings;
	t_raytracer_stats		stats;
	t_raytracer_cache		cache;
}					t_raytracer_engine;

typedef struct s_shading_ctx
{
	double	d_surf;
	t_vec3	ldir;
	double	ndotl;
	double	emitter_facing;
}	t_shading_ctx;

typedef struct s_shading_cache
{
	t_vec3		view;
	double		ndotv;
	t_vec3		org;
	uint64_t	seed_pos;
}	t_shading_cache;

typedef struct s_shading
{
	t_hit					*hit;
	struct s_scene			*scene;
	const t_bvh				*bvh;
	const t_ray				*ray;
	struct s_material		mat;
	t_vec3					albedo;
	t_vec3					aux_v;
	t_vec3					em_normal;
	const t_raytracer_settings	*opts;
	size_t					frame_idx;
	t_shading_cache				cache;
}						t_shading;

typedef struct s_build_item
{
	t_bvh_ref			ref;
	t_aabb				bbox;
	t_vec3				centroid;
}						t_build_item;

typedef struct s_split_info
{
	t_index				axis;
	size_t				split;
	double				cost;
}						t_split_info;
typedef struct s_cyl_info
{
	t_vec3				base;
	t_vec3				top;
	t_vec3				axis;
	double				r;
	t_vec3				tan;
}					t_cyl_info;
#endif
