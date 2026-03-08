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
# include "core.h"
# include "surface.h"
# include "physics.h"

typedef struct s_json_value	t_json_value;

/* ------------------------------------------------------------------------- */
/*                             LEAF STRUCTURES                               */
/* ------------------------------------------------------------------------- */

struct				s_sphere
{
	t_transform		transform;
	double			radius_sq;
	int				mat_id;
	t_vec3			temp_color;
	t_physics_body      phys;
	bool				is_deformed;
	t_mat4				inv_transform;
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

typedef struct s_bin
{
	t_aabb				bounds;
	int					count;
}						t_bin;

typedef struct s_tri_precomp
{
	t_vec3				v0;
	t_vec3				e1;
	t_vec3				e2;
}						t_tri_precomp;

typedef struct s_mbvh_node
{
	t_aabb				bbox;
	int					left_or_first;
	int					count;
	int					axis;
}						t_mbvh_node;

typedef struct s_mbvh_ctx
{
	t_mesh_build_item	*items;
	t_mbvh_node			*nodes;
	int					node_count;
}						t_mbvh_ctx;

typedef struct s_bone_weight
{
	int					bone_ids[4];
	double				weights[4];
}						t_bone_weight;

typedef struct s_transform_q
{
	t_vec3				pos;
	t_vec3				rot; /* Quaternion */
	t_vec3				scale;
}						t_transform_q;

typedef struct s_bone
{
	char				*name;
	int					node_idx;
	int					parent;
	t_mat4				local_transform;	t_mat4				global_transform;	t_mat4				bind_pose;
	t_mat4				inv_bind_pose;
	t_transform_q		trs;
}						t_bone;

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
	t_mbvh_node			*bvh_nodes;
	int					*bvh_indices;
	t_tri_precomp		*tri_cache;
	int					mat_id;
	t_bone_weight		*skin_data;
	t_bone				*skeleton;
	int					bone_count;
	t_mat4				*bone_matrices;
	t_vec3				*base_vertices;
	t_vec3				*base_normals;
	int					node_idx;
	/* Scene-level transform (baked from .rt file, reapplied each frame after skinning) */
	t_mat4				scene_mat;
	t_mat4				scene_rot_mat;
	bool				has_scene_transform;
	/* Physics */
	t_physics_body		phys;
	int					current_anim;
	int					anim_base;       /* index of first clip in scene->clips[] */
	int					anim_clip_count; /* number of clips belonging to this mesh */
	double				anim_time;
	t_collider				collider;
	int						group_id;	 /* -1 = standalone; ≥0 = mesh group (all GLB submeshes share one) */
	/* Editor: post-bake snapshot for live transform editing */
	t_vec3					*edit_snap_verts;
	t_vec3					*edit_snap_norms;
	t_vec3					edit_snap_pivot;};

typedef enum e_interpolation
{
	INTERP_LINEAR,
	INTERP_STEP,
	INTERP_CUBIC
}						t_interpolation;

typedef struct s_anim_sampler
{
	float				*inputs;
	float				*outputs;
	int					count;
	t_interpolation		method;
}						t_anim_sampler;

typedef enum e_anim_path
{
	PATH_TRANSLATION,
	PATH_ROTATION,
	PATH_SCALE,
	PATH_WEIGHTS
}						t_anim_path;

typedef struct s_anim_channel
{
	int					node_idx;
	t_anim_path			path;
	int					sampler_idx;
}						t_anim_channel;

typedef struct s_animation
{
	char				*name;
	t_anim_channel		*channels;
	int					channel_count;
	t_anim_sampler		*samplers;
	int					sampler_count;
	double				max_time;
	double				current_time;
}						t_animation;

typedef struct s_mesh_init
{
	int					v_count;
	int					i_count;
	bool				has_uvs;
	bool				has_normals;
}						t_mesh_init;

void					mesh_apply_transform(t_mesh *mesh,
							t_transform transform);
bool					mesh_init(t_mesh *mesh, t_mesh_init init);
void					mesh_free(t_mesh *mesh);

