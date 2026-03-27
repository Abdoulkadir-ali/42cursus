/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:11:11 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 18:27:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOADER_H
# define LOADER_H

# include "parser.h"
# include "scene.h"
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <fcntl.h>
# include <unistd.h>

/* --- GLB CONSTANTS --- */
# define GLB_MAGIC 0x46546C67
# define CHUNK_JSON 0x4E4F534A
# define CHUNK_BIN 0x004E4942
# define GLB_FLOAT 5126
# define GLB_SHORT 5123
# define GLB_BYTE 5121
# define GLB_USHORT 5123
# define GLB_UBYTE 5121

/* --- GLB DATA TYPES --- */

typedef struct s_glb_header
{
	uint32_t				magic;
	uint32_t				version;
	uint32_t				length;
}							t_glb_header;

typedef struct s_glb_chunk_header
{
	uint32_t				length;
	uint32_t				type;
}							t_glb_chunk_header;

typedef struct s_glb_accessor
{
	int						buffer_view;
	int						byte_offset;
	int						component_type;
	int						count;
	char					type[16];
	int						type_size;
	int						stride;
}							t_glb_accessor;

typedef struct s_glb_buffer_view
{
	int						buffer;
	int						byte_offset;
	int						byte_length;
	int						byte_stride;
}							t_glb_buffer_view;

typedef struct s_glb
{
	t_mesh					*meshes;
	int						*mesh_mats;
	int						mesh_count;
	t_animation				*animations;
	int						anim_count;
	t_material				*materials;
	int						mat_count;
	const char				*path;
	t_json_value			*json;
	char					*bin_ref;
}							t_glb;


/* --- FBX DATA TYPES --- */

typedef struct s_fbx_bin_node
{
	uint64_t				end_offset;
	uint64_t				num_properties;
	uint64_t				property_list_len;
	uint8_t					name_len;
	char					name[256];
}							t_fbx_bin_node;

typedef struct s_fbx_array
{
	char					type;
	uint32_t				actual_sz;
	uint32_t				arr_len;
	uint32_t				encoding;
	uint32_t				comp_len;
}							t_fbx_array;

typedef struct s_fbx
{
	t_mesh					*meshes;
	int						mesh_count;
	t_animation				*animations;
	int						anim_count;
	t_material				*materials;
	int						mat_count;
	const char				*path;
	uint32_t				version;
	int						fd;
	bool					is_64;
	double					*v;
	uint32_t				vc;
	int						*ri;
	uint32_t				rc;
	double					*vn;
	uint32_t				nc;
	double					*vu;
	uint32_t				uc;
}							t_fbx;

typedef struct s_fdf
{
	int						width;
	int						height;
	double					*grid;
	t_mesh					mesh;
	const char				*path;
}							t_fdf;

/* --- LOADER PUBLIC API --- */
bool		glb_load(t_scene *scene, const char *path);
t_glb		*glb_load_asset(const char *path);
bool		parse_glb(t_scene *scene, t_parser *p);
bool		fbx_load(t_scene *scene, const char *path);
bool		parse_fbx(t_scene *scene, t_parser *p);
bool		fdf_load(t_scene *scene, const char *path);
bool		parse_fdf(t_scene *scene, t_parser *p);
bool		rt_load(t_scene *scene, const char *path);

/* --- RT PARSING --- */
bool		dispatch_scan(t_scene *scene, t_parser *p, char *id);
bool		dispatch_meshes(t_scene *scene, t_parser *p, char *id);
bool		parse_glb_entry(t_scene *scene, t_parser *p);
bool		parse_fbx_entry(t_scene *scene, t_parser *p);
bool		parse_fdf_entry(t_scene *scene, t_parser *p);
bool		parse_obj_entry(t_scene *scene, t_parser *p);
bool		parse_mesh_entry(t_scene *scene, t_parser *p, int type);

/* --- FDF INTERNALS --- */
bool		fdf_parse_dims(t_fdf *f, t_parser *p);
bool		fdf_fill_grid(t_fdf *f, t_parser *p);
bool		fdf_parse_grid_single_pass(t_fdf *f, t_parser *p);
bool		fdf_triangulate(t_fdf *f);
void		fdf_compute_normals(t_fdf *f);
void		fdf_gen_uvs(t_fdf *f);

/* --- GLB INTERNALS --- */
bool		glb_parse_to_asset(t_glb *glb, int fd, const char *path);
void		glb_inject_mesh_atomic(t_scene *s, t_glb *g, t_json_value *p, 
			int *mmap);
bool		glb_read_buffers(int fd, char *buf[2]);
bool		glb_load_primitive(t_mesh *mesh, t_json_value *json, char *bin, 
			int mesh_idx, int prim_idx, int mat_id);
void		glb_extract_data(char *bin, t_glb_accessor *acc, t_glb_buffer_view *bv, 
			void *entry);
void		glb_handle_indices_short(t_mesh *mesh, t_json_value *json, 
			char *bin, int idx);
t_material	*glb_extract_materials(t_json_value *json, char *bin, int *count);
t_animation	*glb_extract_animations(t_json_value *json, char *bin, int *out);
void		glb_parse_sampler(t_json_value *j, char *b, t_anim_sampler *s, 
			t_json_value *sj);
void		glb_compute_mesh_bbox(t_mesh *mesh);
void		glb_load_skeleton_impl(t_mesh *mesh, t_json_value *json, 
			char *bin, int extra);
void        glb_fill_attributes(t_mesh *mesh, t_json_value *json, char *bin, 
			int ids[6]);
void        glb_parse_accessor(t_json_value *json, int index, t_glb_accessor *acc);
void        glb_parse_buffer_view(t_json_value *json, int index, t_glb_buffer_view *bv);





/* --- FBX INTERNALS --- */
t_vec3		*fbx_repack_vec3(double *raw, uint32_t v_count);
bool		fbx_is_binary(int fd);
bool		fbx_parse_binary(t_fbx *fbx);
bool		fbx_parse_ascii(t_fbx *fbx);
void		fbx_clear_asset(t_fbx *fbx);
void		fbx_parse_nodes(t_fbx *f, uint64_t end);
void		fbx_read_header(int fd, t_fbx_bin_node *n, bool is_64);
void		fbx_skip_props(int fd, uint64_t num);
bool		fbx_build_mesh(t_fbx *f);
void		*read_fbx_array(int fd, uint32_t *count, size_t elem_sz);
void		*fbx_convert_array(t_fbx_array *a, void *uncomp, size_t elem_sz, 
			uint32_t *count);
char		*fbx_read_file(const char *path, size_t *out_size);
char		*fbx_find_node(char *start, char *end, const char *key);
void		*fbx_parse_array_ascii(char **p, uint32_t *count, size_t elem_sz);

#endif
