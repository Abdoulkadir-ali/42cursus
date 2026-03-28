/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 04:24:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 09:06:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLB_LOADER_H
# define GLB_LOADER_H

# include "parser.h"
# include "mesh.h"
# include "material.h"

/* --- GLB Binary Format Constants --- */
# define GLB_MAGIC   0x46546C67
# define CHUNK_JSON  0x4E4F534A
# define CHUNK_BIN   0x004E4942

/* --- GLB Binary Format Headers --- */
typedef struct s_glb_header
{
	uint32_t	magic;
	uint32_t	version;
	uint32_t	length;
}				t_glb_header;

typedef struct s_glb_chunk_header
{
	uint32_t	length;
	uint32_t	type;
}				t_glb_chunk_header;

/* --- GLB JSON Structure Accessors --- */
typedef struct s_glb_accessor
{
	int		buffer_view;
	int		byte_offset;
	int		component_type;
	int		count;
	char	type[16];
	int		type_size;
	int		stride;
}				t_glb_accessor;

typedef struct s_glb_buffer_view
{
	int		buffer;
	int		byte_offset;
	int		byte_length;
	int		byte_stride;
}				t_glb_buffer_view;

/* --- GLB LOADER STRUCTURE --- */
typedef struct s_glb
{
	t_mesh			*meshes;
	int				*mesh_mats;
	int				mesh_count;
	t_animation		*animations;
	int				anim_count;
	t_material		*materials;
	int				mat_count;
	const char		*path;
	t_json_value	*json;
	char			*bin;
}					t_glb;

/* --- PUBLIC API --- */
bool				glb_load(t_scene *scene, const char *path);
bool				parse_glb_entry(t_scene *scene, t_parser *p);
bool				parse_glb(t_scene *scene, t_parser *p);
t_glb				*glb_load_asset(const char *path);

/* --- MATERIAL PARSING & INJECTION --- */
/* GLB loader parses embedded materials as t_material structs.
 * Materials are injected via scene_add_material() from material/injection.c
 */

/* --- INTERNALS: IO & JSON --- */
bool				glb_parse_to_asset(t_glb *g, int fd, const char *path);
void				glb_clear_asset(t_glb *g);
bool				glb_read_buffers(int fd, char *buf[2]);
void				glb_parse_accessor(t_json_value *json, int index,
						t_glb_accessor *acc);
void				glb_parse_buffer_view(t_json_value *json, int index,
						t_glb_buffer_view *bv);

/* --- INTERNALS: Mesh extraction --- */
bool				glb_load_primitive(t_mesh *mesh, t_json_value *json,
						char *bin, int mesh_idx, int prim_idx, int mat_id);
void				glb_extract_data(char *bin, t_glb_accessor *acc,
						t_glb_buffer_view *bv, void *entry);
void				glb_handle_indices_short(t_mesh *mesh,
						t_json_value *json, char *bin, int idx);
void				glb_fill_attributes(t_mesh *mesh, t_json_value *json,
						char *bin, int ids[6]);
void				glb_compute_mesh_bbox(t_mesh *mesh);

/* --- INTERNALS: Animation & Skeleton --- */
t_animation			*glb_extract_animations(t_json_value *json, char *bin,
						int *out_count);
void				glb_parse_sampler(t_json_value *json, char *bin,
						t_anim_sampler *s, t_json_value *sj);
void				glb_load_skeleton_impl(t_mesh *mesh, t_json_value *json,
						char *bin, int idx);

/* --- INTERNALS: Material extraction & injection --- */
t_material			*glb_extract_materials(t_json_value *json, char *bin,
						int *count);
int					*glb_inject_materials(t_scene *scene, t_glb *glb,
						int *count);
void				glb_inject_mesh_atomic(t_scene *s, t_glb *g,
						t_json_value *p, int *mmap);
void				scene_add_glb(t_scene *scene, t_glb *glb);
bool				glb_parse_io(t_scene *scene, int fd, const char *path);
void				init_mesh(t_mesh *mesh, const char *path);
void				mesh_free(t_mesh *mesh);

/* --- INJECTION (Scene add functions) --- */
bool				scene_add_mesh(t_scene *scene, t_mesh mesh);

#endif