typedef struct s_glb_header
{
	uint32_t			magic;
	uint32_t			version;
	uint32_t			length;
}						t_glb_header;

typedef struct s_chunk_header
{
	uint32_t			length;
	uint32_t			type;
}						t_chunk_header;

typedef struct s_accessor
{
	int					buffer_view;
	int					byte_offset;
	int					component_type;
	int					count;
	char				type[16];
}						t_accessor;

typedef struct s_buffer_view
{
	int					buffer;
	int					byte_offset;
	int					byte_length;
	int					byte_stride;
}						t_buffer_view;

typedef struct s_fbx_bin_node
{
	uint64_t			end_offset;
	uint64_t			num_properties;
	uint64_t			property_list_len;
	uint8_t				name_len;
	char				name[1024];
}						t_fbx_bin_node;

struct					s_skinned_mesh
{
	t_mesh				base;
	/* INHERITANCE: Re-use all mesh intersection code! */
	t_vec3 *base_vertices; /* Original un-posed vertices */
	t_bone *skeleton;      /* The hierarchy of bones */
	t_mat4				*bone_matrices;
	/* The current pose transformations (Global Space) */
	t_bone_weight *weights; /* Per-vertex weights */
	int					bone_count;
	int					vertex_count;
};

/*
** Group container: one entry per loaded model file.
** Owns a contiguous range [start, start+sub_count) in scene->meshes[].
** All editor-level state (transform sliders, pivot, physics) lives here;
** individual submeshes are pure geometry + per-primitive rendering data.
*/
typedef struct s_mesh_group
{
	char			*name;          /* display name — GLB basename, owned heap */
	char			*path;          /* source file path, owned heap */
	int				start;         /* first submesh index in scene->meshes[] */
	int				sub_count;     /* number of consecutive submeshes */
	t_transform		transform;     /* editor-controlled delta (identity after bake) */
	t_vec3			pivot;         /* union-bbox centre of all subs for SR+T */
	t_physics_body	phys;
	t_collider		collider;
	int				anim_base;
	int				anim_clip_count;
}					t_mesh_group;

/* Parsing and Build Types */

struct					s_mesh_info
{
	char				*path;
	t_transform			transform;
	t_vec3				color;
	t_vec3				emission;
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
	t_vec3				*temp_v;
	size_t				v_count;
	size_t				v_cap;
	t_vec2				*temp_vt;

	size_t				vt_count;
	size_t				vt_cap;
	t_vec3				*temp_vn;
	size_t				vn_count;
	size_t				vn_cap;

	t_vec3				*out_v;
	t_vec3				*out_vn;
	t_vec2				*out_vt;
	int					*out_i;
	size_t				out_v_count;
	size_t				out_v_cap;
	size_t				out_i_count;
	size_t				out_i_cap;
	int					current_mat_id;
	int					first_mtl_id;
	t_aabb				bbox;
}						t_obj_ctx;

typedef struct s_obj_face
{
	int					vi[32];
	int					vti[32];
	int					vni[32];
	int					count;
}						t_obj_face;

typedef struct s_mesh_hit_ctx
{
	t_hit				*hit;
	t_mesh				*mesh;
	const t_ray			*ray;
	t_vec2				bary;
	double				t;
	int					tri;
}						t_mesh_hit_ctx;

typedef struct s_hit_calc
{
	t_mesh_hit_ctx		*in;
	int					*idx;
	t_vec3				v[3];
}						t_hit_calc;

typedef struct s_tri_hit
{
	t_vec3				e1;
	t_vec3				e2;
	t_vec3				pvec;
	t_vec3				tvec;
	t_vec3				qvec;
	double				det;
	double				inv_det;
	double				u;
	double				v;
}						t_tri_hit;

typedef struct s_fdf_row_ctx
{
	t_mesh				*mesh;
	int					dims[2];
	int					row;
}						t_fdf_row_ctx;

typedef struct s_extract_ctx
{
	char				*bin;
	t_accessor			*acc;
	t_buffer_view		*bv;
	void				*entry;
	int					stride;
	int					count;
	int					type_size;
}						t_extract_ctx;

