/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:23:29 by abdoali          ###   ########.fr       */
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
# include "helpers/maths.h"
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

typedef struct s_sphere
{
	t_transform				transform;
	double					radius;
	double					radius_sq;
	int						mat_id;
	t_vec3					temp_color;

	/* Cached inverse transform for deformed spheres (physics) */
	t_mat4				inv_transform;
	bool				is_deformed;
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
	t_vec3					normal;
	int						mat_id;
	t_vec3					temp_color;
}							t_rect;

typedef struct s_pyramid
{
	t_transform				transform;
	t_vec3				v[5];
	t_vec3				up;
	double				base_size;
	double				height;
	int					mat_id;
	t_vec3				temp_color;

	/* Cached vertices for fast intersection */
	t_vec3				c[4];
	t_vec3				apex;
}							t_pyramid;

typedef struct s_box
{
	t_transform				transform;
	t_vec3					min;
	t_vec3					max;
	t_vec3					half_extents;
	int						mat_id;
	t_vec3					temp_color;
}							t_box;

typedef struct s_tri_shape
{
	t_transform				transform;
	t_vec3					v[3];
	t_vec3					normal;
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

typedef struct s_parse_obj
{
	t_type					type;
	union					u_data
	{
		t_sphere			sphere;
		t_plane				plane;
		t_cylinder			cylinder;
		t_cone				cone;
		t_light				light;
		t_camera			camera;
		t_ambient			ambient;
		t_tri_shape			tri_shape;
		t_rect				rect;
		t_pyramid			pyramid;
		t_box				box;
		t_capsule			capsule;
	} data;
}							t_parse_obj;

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

typedef struct s_bin
{
	t_aabb					bounds;
	int						count;
}							t_bin;

typedef struct s_tri_precomp
{
	t_vec3					v0;
	t_vec3					e1;
	t_vec3					e2;
}							t_tri_precomp;

typedef struct s_mbvh_node
{
	t_aabb					bbox;
	int						left_or_first;
	int						count;
	int						axis;
}							t_mbvh_node;

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
	bool					has_collider;
	int						sub_idx;
	double					radius;
	double					height;
	t_vec3					local_offset;
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
	t_aabb					bbox;
	t_transform				transform;
	t_mbvh_node				*bvh_nodes;
	int						*bvh_indices;
	t_tri_precomp			*tri_cache;
	int						mat_id;
	t_bone_weight			*skin_data;
	t_bone					*skeleton;
	int						bone_count;
	t_mat4					*bone_matrices;
	t_vec3					*base_vertices;
	t_vec3					*base_normals;
	int						node_idx;
	t_mat4					scene_mat;
	t_mat4					scene_rot_mat;
	bool					has_scene_transform;
	int						current_anim;
	int						anim_base;
	int						anim_clip_count;
	double					anim_time;
	int						group_id;
	t_vec3					*edit_snap_verts;
	t_vec3					*edit_snap_norms;
	t_vec3					edit_snap_pivot;
}							t_mesh;

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
	double					current_time;
}							t_animation;

typedef struct s_mesh_init
{
	int						v_count;
	int						i_count;
	bool					has_uvs;
	bool					has_normals;
}							t_mesh_init;

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

typedef struct s_skinned_mesh
{
	t_mesh					base;
	t_vec3					*base_vertices;
	t_bone					*skeleton;
	t_mat4					*bone_matrices;
	t_bone_weight			*weights;
	int						bone_count;
	int						vertex_count;
}							t_skinned_mesh;

typedef struct s_mesh_group
{
	char					*name;
	char					*path;
	int						start;
	int						sub_count;
	t_transform				transform;
	t_vec3					pivot;
	int						anim_base;
	int						anim_clip_count;
}							t_mesh_group;

typedef struct s_mesh_info
{
	char					*path;
	t_transform				transform;
	t_vec3					color;
	t_vec3					emission;
}							t_mesh_info;

