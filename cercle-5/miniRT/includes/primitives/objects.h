/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 17:17:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
#define OBJECTS_H

/* External dependencies */
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

/* 1. NEUTRAL DEPENDENCIES */
# include "helpers.h"
# include "parser.h"
# include "surface.h"

/* 2. LEAF STRUCTURES */

/* ------------------------------------------------------------------------- */
/*                             LEAF STRUCTURES                               */
/* ------------------------------------------------------------------------- */

/* Enums */

typedef enum e_interpolation
{
	INTERP_LINEAR,
	INTERP_STEP,
	INTERP_CUBIC
}							t_interpolation;

typedef enum e_type
{
	TYPE_NONE = 0,
	TYPE_AMBIENT,
	TYPE_CAMERA,
	TYPE_LIGHT,
	TYPE_SPHERE,
	TYPE_PLANE,
	TYPE_MESH,
	TYPE_ANIM,
	TYPE_CYLINDER,
	TYPE_CONE,
	TYPE_TRI,
	TYPE_RECT,
	TYPE_PYRAMID,
	TYPE_BOX,
	TYPE_CAPSULE
}							t_type;

typedef enum e_light_type
{
	LIGHT_POINT,
	LIGHT_SPOT,
	LIGHT_EMISSIVE
}							t_light_type;

typedef enum e_anim_path
{
	PATH_TRANSLATION,
	PATH_ROTATION,
	PATH_SCALE,
	PATH_WEIGHTS
}							t_anim_path;

typedef struct s_emissive_ref
{
	t_type					type;
	int						index;
}							t_emissive_ref;

typedef struct s_prim_ref
{
	uint8_t					type;
	int						index;
}							t_prim_ref;

typedef struct s_sphere
{
	t_transform				transform;
	double					radius;
	double					radius_sq;
	int						mat_id;
	t_vec3					temp_color;
}							t_sphere;

typedef struct s_plane
{
	t_transform				transform;
	t_vec3					normal;
	int						mat_id;
	t_vec3					temp_color;
}							t_plane;

typedef struct s_cylinder
{
	t_transform				transform;
	double					radius;
	double					height;
	int						mat_id;
	t_vec3					temp_color;
}							t_cylinder;

typedef struct s_cone
{
	t_transform				transform;
	double					radius;
	double					height;
	int						mat_id;
	t_vec3					temp_color;
}							t_cone;

typedef struct s_rect
{
	t_transform				transform;
	t_vec3					v[4];
	int						mat_id;
	t_vec3					temp_color;
}							t_rect;

typedef struct s_pyramid
{
	t_transform				transform;
	double				base_size;
	double				height;
	t_vec3				up;
	int					mat_id;
	t_vec3				c[4];   /* Cached base vertices */
	t_vec3				apex;   /* Cached apex */
	t_vec3				temp_color;
}							t_pyramid;

typedef struct s_box
{
	t_transform				transform;
	t_vec3					half_extents;
	int						mat_id;
	t_vec3					temp_color;
}							t_box;

typedef struct s_tri_shape
{
	t_transform				transform;
	t_vec3					v[3];
	int						mat_id;
	t_vec3					temp_color;
}							t_tri_shape;

typedef struct s_capsule
{
	t_transform				transform;
	t_vec3					axis;
	double					radius;
	double					half_height;
	int						mat_id;
	t_vec3					temp_color;
}							t_capsule;

typedef struct s_light
{
	t_light_type			type;
	t_transform				transform;
	double					cutoff;
	double					brightness;
	t_vec3					rgb;
}							t_light;

typedef struct s_camera
{
	t_transform				transform;
	double					fov;
}							t_camera;

typedef struct s_ambient
{
	double					brightness;
	t_vec3					rgb;
}							t_ambient;

/* t_parse_obj removed for Direct Injection */


typedef struct s_vertex
{
	t_vec3					pos;
	t_vec3					normal;
	t_vec2					uv;
}							t_vertex;

typedef struct s_triangle
{
	int						indices[3];
}							t_triangle;