typedef struct s_parser	t_parser;

typedef struct s_rt_ctx
{
	t_parser			*parser;
	int					fd;
	char				id[16];
	t_parse_obj			obj;
	bool				status;
}						t_rt_ctx;

typedef struct s_fdf_dim
{
	int					w;
	int					h;
}						t_fdf_dim;

typedef struct s_trace_ctx
{
	int					stack[64];
	int					top;
	int					node_idx;
	int					best_tri;
	double				best_t;
	t_vec2				best_uv;
}						t_trace_ctx;

typedef struct s_occ_ctx
{
	int					stack[64];
	int					top;
	int					node_idx;
	double				dist;
}						t_occ_ctx;

typedef struct s_leaf_ctx
{
	int					tri;
	double				t;
	t_vec2				uv;
	t_vec3				v[3];
}						t_leaf_ctx;

typedef struct s_child_ctx
{
	int					left_idx;
	int					right_idx;
	double				tl_min;
	double				tl_max;
	double				tr_min;
	double				tr_max;
	bool				hit_l;
	bool				hit_r;
}						t_child_ctx;

typedef struct s_occ_child
{
	int					left_idx;
	int					right_idx;
	double				tl_min;
	double				tl_max;
	double				tr_min;
	double				tr_max;
	bool				hit_l;
	bool				hit_r;
}						t_occ_child;

typedef struct s_bvh_split
{
	int					axis;
	double				pos;
}						t_bvh_split;

typedef struct s_bvh_sah
{
	t_aabb				centroid_bounds;
	t_aabb				right_box;
	t_bin				bins[BVH_BINS];
	double				left_area[BVH_BINS - 1];
	int					left_counts[BVH_BINS - 1];
	double				min_val;
	double				max_val;
	double				parent_sa;
	double				scale;
	double				best_cost;
	double				split_pos;
	int					right_count;
	int					best_axis;
	int					i;
}						t_bvh_sah;

typedef struct s_bvh_bins_ctx
{
	t_mbvh_ctx			*ctx;
	int					first;
	int					count;
	int					axis;
	double				min_val;
	double				scale;
	t_bin				*bins;
}						t_bvh_bins_ctx;

typedef struct s_bvh_eval_ctx
{
	t_mbvh_ctx			*ctx;
	t_mbvh_node			*node;
	int					first;
	int					count;
	int					axis;
	t_bvh_sah			*s;
}						t_bvh_eval_ctx;

typedef struct s_bvh_find_ctx
{
	t_mbvh_ctx			*ctx;
	t_mbvh_node			*node;
	int					first;
	int					count;
	t_bvh_sah			s;
	t_bvh_split			*out;
}						t_bvh_find_ctx;

typedef struct s_bvh_try_ctx
{
	t_mbvh_ctx			*ctx;
	t_mbvh_node			*node;
	int					first;
	int					count;
	t_bvh_split			*split;
	int					*mid;
}						t_bvh_try_ctx;

typedef struct s_fbx_data
{
	t_vec3				*v;
	uint32_t			vc;
	int					*ri;
	uint32_t			rc;
	t_vec3				*vn;
	uint32_t			nc;
	t_vec2				*vu;
	uint32_t			uc;
}						t_fbx_data;

typedef struct s_fbx_flat_params
{
	int					*raw;
	int					raw_c;
	t_vec3				*n;
	int					nc;
	t_vec2				*u;
	int					uc;
	int					vc;
}						t_fbx_flat_params;

typedef struct s_fbx_build
{
	t_mesh				*m;
	int					*raw;
	int					raw_c;
	t_vec3				*n;
	int					nc;
	t_vec2				*u;
	int					uc;
	int					vc;
	int					tc;
	t_vec3				*nv;
	t_vec3				*nn;
	t_vec2				*nu;
	int					*ni;
	int					*v;
	int					vp;
	int					ps;
	int					use_v_n;
	int					use_v_u;
}						t_fbx_build;