typedef struct s_raw_material
{
	char					name[64];
	t_vec3					color;
	double					specular;
	double					shininess;
	double					transparency;
	double					refract_index;
	double					metallic;
	double					roughness;
	t_vec3					emission;
	char					albedo_map_path[256];
	unsigned char			*tex_data;
	size_t					tex_len;
	bool					has_tex;
}							t_raw_material;

typedef struct s_raw_model
{
	t_mesh					*meshes;
	int						mesh_count;
	t_animation				*anims;
	int						anim_count;
	t_raw_material			*materials;
	int						mat_count;
	int						*mesh_mat_indices;
}							t_raw_model;


typedef struct s_heightmap
{
	double					**map;
	int						width;
	int						height;
	t_vec3					rgb;
}							t_heightmap;

typedef struct s_obj_face
{
	int						vi[32];
	int						vti[32];
	int						vni[32];
	int						count;
}							t_obj_face;

typedef struct s_fdf_dim
{
	int						w;
	int						h;
}							t_fdf_dim;



typedef struct s_occ_child
{
	int						left_idx;
	int						right_idx;
	double					tl_min;
	double					tl_max;
	double					tr_min;
	double					tr_max;
	bool					hit_l;
	bool					hit_r;
}							t_occ_child;

typedef struct s_bvh_ref
{
	uint8_t					type;
	int						index;
}							t_bvh_ref;

typedef struct s_bvh_node
{
	t_aabb					bbox;
	int						left_or_first;
	int						count;
}							t_bvh_node;

typedef struct s_bvh
{
	t_scene					*scene;
	t_bvh_node				*nodes;
	t_bvh_ref				*refs;
	int						num_nodes;
	int						num_refs;
}							t_bvh;


typedef struct s_bvh_tmp_node
{
	t_aabb					bbox;
	struct s_bvh_tmp_node	*left;
	struct s_bvh_tmp_node	*right;
	t_bvh_ref				*refs;
	size_t					num_refs;
}							t_bvh_tmp_node;

typedef struct s_bvh_split
{
	int						axis;
	double					pos;
}							t_bvh_split;

typedef struct s_bvh_sah
{
	t_aabb					centroid_bounds;
	t_aabb					right_box;
	t_bin					bins[BVH_BINS];
	double					left_area[BVH_BINS - 1];
	int						left_counts[BVH_BINS - 1];
	double					min_val;
	double					max_val;
	double					parent_sa;
	double					scale;
	double					best_cost;
	double					split_pos;
	int						right_count;
	int						best_axis;
	int						i;
}							t_bvh_sah;

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


typedef struct s_mesh_query
{
	const struct s_sphere	*s;
	struct s_mesh			*m;
	t_vec3					*out_n;
	double					*out_p;
	t_aabb					sa;
	double					min_d;
	bool					hit;
}							t_mesh_query;

typedef struct s_capsule_var
{
	t_vec3					ab;
	t_vec3					as;
	t_vec3					cl;
	t_vec3					d;
	double					t;
	double					dsq;
	double					rs;
	double					dist;
}							t_capsule_var;

typedef struct s_tri_var
{
	t_vec3					cl;
	t_vec3					d;
	double					dsq;
	double					rad;
	double					dist;
}							t_tri_var;



/** CTX **/
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

typedef struct s_extract_ctx
{
	char					*bin;
	t_accessor				*acc;
	t_buffer_view			*bv;
	void					*entry;
	int						stride;
	int						count;
	int						type_size;
}							t_extract_ctx;



typedef struct s_trace_ctx
{
	int						stack[64];
	int						top;
	int						node_idx;
	int						best_tri;
	double					best_t;
	t_vec2					best_uv;
}							t_trace_ctx;

typedef struct s_occ_ctx
{
	int						stack[64];
	int						top;
	int						node_idx;
	double					dist;
}							t_occ_ctx;

typedef struct s_leaf_ctx
{
	int						tri;
	double					t;
	t_vec2					uv;
	t_vec3					v[3];
}							t_leaf_ctx;

typedef struct s_child_ctx
{
	int						left_idx;
	int						right_idx;
	double					tl_min;
	double					tl_max;
	double					tr_min;
	double					tr_max;
	bool					hit_l;
	bool					hit_r;
}							t_child_ctx;

