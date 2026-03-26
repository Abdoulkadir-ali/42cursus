/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poc_objects.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:59:06 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 15:59:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

/* Dépendances externes */
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

/* Dépendances du projet */
# include "debug.h"
# include "defines.h"
# include "maths.h"
# include "profiler.h"
# include "surface.h"

/* ------------------------------------------------------------------------- */
/* CONSTANTES & MACROS                                                       */
/* ------------------------------------------------------------------------- */

# define GLB_MAGIC 0x46546C67
# define CHUNK_JSON 0x4E4F534A
# define CHUNK_BIN 0x004E4942
# define BVH_BINS 16
# define CACHE_CAP 64

/* ------------------------------------------------------------------------- */
/* ENUMÉRATIONS                                                              */
/* ------------------------------------------------------------------------- */

typedef enum e_interpolation
{
	INTERP_LINEAR,
	INTERP_STEP,
	INTERP_CUBIC
}					t_interpolation;

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
}					t_type;

typedef enum e_light_type
{
	LIGHT_POINT,
	LIGHT_SPOT,
	LIGHT_EMISSIVE
}					t_light_type;

typedef enum e_anim_path
{
	PATH_TRANSLATION,
	PATH_ROTATION,
	PATH_SCALE,
	PATH_WEIGHTS
}					t_anim_path;

/* ------------------------------------------------------------------------- */
/* STRUCTURES GÉOMÉTRIQUES (DÉCOUPLÉES DE LA PHYSIQUE)                       */
/* ------------------------------------------------------------------------- */

typedef struct s_emissive_ref
{
	t_type			type;
	int				index;
}					t_emissive_ref;

typedef struct s_sphere
{
	t_transform		transform;
	double			radius;
	double			radius_sq;
	int				mat_id;
	t_vec3			temp_color;
	bool			is_deformed;
	t_mat4			inv_transform;
}					t_sphere;

typedef struct s_plane
{
	t_transform		transform;
	int				mat_id;
	t_vec3			temp_color;
}					t_plane;

typedef struct s_cylinder
{
	t_transform		transform;
	double			radius;
	double			height;
	int				mat_id;
	t_vec3			temp_color;
}					t_cylinder;

typedef struct s_cone
{
	t_transform		transform;
	double			radius;
	double			height;
	int				mat_id;
	t_vec3			temp_color;
}					t_cone;

typedef struct s_tri_shape
{
	t_transform		transform;
	t_vec3			v;
	t_vec3			normal;
	int				mat_id;
	t_vec3			temp_color;
}					t_tri_shape;

typedef struct s_rect
{
	t_transform		transform;
	t_vec3			v;
	t_vec3			normal;
	int				mat_id;
	t_vec3			temp_color;
}					t_rect;

typedef struct s_pyramid
{
	t_transform		transform;
	t_vec3			up;
	double			base_size;
	double			height;
	int				mat_id;
	t_vec3			temp_color;
	t_vec3			c;
	t_vec3			apex;
}					t_pyramid;

typedef struct s_box
{
	t_transform		transform;
	t_vec3			half_extents;
	int				mat_id;
	t_vec3			temp_color;
}					t_box;

typedef struct s_capsule
{
	t_transform		transform;
	t_vec3			axis;
	double			radius;
	double			half_height;
	int				mat_id;
	t_vec3			temp_color;
}					t_capsule;

typedef struct s_light
{
	t_light_type	type;
	t_transform		transform;
	double			cutoff;
	double			brightness;
	t_vec3			rgb;
}					t_light;

typedef struct s_camera
{
	t_transform		transform;
	double			fov;
}					t_camera;

typedef struct s_ambient
{
	double			brightness;
	t_vec3			rgb;
}					t_ambient;

/* ------------------------------------------------------------------------- */
/* MESH, SKELETON & ANIMATION                                                */
/* ------------------------------------------------------------------------- */

typedef struct s_vertex
{
	t_vec3			pos;
	t_vec3			normal;
	t_vec2			uv;
}					t_vertex;

typedef struct s_triangle
{
	int				indices;
}					t_triangle;

typedef struct s_tri_precomp
{
	t_vec3			v0;
	t_vec3			e1;
	t_vec3			e2;
}					t_tri_precomp;

typedef struct s_mbvh_node
{
	t_aabb			bbox;
	int				left_or_first;
	int				count;
	int				axis;
}					t_mbvh_node;

typedef struct s_bone_weight
{
	int				bone_ids;
	double			weights;
}					t_bone_weight;

typedef struct s_transform_q
{
	t_vec3			pos;
	t_vec3			rot;
	t_vec3			scale;
}					t_transform_q;

typedef struct s_bone
{
	char			*name;
	int				node_idx;
	int				parent;
	t_mat4			local_transform;
	t_mat4			global_transform;
	t_mat4			bind_pose;
	t_mat4			inv_bind_pose;
	t_transform_q	trs;
	bool			has_collider;
	int				sub_idx;
	double			radius;
	double			height;
	t_vec3			local_offset;
}					t_bone;