typedef struct s_fbx_parse_ctx
{
	int					fd;
	bool				is_64;
	t_fbx_data			*d;
}						t_fbx_parse_ctx;

typedef struct s_fbx_array_req
{
	const char			*label;
	void				**dst;
	uint32_t			*count;
	size_t				elem_sz;
	uint32_t			div;
}						t_fbx_array_req;

typedef struct s_fbx_array
{
	uint32_t			arr_len;
	uint32_t			encoding;
	uint32_t			comp_len;
	size_t				actual_sz;
	char				type;
}						t_fbx_array;

typedef struct s_fbx_bin_ctx
{
	int					fd;
	uint32_t			version;
	t_skinned_mesh		mesh;
	t_fbx_data			data;
}						t_fbx_bin_ctx;

typedef struct s_fbx_buf
{
	char				*buf;
	size_t				cap;
	size_t				len;
}						t_fbx_buf;

typedef struct s_fbx_ascii_ctx
{
	t_skinned_mesh		mesh;
	t_vec3				*rn;
	t_vec2				*ru;
	int					*ri;
	int					rc;
	int					vc;
	int					nc;
	int					uc;
	char				*buf;
	char				*p;
	char				*end;
	size_t				buf_size;
	int					mat_id;
	const char			*path;
}						t_fbx_ascii_ctx;

t_parse_obj				dispatch_scan(t_parser *p, char *id);
t_parse_obj				parse_mesh_entry(t_parser *p, t_type type);
bool					handle_mesh_injection(t_parse_obj *obj, const char *ext,
							t_scene *scene);
bool					mesh_cache_has(const char *path);
bool					mesh_cache_save(const char *path, t_scene *scene,
						int start_mesh);
bool					mesh_cache_restore(const char *path, t_scene *scene);
bool					process_object(t_scene *scene, t_parse_obj obj);
const char				*rt_get_extension(const char *path);
bool					rt_init_parser(t_rt_ctx *ctx, const char *path);
bool					rt_parse_loop(t_scene *scene, t_rt_ctx *ctx);
bool					rt_parse_entry(t_scene *scene, t_rt_ctx *ctx);
bool					rt_parse_token(t_parser *p, char *buf, size_t max_len);
void					rt_parse_scale(t_parser *p, t_parse_obj *obj);
t_parse_obj				rt_mesh_fail(t_parse_obj obj);
bool					rt_parse_mesh_position(t_parser *p, t_parse_obj *obj);
bool					rt_parse_mesh_rotation(t_parser *p, t_parse_obj *obj);
void					rt_parse_mesh_color(t_parser *p, t_parse_obj *obj);
void					rt_parse_mesh_emission(t_parser *p, t_parse_obj *obj);

/* 3. PARSING */
bool					fdf_get_dimensions(const char *path, int *w, int *h);
void					fdf_fill_data(const char *path, t_mesh *mesh, int w,
							int h);
void					fdf_compute_normals(t_mesh *mesh, int w, int h);
void					fdf_compute_uvs(t_mesh *mesh, int w, int h);
void					fdf_triangulate(t_mesh *mesh, int w, int h);
bool					fdf_init_mesh(t_mesh *mesh, int v_count, int i_count,
							const char *p);

void					glb_parse_accessor(t_json_value *json, int index,
							t_accessor *acc);
void					glb_parse_buffer_view(t_json_value *json, int index,
							t_buffer_view *bv);
void					glb_extract_data(t_extract_ctx ctx);
void					glb_handle_indices_short(t_mesh *mesh, t_json_value *json,
							char *bin, int idx);
void					glb_fill_attributes(t_mesh *mesh, t_json_value *json, char *bin,
							int ids[6]);
bool					glb_load_primitive(t_mesh *mesh, t_json_value *json, char *bin,
							int mesh_idx, int prim_idx, int mat_id);
int						*glb_load_materials(t_scene *scene, t_json_value *json,
							char *bin);
bool					glb_read_buffers(int fd, char *buf[2]);
void					glb_load_skeleton(t_mesh *mesh, t_json_value *json,
							char *bin, int extra_count);