typedef struct s_fbx_parse_ctx
{
	int						fd;
	bool					is_64;
	t_fbx_data				*d;
}							t_fbx_parse_ctx;

typedef struct s_fbx_bin_ctx
{
	int						fd;
	uint32_t				version;
	t_skinned_mesh			mesh;
	t_fbx_data				data;
}							t_fbx_bin_ctx;


typedef struct s_fbx_ascii_ctx
{
	t_skinned_mesh			mesh;
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


typedef struct s_mesh_build_item
{
	t_aabb					bbox;
	t_vec3					centroid;
	int					index;
	int					first_tri;
	int					count;
	int					parent;
	int					axis;
} t_mesh_build_item;

typedef struct s_mbvh_ctx
{
	t_mesh_build_item		*items;
	t_mbvh_node				*nodes;
	int						node_count;
}							t_mbvh_ctx;


typedef struct s_bvh_bins_ctx
{
	t_mbvh_ctx				*ctx;
	int						first;
	int						count;
	int						axis;
	double					min_val;
	double					scale;
	t_bin					*bins;
}							t_bvh_bins_ctx;

typedef struct s_bvh_eval_ctx
{
	t_mbvh_ctx				*ctx;
	t_mbvh_node				*node;
	int						first;
	int						count;
	int						axis;
	t_bvh_sah				*s;
}							t_bvh_eval_ctx;

typedef struct s_bvh_find_ctx
{
	t_mbvh_ctx				*ctx;
	t_mbvh_node				*node;
	int						first;
	int						count;
	t_bvh_sah				s;
	t_bvh_split				*out;
}							t_bvh_find_ctx;

typedef struct s_bvh_try_ctx
{
	t_mbvh_ctx				*ctx;
	t_mbvh_node				*node;
	int						first;
	int						count;
	t_bvh_split				*split;
	int						*mid;
}							t_bvh_try_ctx;




/* 3. PARSING */
bool						fdf_get_dimensions(const char *path, int *w,
								int *h);
void						fdf_fill_data(const char *path, t_mesh *mesh, int w,
								int h);
void						fdf_compute_normals(t_mesh *mesh, int w, int h);
void						fdf_compute_uvs(t_mesh *mesh, int w, int h);
void						fdf_triangulate(t_mesh *mesh, int w, int h);
bool						fdf_init_mesh(t_mesh *mesh, int v_count,
								int i_count, const char *p);

void						glb_parse_accessor(t_json_value *json, int index,
								t_accessor *acc);
void						glb_parse_buffer_view(t_json_value *json, int index,
								t_buffer_view *bv);
void						glb_extract_data(t_extract_ctx ctx);
void						glb_handle_indices_short(t_mesh *mesh,
								t_json_value *json, char *bin, int idx);
void						glb_fill_attributes(t_mesh *mesh,
								t_json_value *json, char *bin, int ids[6]);
bool						glb_load_primitive(t_mesh *mesh, t_json_value *json,
								char *bin, int mesh_idx, int prim_idx,
								int mat_id);
bool						glb_read_buffers(int fd, char *buf[2]);

/* Parsing Helpers */


/* .rt Parser (srcs/objects/rt/parsing/) */


void						update_object_material(void *obj_data, t_type type);
void						mesh_apply_transform(t_mesh *mesh,
								t_transform transform);
bool						mesh_init(t_mesh *mesh, t_mesh_init init);
void						init_mesh(t_mesh *mesh, const char *path);
void						mesh_free(t_mesh *mesh);

/* File Specific Parsers */
bool						fbx_bin_build_mesh(t_fbx_bin_ctx *ctx);
void						fbx_build_flat(t_mesh *m, t_fbx_flat_args *p);
bool						fbx_setup_build(t_fbx_build *b, t_mesh *m,
								t_fbx_flat_args *p);
void						fbx_build_tris(t_fbx_build *b);
void						fbx_free_build(t_fbx_build *b);
char						*fbx_next(char *p);
char						*find_node(char *p, char *end, const char *name);
char						*advance_to_data(char *p, char *end);
char						*read_file_content(const char *path,
								size_t *out_size);
void						*parse_array(char **p, int *count, size_t sz,
								void (*f)(char **, void *));
void						f_vec3(char **p, void *dst);
void						f_vec2(char **p, void *dst);
void						f_int(char **p, void *dst);
void						ascii_load_normals(t_fbx_ascii_ctx *ctx);
void						ascii_load_uvs(t_fbx_ascii_ctx *ctx);
ssize_t						safe_read(int fd, void *buf, size_t count);
void						*read_fbx_array(int fd, uint32_t *count,
								size_t elem_sz);
void						skip_properties(int fd, uint64_t num_props);
void						read_offsets(int fd, t_fbx_bin_node *node,
								bool is_64bit);
void						read_node_header(int fd, t_fbx_bin_node *node,
								bool is_64bit);
void						parse_nodes(int fd, uint64_t end_offset, bool is_64,
								t_fbx_data *d);
t_vec3						*repack_doubles_to_vec3(double *raw,
								uint32_t count);

bool						obj_read_id(t_parser *p, char *id, size_t max_len);
void						obj_skip_line(t_parser *p);
char						*fbx_ascii_parse_texture_path(char *p, char *end,
								const char *fbx_p);
void						obj_parse_v(t_obj_ctx *ctx, t_parser *p);
void						obj_parse_vt(t_obj_ctx *ctx, t_parser *p);
void						obj_parse_vn(t_obj_ctx *ctx, t_parser *p);
void						obj_parse_f(t_obj_ctx *ctx, t_parser *p);
int							obj_fix_index(int idx, int count);
void						obj_set_out_vertex(t_obj_ctx *ctx, int vi, int vti,
								int vni);
void						obj_ensure_out_capacity(t_obj_ctx *ctx);
void						obj_face_init(t_obj_face *face);
void						obj_face_read(t_parser *p, t_obj_face *face);
void						obj_face_read_slash(t_parser *p, t_obj_face *face);
void						obj_face_emit_tris(t_obj_ctx *ctx,
								t_obj_face *face);
void						obj_add_vert(t_obj_ctx *ctx, int vi, int vti,
								int vni);
void						obj_free_ctx(t_obj_ctx *ctx);
void						obj_generate_normals(t_obj_ctx *ctx);
bool						obj_finalize_mesh_raw(t_obj_ctx *ctx, t_raw_model *model, const char *path);
void						obj_init_mesh(t_mesh *mesh, t_obj_ctx *ctx, const char *path);
void						obj_parse_mtllib_raw(t_obj_ctx *ctx, struct s_parser *p, t_raw_model *model, const char *obj_path);
void						obj_parse_usemtl_raw(t_obj_ctx *ctx, struct s_parser *p, t_raw_model *model);
void						obj_set_mat_id(t_mesh *mesh, t_obj_ctx *ctx);
bool						mtl_open(const char *path, int *fd);
char						*mtl_resolve_path(const char *mtl_path,
								const char *tex_filename);
void						mtl_trim_line_end(char *p);
char						*mtl_skip_ws(char *p);
bool						mtl_is_tag(char *p, const char *tag);

/* Build logic */
void						mesh_build_bvh(t_mesh *mesh);
void						mesh_build_tri_cache(t_mesh *mesh);

void						bvh_get_triangle_info(t_mesh *mesh, int tri_idx,
								t_mesh_build_item *out);
int							bvh_partition_items(t_mesh_build_item *items,
								int count, int axis, double split_val);
void						bvh_copy_indices(t_mesh *mesh, t_mbvh_ctx *ctx);
void						bvh_update_node_bounds(t_mbvh_node *node,
								t_mbvh_ctx *ctx, int first, int count);
void						bvh_centroid_bounds(t_mbvh_ctx *ctx, int first,
								int count, t_aabb *out);
void						bvh_axis_min_max(t_aabb *bounds, int axis,
								double *min_val, double *max_val);
void						bvh_bins_init(t_bin *bins);
void						bvh_fill_bins(t_bvh_bins_ctx *b);
void						bvh_sweep_left(t_bin *bins, double *left_area,
								int *left_counts);
void						bvh_sweep_right(t_bvh_sah *s, int axis);
void						bvh_eval_axis(t_bvh_eval_ctx *e);
bool						bvh_find_split(t_bvh_find_ctx *f);

/* srcs/objects/mesh/collision */
t_vec3						closest_point_on_triangle(t_vec3 p, t_vec3 v0,
								t_vec3 v1, t_vec3 v2);
bool						detect_sphere_mesh_collision(const struct s_sphere *s,
								struct s_mesh *m, t_vec3 *out_normal,
								double *out_penetration);

/* LOADERS */
bool						load_mesh_file(const char *path, t_raw_model *out);
bool						fbx_load(const char *path, t_raw_model *out);
bool						fbx_load_binary(const char *path, t_raw_model *out);
bool						fbx_load_ascii(const char *path, t_raw_model *out);
bool						obj_load(const char *path, t_raw_model *out);
bool						fdf_load(const char *path, t_raw_model *out);
bool						glb_load(const char *path, t_raw_model *out);
t_raw_material				*glb_extract_materials(struct s_json_value *json,
								char *bin, int *out_count);
t_animation					*glb_extract_animations(struct s_json_value *json,
								char *bin, int *out_count);
bool						mtl_load(const char *path, t_raw_model *out);
void						mtl_parse_lines_raw(t_raw_model *model,
								struct s_parser *parser, int *cur_mat_idx,
								const char *path);
void						mtl_parse_line_raw(t_raw_model *model,
								char *line, int *cur_mat_idx,
								const char *mtl_path);
bool						mtl_open(const char *path, int *fd);
void						model_apply_transform(t_raw_model *model, t_transform transform);
void						model_apply_material_override(t_raw_model *model, t_vec3 color, t_vec3 emission);
int							raw_model_add_material(t_raw_model *model, const char *name);
void						raw_material_set_texture(t_raw_material *mat, const char *path);

/* AABB Core Management */
t_aabb						aabb_create_empty(void);
t_aabb						aabb_union(const t_aabb *a, const t_aabb *b);
void						aabb_expand_point(t_aabb *a, t_vec3 p);
void						aabb_expand_eps(t_aabb *a, double eps);
double						aabb_surface_area(t_aabb a);
t_aabb						aabb_transform(t_aabb bbox, t_transform t);
bool						aabb_overlap(t_aabb a, t_aabb b);

/* Per-shape world-space AABB producers */
t_aabb						sphere_aabb(t_sphere *sp);
t_aabb						plane_aabb(t_plane *pl);
t_aabb						cylinder_aabb(t_cylinder *cy);
t_aabb						cone_aabb(t_cone *co);
t_aabb						tri_aabb(t_tri_shape *tr);
t_aabb						rect_aabb(t_rect *rc);
t_aabb						pyramid_aabb(t_pyramid *py);
t_aabb						box_aabb(t_box *bx);
t_aabb						capsule_aabb(t_capsule *cp);

/* Decoupled Parsing (Rule 1) */
t_parse_obj					rt_parse_ambient_obj(struct s_parser *p);
t_parse_obj					rt_parse_camera_obj(struct s_parser *p);
t_parse_obj					rt_parse_light_obj(struct s_parser *p);
t_parse_obj					rt_parse_sphere_obj(struct s_parser *p);
t_parse_obj					rt_parse_plane_obj(struct s_parser *p);
t_parse_obj					rt_parse_cylinder_obj(struct s_parser *p);
t_parse_obj					rt_parse_cone_obj(struct s_parser *p);
t_parse_obj					rt_parse_tri_shape_obj(struct s_parser *p);
t_parse_obj					rt_parse_rect_obj(struct s_parser *p);
t_parse_obj					rt_parse_pyramid_obj(struct s_parser *p);
t_parse_obj					rt_parse_box_obj(struct s_parser *p);
t_parse_obj					rt_parse_capsule_obj(struct s_parser *p);
#endif
