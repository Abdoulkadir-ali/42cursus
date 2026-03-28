/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 09:00:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIM_H
# define ANIM_H

# include "objects.h"

/* ----------------------------------------------------------------- */
/*  SCENE-PERSISTENT ANIMATION / SKELETAL TYPES                      */
/*  These live in scene->animated[] and scene->clips[].              */
/*  Engines access them via t_scene only -- never via t_mesh.        */
/*  t_mesh is a LOADER TRANSIENT (see primitives/loader/mesh.h).     */
/* ----------------------------------------------------------------- */

typedef enum e_interp_method
{
	INTERP_LINEAR,
	INTERP_STEP,
	INTERP_CUBIC
}	t_interp_method;

typedef enum e_anim_path
{
	PATH_TRANSLATION,
	PATH_ROTATION,
	PATH_SCALE,
	PATH_WEIGHTS
}	t_anim_path;

typedef struct s_anim_sampler
{
	float			*inputs;
	float			*outputs;
	int				count;
	t_interp_method	method;
}	t_anim_sampler;

typedef struct s_anim_channel
{
	int			sampler_idx;
	int			node_idx;
	t_anim_path	path;
}	t_anim_channel;

typedef struct s_animation
{
	char			*name;
	t_anim_channel	*channels;
	int				channel_count;
	t_anim_sampler	*samplers;
	int				sampler_count;
	float			max_time;
}	t_animation;

typedef struct s_bone_trs
{
	t_vec3	pos;
	t_vec3	rot;	/* Quaternion: x/y/z/w stored in t_vec3.w */
	t_vec3	scale;
}	t_bone_trs;

typedef struct s_bone
{
	int			node_idx;
	int			parent;
	t_mat4		inv_bind_pose;
	t_mat4		local_transform;
	t_mat4		global_transform;
	t_bone_trs	trs;
}	t_bone;

typedef struct s_skinned_mesh
{
	t_vec3			*base_vertices;
	t_vec3			*base_normals;
	t_vec3			*vertices;
	t_vec3			*normals;
	t_bone_weight	*weights;
	t_bone			*skeleton;
	t_mat4			*bone_matrices;
	int				bone_count;
	int				vertex_count;
	int				anim_clip_count;
	int				current_anim;
	double			anim_time;
	int				mat_id;
	t_aabb			bbox;
}	t_skinned_mesh;

#endif
