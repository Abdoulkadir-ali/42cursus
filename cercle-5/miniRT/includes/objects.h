/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 15:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

/* 1. EXTERNAL DEPENDENCIES */
# include "libft.h"
# include "material.h"
# include "maths.h"
# include "types.h"
# include "parser.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* 2. MODULE TYPES & ENUMS */

#define GLB_MAGIC 0x46546C67
#define CHUNK_JSON 0x4E4F534A
#define CHUNK_BIN 0x004E4942
#define BVH_BINS 16

/* ------------------------------------------------------------------------- */
/*                             LEAF STRUCTURES                               */
/* ------------------------------------------------------------------------- */


struct					s_sphere
{
	t_transform			transform;
	float				radius_sq;
	int					mat_id;
	t_vec3				temp_color;
};

struct					s_plane
{
	t_transform			transform;
	int					mat_id;
	t_vec3				temp_color;
};

struct					s_cylinder
{
	t_transform			transform;
	int					mat_id;
	t_vec3				temp_color;
};

struct					s_cone
{
	t_transform			transform;
	int					mat_id;
	t_vec3				temp_color;
};

struct					s_light
{
	t_light_type		type;
	t_transform			transform;
	double				cutoff;
	double				brightness;
	t_vec3				rgb;
};

struct					s_camera
{
	t_transform			transform;
	double				fov;
};

struct					s_ambient
{
	double				brightness;
	t_vec3				rgb;
};

struct					s_vertex
{
	t_vec3				pos;
	t_vec3				normal;
	t_vec2				uv;
};

struct					s_triangle
{
	int					indices[3];
};

struct					s_mesh
{
	char				*name;
	t_vec3				*vertices;
	t_vec3				*normals;
	t_vec2				*uvs;
	int					*indices;
	int					vertex_count;
	int					tri_count;
	t_aabb				bbox;
	t_transform			transform;
	t_bvh				*internal_bvh;
	int					mat_id;
};

void					mesh_apply_transform(t_mesh *mesh, t_transform transform);

struct					s_bone_weight
{
	int					bone_ids[4];
	double				weights[4];
};

struct					s_bone
{
	char				*name;
	int				parent;
	t_mat4				local_transform;
	t_mat4				bind_pose;
	t_mat4				inv_bind_pose;
};

typedef struct s_glb_header
{
	uint32_t	magic;
	uint32_t	version;
	uint32_t	length;
}				t_glb_header;

typedef struct s_chunk_header
{
	uint32_t	length;
	uint32_t	type;
}				t_chunk_header;

typedef struct s_accessor
{
	int			buffer_view;
	int			byte_offset;
	int			component_type;
	int			count;
	char		type[16];
}				t_accessor;

typedef struct s_buffer_view
{
	int			buffer;
	int			byte_offset;
	int			byte_length;
	int			byte_stride;
}				t_buffer_view;

typedef struct s_fbx_bin_node
{
	uint64_t	end_offset;
	uint64_t	num_properties;
	uint64_t	property_list_len;
	uint8_t		name_len;
	char		name[256];
}				t_fbx_bin_node;

struct					s_skinned_mesh
{
	t_mesh base;           
		/* INHERITANCE: Re-use all mesh intersection code! */
	t_vec3 *base_vertices;  /* Original un-posed vertices */
	t_bone *skeleton;       /* The hierarchy of bones */
	t_mat4 *bone_matrices; 
		/* The current pose transformations (Global Space) */
	t_bone_weight *weights; /* Per-vertex weights */
	int					bone_count;
	int					vertex_count;
};

/* Parsing and Build Types */

struct					s_mesh_info
{
	char				*path;
	t_transform			transform;
	t_vec3				color;
};

struct					s_heightmap
{
	double				**map;
	int					width;
	int					height;
	t_vec3				rgb;
};

struct					s_mesh_build_item
{
	int index; // Triangle index
	t_aabb				bbox;
	t_vec3				centroid;
};

struct					s_parse_obj
{
	t_type				type;
	union				u_data
	{
		t_sphere		sphere;
		t_plane			plane;
		t_cylinder		cylinder;
		t_cone			cone;
		t_mesh			mesh;
		t_light			light;
		t_camera		camera;
		t_ambient		ambient;
		t_skinned_mesh	animated;
		t_mesh_info		mesh_info;
	} data;
};

typedef struct s_obj_ctx
{
	t_vec3		*temp_v;
	size_t		v_count;
	size_t		v_cap;
	t_vec2		*temp_vt;
	size_t		vt_count;
	size_t		vt_cap;
	t_vec3		*temp_vn;
	size_t		vn_count;
	size_t		vn_cap;

	t_vec3		*out_v;
	t_vec3		*out_vn;
	t_vec2		*out_vt;
	int			*out_i;
	size_t		out_v_count;
	size_t		out_v_cap;
	size_t		out_i_count;
	size_t		out_i_cap;
	int			current_mat_id; /* Added for MTL support */

	t_aabb		bbox;
}				t_obj_ctx;

typedef struct s_extract_ctx
{
	char			*bin;
	t_accessor		*acc;
	t_buffer_view	*bv;
	void			*entry;
	int				stride;
	int				count;
	int				type_size;
}					t_extract_ctx;

/* 3. FUNCTION PROTOTYPES */

/* Parsing Helpers (srcs/objects/rt/parsing/utils.c) */
void					skip_whitespace(char **line);
bool					parse_float_fast(char **line, double *out);
bool					parse_vec3_fast(char **line, t_vec3 *out);
bool					parse_color_fast(char **line, t_vec3 *out);
char					*get_next_token(char **line);
bool					validate_file(const char *path);

/* .rt Parser (srcs/objects/rt/parsing/) */
t_parse_obj				parse_ambient(t_parser *p);
t_parse_obj				parse_camera(t_parser *p);
t_parse_obj				parse_light(t_parser *p);
t_parse_obj				parse_spot_light(t_parser *p);
t_parse_obj				parse_sphere(t_parser *p);
t_parse_obj				parse_plane(t_parser *p);
t_parse_obj				parse_cylinder(t_parser *p);
t_parse_obj				parse_cone(t_parser *p);
t_parse_obj				parse_mesh_entry(t_parser *p, t_type type);


void					update_object_material(void *obj_data, t_type type);

/* File Specific Parsers */
bool					parse_rt(const char *path, t_scene *scene);
bool					parse_obj(const char *path, t_scene *scene);
bool					parse_mtl(t_scene *scene, const char *path);
bool					parse_fdf(const char *path, t_scene *scene);
bool					parse_fbx(const char *path, t_scene *scene);
bool					parse_glb(const char *path, t_scene *scene);
bool					parse_fbx_ascii(const char *path, t_scene *scene);
bool					parse_fbx_binary(const char *path, t_scene *scene);
void					fbx_build_flat(t_mesh *m, int *raw, int raw_c, \
							t_vec3 *n, int nc, t_vec2 *u, int uc, int vc);

/* Build logic */
void					mesh_build_bvh(t_mesh *mesh);
bool					intersect_triangle(const t_ray *ray, t_vec3 v[3], double *t, t_vec2 *uv);
bool					intersect_mesh(const t_ray *ray, t_mesh *mesh, t_hit *hit);
bool					mesh_occluded(const t_ray *ray, t_mesh *mesh, double dist);

/* 4. IMPLEMENTATION IMPORTS */
# include "bvh.h"
# include "raytracing.h"

#endif