typedef struct s_mesh
{
	char			*name;
	t_vec3			*vertices;
	t_vec3			*normals;
	t_vec2			*uvs;
	int				*indices;
	int				vertex_count;
	int				tri_count;
	t_aabb			bbox;
	t_transform		transform;
	t_mbvh_node		*bvh_nodes;
	int				*bvh_indices;
	t_tri_precomp	*tri_cache;
	int				mat_id;
	t_bone_weight	*skin_data;
	t_bone			*skeleton;
	int				bone_count;
	t_mat4			*bone_matrices;
	t_vec3			*base_vertices;
	t_vec3			*base_normals;
	int				node_idx;
	t_mat4			scene_mat;
	t_mat4			scene_rot_mat;
	bool			has_scene_transform;
	int				current_anim;
	int				anim_base;
	int				anim_clip_count;
	double			anim_time;
	int				group_id;
	t_vec3			*edit_snap_verts;
	t_vec3			*edit_snap_norms;
	t_vec3			edit_snap_pivot;
}					t_mesh;

typedef struct s_anim_sampler
{
	float			*inputs;
	float			*outputs;
	int				count;
	t_interpolation	method;
}					t_anim_sampler;

typedef struct s_anim_channel
{
	int				node_idx;
	t_anim_path		path;
	int				sampler_idx;
}					t_anim_channel;

typedef struct s_animation
{
	char			*name;
	t_anim_channel	*channels;
	int				channel_count;
	t_anim_sampler	*samplers;
	int				sampler_count;
	double			max_time;
	double			current_time;
}					t_animation;

typedef struct s_mesh_group
{
	char			*name;
	char			*path;
	int				start;
	int				sub_count;
	t_transform		transform;
	t_vec3			pivot;
	int				anim_base;
	int				anim_clip_count;
}					t_mesh_group;

/* ------------------------------------------------------------------------- */
/* L'OBJET GÉNÉRIQUE (ECS-STYLE)                                             */
/* ------------------------------------------------------------------------- */

typedef struct s_object
{
	t_type			type;
	void *data;             /* Pointeur vers la primitive réelle */
	t_transform *transform; /* Pointeur direct vers le transform de data */
	int id;                 /* ID unique pour picking/editor */
	bool			is_visible;
}					t_object;

/* ------------------------------------------------------------------------- */
/* STRUCTURES DE PARSING & CONTEXTES                                         */
/* ------------------------------------------------------------------------- */

typedef struct s_mesh_init
{
	int				v_count;
	int				i_count;
	bool			has_uvs;
	bool			has_normals;
}					t_mesh_init;

typedef struct s_obj_ctx
{
	t_vec3			*temp_v;
	size_t			v_count;
	size_t			v_cap;
	t_vec2			*temp_vt;
	size_t			vt_count;
	size_t			vt_cap;
	t_vec3			*temp_vn;
	size_t			vn_count;
	size_t			vn_cap;
	t_vec3			*out_v;
	t_vec3			*out_vn;
	t_vec2			*out_vt;
	int				*out_i;
	size_t			out_v_count;
	size_t			out_v_cap;
	size_t			out_i_count;
	size_t			out_i_cap;
	int				current_mat_id;
	int				first_mtl_id;
	t_aabb			bbox;
}					t_obj_ctx;

typedef struct s_obj_face
{
	int				vi;
	int				vti;
	int				vni;
	int				count;
}					t_obj_face;

typedef struct s_parse_obj
{
	t_type			type;
	union			u_data
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_cone		cone;
		t_mesh		mesh;
		t_light		light;
		t_camera	camera;
		t_ambient	ambient;
		t_tri_shape	tri_shape;
		t_rect		rect;
		t_pyramid	pyramid;
		t_box		box;
		t_capsule	capsule;
	} data;
}					t_parse_obj;

/* ------------------------------------------------------------------------- */
/* PROTOTYPES                                                                */
/* ------------------------------------------------------------------------- */

/* Mesh Management */
bool				mesh_init(t_mesh *mesh, t_mesh_init init);
void				mesh_free(t_mesh *mesh);
void				mesh_build_bvh(t_mesh *mesh);
void				mesh_build_tri_cache(t_mesh *mesh);
void				update_object_material(void *obj_data, t_type type);
void				mesh_apply_transform(t_mesh *mesh, t_transform transform);

/* Parsing & File Loading */
t_parse_obj			dispatch_scan(struct s_parser *p, char *id);
t_parse_obj			parse_mesh_entry(struct s_parser *p, t_type type);
bool				process_object(struct s_scene *scene, t_parse_obj obj);
bool				handle_mesh_injection(t_parse_obj *obj, const char *ext,
						struct s_scene *scene);
bool				mesh_cache_has(const char *path);
bool				mesh_cache_save(const char *path, struct s_scene *scene,
						int start_mesh);
bool				mesh_cache_restore(const char *path, struct s_scene *scene);

/* Intersection (Géométrie Pure pour Raytracing) */
bool				intersect_triangle(const t_ray *ray, t_vec3 v, double *t,
						t_vec2 *uv);
bool				intersect_mesh(const t_ray *ray, t_mesh *mesh, t_hit *hit);
bool				mesh_occluded(const t_ray *ray, t_mesh *mesh, double dist);

/* Animation System */
void				glb_update_mesh_anim(t_mesh *mesh, struct s_scene *scene,
						double dt);

/* Helpers GJK Support (Utilisés par le moteur physique via pointeurs de fonction) */
t_vec3				support_sphere(const void *data, t_vec3 dir);
t_vec3				support_box(const void *data, t_vec3 dir);
t_vec3				support_mesh(const void *data, t_vec3 dir);
t_vec3				support_cylinder(const void *data, t_vec3 dir);
t_vec3				support_capsule(const void *data, t_vec3 dir);
t_vec3				support_rect(const void *data, t_vec3 dir);
t_vec3				support_tri(const void *data, t_vec3 dir);
t_vec3				support_pyramid(const void *data, t_vec3 dir);

#endif