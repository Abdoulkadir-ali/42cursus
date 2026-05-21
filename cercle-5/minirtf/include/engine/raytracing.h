/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/02 17:25:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

# include <immintrin.h>
# include <stdbool.h>
# include "maths.h"
# include "physics.h"
# include "scene.h"
# include "shapes.h"

# define SAH_BINS 16

typedef struct s_tri_soa4
{
	t_vec4	ax;
	t_vec4	ay;
	t_vec4	az;
	t_vec4	e1x;
	t_vec4	e1y;
	t_vec4	e1z;
	t_vec4	e2x;
	t_vec4	e2y;
	t_vec4	e2z;
	t_vec4	nx;
	t_vec4	ny;
	t_vec4	nz;
	int		ids[4];
}			t_tri_soa4;

typedef struct s_bvh_node
{
	t_aabb	box;
	size_t	first;
	size_t	count;
	int		simd_idx;
}			t_bvh_node;

typedef struct s_bvh
{
	t_bvh_node	*nodes;
	size_t		n_nodes;
	size_t		cap_nodes;
	size_t		*indices;
	size_t		n_indices;
	size_t		n_soa;
	size_t		n_soa_capacity;
	t_tri_soa4	*soa_tris;
}				t_bvh;

typedef struct s_bin
{
	t_aabb	box;
	size_t	count;
}			t_bin;

typedef struct s_task
{
	size_t	node;
	size_t	start;
	size_t	end;
}			t_task;

typedef struct s_trav
{
	const t_bvh		*bvh;
	const t_ray		*r;
	const t_object	*objs;
	t_hit			*out;
}					t_trav;

typedef struct s_occ
{
	const t_bvh		*bvh;
	const t_ray		*r;
	const t_object	*objs;
	float			max_t;
}					t_occ;

typedef struct s_bd
{
	t_aabb	*boxes;
	t_vec3	*centers;
	t_task	*stack;
	t_task	out[2];
	size_t	sp;
	size_t	n;
}			t_bd;

typedef struct s_sah
{
	const t_aabb	*boxes;
	const t_vec3	*centers;
	size_t			*idx;
	size_t			n;
	int				axis;
	float			k;
	float			bmin;
}					t_sah;

typedef struct s_split
{
	t_aabb	left[SAH_BINS];
	t_aabb	right[SAH_BINS];
	size_t	lc[SAH_BINS];
	size_t	rc[SAH_BINS];
}			t_split;

typedef struct s_sah_out
{
	size_t	split;
	t_aabb	left;
	t_aabb	right;
}			t_sah_out;

struct s_app;

typedef struct s_raytracing_settings
{
	int		max_bounces;
	int		shadow_samples;
	float	emit_mult;
	float	shadow_ray_gate;
	bool	shadows;
	bool	emitters_as_lights;
	bool	show_normals;
	bool	blackbody;
	bool	soft_shadows;
	bool	indirect_light;
	bool	lensing_on;
	bool	collision_heat;
}			t_raytracing_settings;

float	axis_val(t_vec3 v, int a);
int		pick_axis(t_aabb cb, float *kk, float *bmin);
void	bin_objs(t_bin *bins, t_sah *s);
int		best_split(t_bin *bins, float *out_cost, t_aabb *lb, t_aabb *rb);
size_t	partition_idx(t_sah s, int best);
int		sah_choose_axis(t_sah *s, t_sah_out *out);
t_aabb	obj_box(const t_object *o);
t_vec3	obj_center(const t_object *o);
size_t	push_node(t_bvh *bvh);
void	make_leaf(t_bvh *bvh, t_task t, const t_aabb *boxes, size_t *idx);
int		subdivide(t_bvh *bvh, t_task t, t_sah *s, t_task out[2]);
int		bvh_build(t_bvh *bvh, t_object *objs, int n);
void	bvh_free(t_bvh *bvh);
void	bvh_refit(t_bvh *bvh, const t_object *objs);
int		hit_one(const t_object *o, const t_ray *r, t_hit *h);
int		hit_triangle_sse(const t_tri_soa4 *t, const t_ray *r, t_hit *h);
int		bvh_traverse(const t_bvh *bvh, const t_ray *r, t_hit *out,
			const t_object *objs);
int		bvh_occluded(const t_bvh *bvh, const t_ray *r, float max_t,
			const t_object *objs);
int		bvh_rebuild(struct s_app *app);
void	bvh_prepare_simd(t_bvh *bvh, const t_object *objs);
void	assign_node_soa(t_bvh *bvh, const t_object *objs, t_bvh_node *node);

#endif
