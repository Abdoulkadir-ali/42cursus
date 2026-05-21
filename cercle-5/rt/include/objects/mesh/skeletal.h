/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skeletal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 02:26:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 18:41:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKELETAL_H
# define SKELETAL_H

# include "maths.h"
# include "threads.h"
# include <stdbool.h>

typedef struct s_animation_settings
{
	float	mip_bias;
	bool	anim_skinning;
	bool	use_mips;
}			t_animation_settings;

typedef struct s_keyframe
{
	int		lo;
	int		hi;
	float	alpha;
}			t_keyframe;

typedef struct s_anim_node
{
	t_vec3	t;
	t_vec4	r;
	t_vec3	s;
	t_vec3	bt;
	t_vec4	br;
	t_vec3	bs;
	int		parent;
	t_mat4	world;
	t_mat4	bind_world;
	t_mat4	bind_world_inv;
	t_mat4	local_mat;
	int		has_matrix;
}			t_anim_node;

typedef struct s_anim_skin
{
	int		*joints;
	int		n_joints;
	float	*ibm;
}			t_anim_skin;

typedef struct s_anim_chan
{
	int		target_node;
	int		path;
	int		interp;
	int		n_keys;
	int		comp;
	float	*times;
	float	*values;
}			t_anim_chan;

typedef struct s_anim_clip
{
	char		name[64];
	t_anim_chan	*chans;
	int			n_chans;
	float		duration;
}				t_anim_clip;

typedef struct s_anim_prim
{
	float			*positions;
	float			*uvs;
	float			*weights;
	unsigned int	*joints;
	unsigned int	*indices;
	int				n_verts;
	int				n_tris;
	int				node;
	int				skin;
	int				bvh_base;
	int				tex_id;
	t_vec3			color;
}					t_anim_prim;

struct s_reskin;

typedef struct s_reskin_job
{
	const struct s_reskin	*c;
	int						start;
	int						end;
}	t_reskin_job;

typedef struct s_animator
{
	t_anim_node	*nodes;
	int			n_nodes;
	t_anim_skin	*skins;
	int			n_skins;
	t_anim_clip	*clips;
	int			n_clips;
	t_anim_prim	*prims;
	int			n_prims;
	int			active;
	float		time;
	int			playing;
	float		speed;
	int			loop;
	int			group_id;
	float		pre[9];
	t_vec3		pre_origin;
	float		pre_scale;
	t_mat4		extra;
	int			has_extra;
	float			*joint_mats;
	int				max_joints;
	t_reskin_job	reskin_jobs[MAX_THREADS];
}				t_animator;

typedef struct s_reskin
{
	t_animator		*a;
	t_anim_prim		*p;
	struct s_scene	*s;
	t_mat4			mesh_inv;
	int				has_inv;
}				t_reskin;

typedef struct s_subdets
{
	t_vec3	up[2];
	t_vec3	lo[2];
}			t_subdets;

/* Column-major 4x4 matrix macros.
** M4_AT : Get/Set element at row r, col c.
** DET2  : 2x2 determinant of rows (r0,r1) and cols (c0,c1).
** C3	: 3x3 cofactor pattern. */
# define M4_AT(m, r, c)  ((m)[(c) * 4 + (r)])
# define DET2(m, r0, c0, r1, c1) \
	(M4_AT(m, r0, c0) * M4_AT(m, r1, c1) - M4_AT(m, r1, c0) * M4_AT(m, r0, c1))
# define C3(m, r, c1, d1, c2, d2, c3, d3) \
	(M4_AT(m, r, c1) * (d1) - M4_AT(m, r, c2) * (d2) + M4_AT(m, r, c3) * (d3))

struct s_app;
struct s_scene;

t_animator	*skel_animator_create(void);
void		skel_animator_destroy(t_animator *a);
void		skel_animator_attach(struct s_scene *s, t_animator *a);
void		skel_animator_apply_extra_xform(t_animator *a, const t_mat4 m);
void		skel_animator_extra_apply(t_animator *a, int kind, t_vec3 piv,
				const void *data);
void		skel_animator_tick(struct s_app *app, float dt);
int			skel_animator_clip_count(const t_animator *a);
const char	*skel_animator_clip_name(const t_animator *a, int i);
float		skel_animator_clip_duration(const t_animator *a, int i);
void		skel_m4_identity(t_mat4 m);
void		skel_m4_mul(const t_mat4 a, const t_mat4 b, t_mat4 o);
void		skel_m4_from_trs(const t_vec3 *t, const t_vec4 *q,
				const t_vec3 *s, t_mat4 m);
t_vec3		skel_m4_xform_pos(const t_mat4 m, t_vec3 p);
int			skel_m4_inverse(const t_mat4 m, t_mat4 out);
t_vec4		skel_q_slerp(t_vec4 a, t_vec4 b, float t);
void		skel_compute_world(t_animator *a);
void		skel_reset_to_bind(t_animator *a);
void		skel_apply_clip(t_animator *a);
void		skel_reskin_all(t_animator *a, struct s_scene *s, struct s_tpool *tp);
t_vec3		skel_skin_vertex(const t_animator *a, const t_anim_prim *p, int v);
void		skel_build_palette(t_animator *a, int skin_idx);

#endif