int						glb_count_extra_anim_nodes(t_json_value *json);
void					glb_fill_extra_anim_nodes(t_mesh *mesh,
							t_json_value *json);
void					glb_load_animations(t_scene *scene, t_json_value *json,
							char *bin);

/* Parsing Helpers */
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
bool					fbx_bin_build_mesh(t_fbx_bin_ctx *ctx);
void					fbx_build_flat(t_mesh *m, t_fbx_flat_params *p);
bool					fbx_setup_build(t_fbx_build *b, t_mesh *m,
							t_fbx_flat_params *p);
void					fbx_build_tris(t_fbx_build *b);
void					fbx_free_build(t_fbx_build *b);
char					*fbx_next(char *p);
char					*find_node(char *p, char *end, const char *name);
char					*advance_to_data(char *p, char *end);
char					*read_file_content(const char *path, size_t *out_size);
void					*parse_array(char **p, int *count, size_t sz,
							void (*f)(char **, void *));
void					f_vec3(char **p, void *dst);
void					f_vec2(char **p, void *dst);
void					f_int(char **p, void *dst);
int						parse_texture(char *p, char *end, t_scene *scene,
							const char *fbx_path);
void					ascii_load_normals(t_fbx_ascii_ctx *ctx);
void					ascii_load_uvs(t_fbx_ascii_ctx *ctx);
ssize_t					safe_read(int fd, void *buf, size_t count);
void					*read_fbx_array(int fd, uint32_t *count,
							size_t elem_sz);
void					skip_properties(int fd, uint64_t num_props);
void					read_offsets(int fd, t_fbx_bin_node *node,
							bool is_64bit);
void					read_node_header(int fd, t_fbx_bin_node *node,
							bool is_64bit);
void					parse_nodes(int fd, uint64_t end_offset, bool is_64,
							t_fbx_data *d);
t_vec3					*repack_doubles_to_vec3(double *raw, uint32_t count);

bool					obj_read_id(t_parser *p, char *id, size_t max_len);
void					obj_skip_line(t_parser *p);
void					obj_parse_v(t_obj_ctx *ctx, t_parser *p);
void					obj_parse_vt(t_obj_ctx *ctx, t_parser *p);
void					obj_parse_vn(t_obj_ctx *ctx, t_parser *p);
void					obj_parse_f(t_obj_ctx *ctx, t_parser *p);
void					obj_parse_mtllib(t_obj_ctx *ctx, t_parser *p,
							t_scene *scene, const char *obj_path);
void					obj_parse_usemtl(t_obj_ctx *ctx, t_parser *p,
							t_scene *scene);
bool					obj_build_mesh(t_scene *scene, t_obj_ctx *ctx,
							const char *path);
int						obj_fix_index(int idx, int count);
void					obj_set_out_vertex(t_obj_ctx *ctx, int vi, int vti,
							int vni);
void					obj_ensure_out_capacity(t_obj_ctx *ctx);
void					obj_face_init(t_obj_face *face);
void					obj_face_read(t_parser *p, t_obj_face *face);
void					obj_face_read_slash(t_parser *p, t_obj_face *face);
void					obj_face_emit_tris(t_obj_ctx *ctx, t_obj_face *face);
void					obj_add_vert(t_obj_ctx *ctx, int vi, int vti, int vni);
void					obj_free_ctx(t_obj_ctx *ctx);
void					obj_generate_normals(t_obj_ctx *ctx);
void					obj_init_mesh(t_mesh *mesh, t_obj_ctx *ctx,
							const char *path);
void					obj_set_mat_id(t_mesh *mesh, t_obj_ctx *ctx);
bool					mtl_open(const char *path, int *fd);
void					mtl_parse_lines(t_scene *scene, t_parser *parser,
							int *cur_mat, const char *path);
void					mtl_parse_line(t_scene *scene, char *line, int *cur_mat,
							const char *mtl_path);
void					mtl_handle_newmtl(t_scene *scene, char *p,
							int *cur_mat);