typedef struct s_bone_weight
{
	int						bone_ids[4];
	double					weights[4];
}							t_bone_weight;

typedef struct s_transform_q
{
	t_vec3					pos;
	t_vec3					rot;
	t_vec3					scale;
}							t_transform_q;

typedef struct s_bone
{
	char					*name;
	int						node_idx;
	int						parent;
	t_mat4					local_transform;
	t_mat4					global_transform;
	t_mat4					bind_pose;
	t_mat4					inv_bind_pose;
	t_transform_q			trs;
}							t_bone;

typedef struct s_mesh
{
	char					*name;
	t_vec3					*vertices;
	t_vec3					*normals;
	t_vec2					*uvs;
	int						*indices;
	int						vertex_count;
	int						tri_count;
	t_transform				transform;
	int						mat_id;
	t_bone_weight			*skin_data;
	t_bone					*skeleton;
	int						bone_count;
	t_vec3					*base_vertices;
	t_vec3					*base_normals;
	int						node_idx;
	bool					has_scene_transform;
	int						group_id;
	int						anim_base;
	int						anim_clip_count;
	t_aabb					bbox;
}							t_mesh;

typedef struct s_mesh_group
{
	char					*name;
	char					*path;
	t_aabb					bbox;
	int						tri_start;
	int						tri_count;
	int						anim_base;
	int						anim_clip_count;
	t_vec3					pivot;
	t_transform				transform;
}							t_mesh_group;

typedef struct s_skinned_mesh
{
	t_mesh					base;
	t_bone					*skeleton;
	t_mat4					*bone_matrices;
	int						bone_count;
}							t_skinned_mesh;

typedef struct s_anim_sampler
{
	float					*inputs;
	float					*outputs;
	int						count;
	t_interpolation			method;
}							t_anim_sampler;

typedef struct s_anim_channel
{
	int						node_idx;
	t_anim_path				path;
	int						sampler_idx;
}							t_anim_channel;

typedef struct s_animation
{
	char					*name;
	t_anim_channel			*channels;
	int						channel_count;
	t_anim_sampler			*samplers;
	int						sampler_count;
	double					max_time;
}							t_animation;

typedef struct s_mesh_info
{
	char					*path;
	t_transform				transform;
	t_vec3					color;
	t_vec3					emission;
}							t_mesh_info;

typedef struct s_mesh_init
{
	int						v_count;
	int						i_count;
	bool					has_uvs;
	bool					has_normals;
}							t_mesh_init;


/* ------------------------------------------------------------------------- */
/*                             SCENE UTILS                                   */
/* ------------------------------------------------------------------------- */

void						update_object_material(void *obj_data, t_type type);
void						mesh_apply_transform(t_mesh *mesh,
								t_transform transform);
void						mesh_free(t_mesh *mesh);

/* AABB Core Management (Maths/Data level) */
t_aabb						aabb_create_empty(void);
t_aabb						aabb_union(const t_aabb *a, const t_aabb *b);
void						aabb_expand_point(t_aabb *a, t_vec3 p);
void						aabb_expand_eps(t_aabb *a, double eps);
double						aabb_surface_area(t_aabb a);
t_aabb						aabb_transform(t_aabb bbox, t_transform t);
bool						aabb_overlap(t_aabb a, t_aabb b);

/* Per-shape world-space AABB producers (Maths level) */
t_aabb						sphere_aabb(t_sphere *sp);
t_aabb						plane_aabb(t_plane *pl);
t_aabb						cylinder_aabb(t_cylinder *cy);
t_aabb						cone_aabb(t_cone *co);
t_aabb						tri_aabb(t_tri_shape *tr);
t_aabb						rect_aabb(t_rect *rc);
t_aabb						pyramid_aabb(t_pyramid *py);
t_aabb						box_aabb(t_box *bx);
t_aabb						capsule_aabb(t_capsule *cp);

/* RT Parsing Functions (Rule 1) - Deprecated for Direct Injection */


#endif

