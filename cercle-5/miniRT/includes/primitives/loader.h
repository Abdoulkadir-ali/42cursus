/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Created: 2026/03/27 12:00:00 by copilot           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIMITIVES_LOADER_H
#define PRIMITIVES_LOADER_H

#include "objects.h"
#include "parser.h"

typedef struct s_scene t_scene;

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

/* Asset Loading Structures */

typedef struct s_glb_header
{
	uint32_t				magic;
	uint32_t				version;
	uint32_t				length;
}							t_glb_header;

typedef struct s_chunk_header
{
	uint32_t				length;
	uint32_t				type;
}							t_chunk_header;

typedef struct s_accessor
{
	int						buffer_view;
	int						byte_offset;
	int						component_type;
	int						count;
	char					type[16];
}							t_accessor;

typedef struct s_buffer_view
{
	int						buffer;
	int						byte_offset;
	int						byte_length;
	int						byte_stride;
}							t_buffer_view;

typedef struct s_fbx_bin_node
{
	uint64_t				end_offset;
	uint64_t				num_properties;
	uint64_t				property_list_len;
	uint8_t					name_len;
	char					name[1024];
}							t_fbx_bin_node;

typedef struct s_fbx_data
{
	t_vec3					*v;
	uint32_t				vc;
	int						*ri;
	uint32_t				rc;
	t_vec3					*vn;
	uint32_t				nc;
	t_vec2					*vu;
	uint32_t				uc;
}							t_fbx_data;

typedef struct s_fbx_flat_args
{
	int						*raw;
	int						raw_c;
	t_vec3					*n;
	int						nc;
	t_vec2					*u;
	int						uc;
	int						vc;
}							t_fbx_flat_args;

typedef struct s_fbx_build
{
	t_mesh					*m;
	int						*raw;
	int						raw_c;
	t_vec3					*n;
	int						nc;
	t_vec2					*u;
	int						uc;
	int						vc;
	int						tc;
	t_vec3					*nv;
	t_vec3					*nn;
	t_vec2					*nu;
	int						*ni;
	int						*v;
	int						vp;
	int						ps;
	int						use_v_n;
	int						use_v_u;
}							t_fbx_build;

typedef struct s_fbx_array_req
{
	const char				*label;
	void					**dst;
	uint32_t				*count;
	size_t					elem_sz;
	uint32_t				div;
}							t_fbx_array_req;

typedef struct s_fbx_array
{
	uint32_t				arr_len;
	uint32_t				encoding;
	uint32_t				comp_len;
	size_t					actual_sz;
	char					type;
}							t_fbx_array;

typedef struct s_fbx_buf
{
	char					*buf;
	size_t					cap;
	size_t					len;
}							t_fbx_buf;

typedef struct s_obj_ctx
{
	t_vec3					*temp_v;
	size_t					v_count;
	size_t					v_cap;
	t_vec2					*temp_vt;
	size_t					vt_count;
	size_t					vt_cap;
	t_vec3					*temp_vn;
	size_t					vn_count;
	size_t					vn_cap;
	t_vec3					*out_v;
	t_vec3					*out_vn;
	t_vec2					*out_vt;
	int						*out_i;
	size_t					out_v_count;
	size_t					out_v_cap;
	size_t					out_i_count;
	size_t					out_i_cap;
	int						current_mat_id;
	int						first_mtl_id;
	t_aabb					bbox;
}							t_obj_ctx;

typedef struct s_fdf_row_ctx
{
	t_mesh					*mesh;
	int						dims[2];
	int						row;
}							t_fdf_row_ctx;

typedef struct s_fbx_parse_ctx
{
	int						fd;
	bool					is_64;
	t_fbx_data				*d;
}							t_fbx_parse_ctx;

typedef struct s_fbx_ascii_ctx
{
	int						fd;
	t_vec3					*rn;
	t_vec2					*ru;
	int						*ri;
	int						rc;
	int						vc;
	int						nc;
	int						uc;
	char					*buf;
	char					*p;
	char					*end;
	size_t					buf_size;
	int						mat_id;
	const char				*path;
}							t_fbx_ascii_ctx;

typedef struct s_extract_ctx
{
	char					*bin;
	t_accessor				*acc;
	t_buffer_view			*bv;
	void					*entry;
	int						type_size;
	int						count;
	int						stride;
}							t_extract_ctx;

typedef struct s_obj_face
{
	int						vi[32];
	int						vti[32];
	int						vni[32];
	int						count;
}							t_obj_face;


/* Loader public API */
bool		parse_rt_fd(int fd, t_scene *scene);
t_scene		*parse_file(const char *path, void *mlx);
bool		scene_parse_rt(t_scene *scene, const char *path);
bool		rt_parse_loop(t_scene *scene, struct s_parser *p);
bool		rt_parse_token(struct s_parser *p, char *buf, size_t max_len);
void		rt_parse_scale_raw(struct s_parser *p, t_vec3 *scale);

/* Static Mesh/Model injection API (Direct to Scene) */
bool		load_mesh_file(t_scene *scene, const char *path);
bool		load_injected_mesh(t_scene *scene, const char *path,
							 t_transform transform, t_vec3 color, t_vec3 emission);

/* Loader Implementations */
bool		fbx_load(t_scene *scene, const char *path);
bool		obj_load(t_scene *scene, const char *path);
bool		fdf_load(t_scene *scene, const char *path);
bool		glb_load(t_scene *scene, const char *path);

/* FBX Internals */
bool		fbx_load_binary(t_scene *scene, const char *path);
bool		fbx_load_ascii(t_scene *scene, const char *path);
void		*fbx_convert_array(t_fbx_array *a, void *uncomp, size_t elem_sz, uint32_t *count);

/* OBJ Internals */
bool		obj_read_id(t_parser *p, char *id, size_t max_len);
void		obj_parse_v(t_obj_ctx *ctx, t_parser *p);
void		obj_parse_vt(t_obj_ctx *ctx, t_parser *p);
void		obj_parse_vn(t_obj_ctx *ctx, t_parser *p);
void		obj_parse_f(t_obj_ctx *ctx, t_parser *p);
void		obj_parse_mtllib_to_scene(t_obj_ctx *ctx, t_parser *p, t_scene *scene, const char *path);
void		obj_parse_usemtl_to_scene(t_obj_ctx *ctx, t_parser *p, t_scene *scene);
void		obj_skip_line(t_parser *p);
bool		obj_finalize_mesh_to_scene(t_obj_ctx *ctx, t_scene *scene, const char *path);
bool		mtl_load_to_scene(const char *path, t_scene *scene);

/* GLB Internals */
void		glb_extract_data(t_extract_ctx ctx);

#endif