void					mtl_handle_map_kd(t_scene *scene, char *p, int cur_mat,
							const char *mtl_path);
char					*mtl_resolve_path(const char *mtl_path,
							const char *tex_filename);
void					mtl_trim_line_end(char *p);
char					*mtl_skip_ws(char *p);
bool					mtl_is_tag(char *p, const char *tag);

/* Build logic */
void					mesh_build_bvh(t_mesh *mesh);
void					mesh_build_tri_cache(t_mesh *mesh);
bool					intersect_triangle(const t_ray *ray, t_vec3 v[3],
							double *t, t_vec2 *uv);
bool					intersect_triangle_fast(const t_ray *ray, t_vec3 v[3],
							double *t, t_vec2 *uv);
bool					intersect_tri_precomp(const t_ray *ray,
							const t_tri_precomp *tc, double *t, t_vec2 *uv);
bool					intersect_mesh(const t_ray *ray, t_mesh *mesh,
							t_hit *hit);
bool					mesh_occluded(const t_ray *ray, t_mesh *mesh,
							double dist);
bool					leaf_occluded(t_mesh *mesh, t_mbvh_node *node,
							const t_ray *ray, double dist);
void					test_occ_children(t_mesh *mesh, int node_idx,
							const t_ray *ray, t_occ_child *c);
int						pick_occ_children(t_mesh *mesh, int node_idx,
							const t_ray *ray, t_occ_ctx *ctx);
int						process_occ_node(t_mesh *mesh, int node_idx,
							const t_ray *ray, t_occ_ctx *ctx);
bool					traverse_occlude(t_mesh *mesh, const t_ray *ray,
							double dist);
void					update_mesh_hit(t_mesh_hit_ctx *ctx);
void					intersect_init_ctx(t_trace_ctx *ctx, t_hit *hit);
void					process_mesh_leaf(t_mesh *mesh, t_mbvh_node *node,
							const t_ray *ray, t_trace_ctx *ctx);
void					test_children(t_mesh *mesh, int node_idx,
							const t_ray *ray, t_child_ctx *c);
int						select_child(t_child_ctx *c, t_trace_ctx *ctx);
int						pick_children(t_mesh *mesh, int node_idx,
							const t_ray *ray, t_trace_ctx *ctx);
int						process_node(t_mesh *mesh, int node_idx,
							const t_ray *ray, t_trace_ctx *ctx);
void					intersect_traverse_mesh(t_mesh *mesh, const t_ray *ray,
							t_trace_ctx *ctx);
bool					intersect_finish_hit(t_trace_ctx *ctx, t_mesh *mesh,
							t_hit *hit, const t_ray *ray);

void					bvh_get_triangle_info(t_mesh *mesh, int tri_idx,
							t_mesh_build_item *out);
int						bvh_partition_items(t_mesh_build_item *items, int count,
							int axis, double split_val);
void					bvh_copy_indices(t_mesh *mesh, t_mbvh_ctx *ctx);
void					bvh_update_node_bounds(t_mbvh_node *node,
							t_mbvh_ctx *ctx, int first, int count);
void					bvh_centroid_bounds(t_mbvh_ctx *ctx, int first,
							int count, t_aabb *out);
void					bvh_axis_min_max(t_aabb *bounds, int axis,
							double *min_val, double *max_val);
void					bvh_bins_init(t_bin *bins);
void					bvh_fill_bins(t_bvh_bins_ctx *b);
void					bvh_sweep_left(t_bin *bins, double *left_area,
							int *left_counts);
void					bvh_sweep_right(t_bvh_sah *s, int axis);
void					bvh_eval_axis(t_bvh_eval_ctx *e);
bool					bvh_find_split(t_bvh_find_ctx *f);

/* srcs/objects/glb/anim_system.c */
void					glb_update_mesh_anim(t_mesh *mesh, t_scene *scene,
							double dt);

/* 4. IMPLEMENTATION IMPORTS */
# include "debug.h"
# include "parser.h"
# include "raytracing.h"
# include "utils.h"

#endif
