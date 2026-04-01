/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_meshes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:23:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 18:03:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_PRIMITIVES_MESHES_H
# define TYPES_PRIMITIVES_MESHES_H

# include "t_maths.h"
# include "t_physics.h"

# define BVH_BINS 16

typedef struct s_json_value	t_json_value;
typedef struct s_mesh	t_mesh;

typedef struct s_vertex
{
	t_vec3				pos;
	t_vec3				normal;
	t_vec2				uv;
	t_vec3				tangent;
	t_vec3				bitangent;
	int					bone_ids[4];
	float				bone_weights[4];
}						t_vertex;

typedef struct s_triangle
{
	int					v[3];
}						t_triangle;

typedef struct s_bone_weight
{
	int					bone_indices[4];
	float				weights[4];
}						t_bone_weight;

typedef struct s_tri_precomp
{
	t_vec3				v0;
	t_vec3				e1;
	t_vec3				e2;
}						t_tri_precomp;

typedef struct s_mesh_geom
{
	t_vec3				*vertices;
	t_vec3				*normals;
	t_vec2				*uvs;
	int					*indices;
	int					vertex_count;
	int					tri_count;
	int					index_count;
}						t_mesh_geom;

typedef struct s_mesh_group
{
	int					mesh_start;
	int					mesh_count;
	int					start;
	int					sub_count;
	t_vec3				pivot;
	char				*name;
	char				*path;
	t_transform			transform;
	t_physics_body		phys;
}						t_mesh_group;

typedef struct s_bone
{
	char				*name;
	int					parent;
	int					node_idx;
	t_mat4				offset_matrix;
	t_mat4				local_transform;
	t_mat4				global_transform;
	t_mat4				inv_bind_pose;
	t_transform			trs;
	t_vec4				r_quat;
}						t_bone;

typedef struct s_mbvh_node
{
	t_aabb				bbox;
	int					left_or_first;
	int					count;
	int					axis;
}						t_mbvh_node;

typedef struct s_bin
{
	t_aabb				bounds;
	int					count;
}						t_bin;

typedef struct s_bvh_bins
{
	struct s_mbvh		*bvh;
	int					first;
	int					count;
	int					axis;
	double				min_val;
	double				scale;
	t_bin				*bins;
}						t_bvh_bins;

typedef struct s_bvh_split
{
	t_aabb				centroid_bounds;
	double				min_val;
	double				max_val;
	double				scale;
	double				parent_sa;
	t_bin				bins[BVH_BINS];
	double				left_area[BVH_BINS];
	int					left_counts[BVH_BINS];
	int					axis;
	double				pos;
	double				best_cost;
	int					i;
	double				split_pos;
	int					right_count;
	t_aabb				right_box;
	int					best_axis;
}						t_bvh_split;

typedef struct s_bvh_eval
{
	struct s_mbvh		*bvh;
	struct s_mbvh_node	*node;
	struct s_bvh_split	*s;
	int					first;
	int					count;
	int					axis;
}						t_bvh_eval;

typedef struct s_bvh_find
{
	struct s_mbvh		*bvh;
	struct s_mbvh_node	*node;
	int					first;
	int					count;
	struct s_bvh_split	*out;
	t_bvh_split			s;
}						t_bvh_find;

typedef struct s_bvh_try
{
	struct s_mbvh		*bvh;
	struct s_mbvh_node	*node;
	int					first;
	int					count;
	struct s_bvh_split	*split;
	int					*mid;
}						t_bvh_try;

typedef struct s_mesh_build_item
{
	t_aabb				bbox;
	t_vec3				centroid;
	int					index;
}						t_mesh_build_item;

typedef struct s_mbvh
{
	t_mesh				*mesh;
	t_mesh_build_item	*items;
	t_mbvh_node			*nodes;
	int					node_count;
}						t_mbvh;

typedef struct s_mesh
{
	/* Vertex-Centric Data (Model A) */
	t_vertex			*vertices;
	int					vertex_count;
	t_triangle			*triangles;
	int					tri_count;
	int					*indices;
	t_vertex			*edit_snap_verts;
	t_vec3				*edit_snap_norms;
	t_tri_precomp		*tri_cache;

	/* Array-Centric Data (Model B / GLB) */
	t_mesh_geom			geometry;
	t_mesh_geom			base_geometry;
	t_vec3				*normals;
	t_vec3				*base_normals;
	t_vec2				*uvs;
	struct s_bone		*skeleton;
	t_bone_weight		*weights;
	int					bone_count;
	t_mat4				*bone_matrices;

	/* Physics and Intersection (BVH) */
	struct s_mbvh_node	*bvh_nodes;
	int					*bvh_indices;
	int					bvh_node_count;
	struct s_collider	collider;
	int					mat_id;
	int					group_id;
	t_aabb				bbox;
	struct s_bvh		*bvh;
	char				*name;
	t_vec3				color;
	void				*extra;
	t_physics_body		phys;
	t_vec3				edit_snap_pivot;
	t_mat4				scene_mat;
	t_mat4				scene_rot_mat;
	bool				has_scene_transform;
	t_transform			transform;
	t_mat4				scene_transform;
}						t_mesh;

typedef struct s_skinned_mesh
{
	t_mesh				base;
	t_bone				*bones;
	int					bone_count;
	t_mat4				global_inverse;
	t_bone				*skeleton;
	t_mat4				*bone_matrices;
	int					vertex_count;
	t_vec3				*base_vertices;
	t_bone_weight		*weights;
}						t_skinned_mesh;

typedef struct s_mesh_resource
{
	int					mesh_count;
	int					mesh_cap;
	t_mesh				*meshes;
	int					group_count;
	int					group_cap;
	t_mesh_group		*groups;
	int					mat_count;
	int					mat_cap;
	struct s_material	*materials;
}						t_mesh_resource;

typedef struct s_mesh_info
{
	char				*path;
	t_transform			transform;
	t_vec3				color;
	t_vec3				emission;
}						t_mesh_info;

typedef struct s_mesh_init
{
	int					v_count;
	int					i_count;
	bool				has_normals;
	bool				has_uvs;
}						t_mesh_init;

typedef struct s_occ
{
	double				dist;
	int					top;
	int					stack[64];
}						t_occ;

typedef struct s_occ_child
{
	int					left_idx;
	int					right_idx;
	bool				hit_l;
	bool				hit_r;
	double				tl_min;
	double				tl_max;
	double				tr_min;
	double				tr_max;
}						t_occ_child;

typedef struct s_mesh_hit
{
	t_mesh				*mesh;
	const t_ray			*ray;
	struct s_hit		*hit;
	t_vec2				bary;
	double				t;
	int					tri;
}						t_mesh_hit;

typedef struct s_hit_calc
{
	t_mesh_hit			*in;
	int					*idx;
	t_vec3				v[3];
}						t_hit_calc;

typedef struct s_tri_hit
{
	t_vec3				e1;
	t_vec3				e2;
	t_vec3				tvec;
	t_vec3				pvec;
	t_vec3				qvec;
	double				det;
	double				inv_det;
	double				u;
	double				v;
}						t_tri_hit;

typedef struct s_leaf
{
	int					tri;
	double				t;
	t_vec2				uv;
}						t_leaf;

typedef struct s_child
{
	int					left_idx;
	int					right_idx;
	bool				hit_l;
	bool				hit_r;
	double				tl_min;
	double				tl_max;
	double				tr_min;
	double				tr_max;
}						t_child;

typedef struct s_fbx_bin_node
{
	uint64_t			end_offset;
	uint64_t			num_properties;
	uint64_t			property_list_len;
	uint8_t				name_len;
	char				name[1024];
}						t_fbx_bin_node;

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
	t_vertex			*vertices;
	t_triangle			*triangles;
	int					*v;
	int					vp;
	int					ps;
	int					use_v_n;
	int					use_v_u;
}						t_fbx_build;

typedef struct s_fbx_parse
{
	int					fd;
	bool				is_64;
	t_fbx_data			*d;
}						t_fbx_parse;

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

typedef struct s_fbx_bin
{
	int					fd;
	uint32_t			version;
	t_skinned_mesh		mesh;
	t_fbx_data			data;
}						t_fbx_bin;

typedef struct s_fbx_buf
{
	char				*buf;
	size_t				cap;
	size_t				len;
}						t_fbx_buf;

typedef struct s_fbx_ascii
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
}						t_fbx_ascii;

typedef struct s_fdf
{
	t_mesh				*mesh;
	int					dims[2];
	int					row;
}						t_fdf;

typedef struct s_fdf_dim
{
	int					w;
	int					h;
}						t_fdf_dim;

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

typedef struct s_extract
{
	char				*bin;
	t_accessor			*acc;
	t_buffer_view		*bv;
	void				*dst;
	int					dst_stride;
	int					ext_stride;
	int					elem_size;
	int					count;
}						t_extract;

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

typedef struct s_glb_mat
{
	t_mesh_resource	*out;
	void			*mlx_ptr;
	t_json_value	*json;
	char			*bin;
	int				mat_idx;
	int				*out_ids;
}	t_glb_mat;

typedef struct s_obj_face
{
	int					vi[32];
	int					vti[32];
	int					vni[32];
	int					count;
}						t_obj_face;

typedef struct s_obj
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
	t_vec2				*out_vt;
	t_vec3				*out_vn;
	size_t				out_v_count;
	size_t				out_v_cap;

	int					*out_i;
	size_t				out_i_count;
	size_t				out_i_cap;

	t_aabb				bbox;
	int					current_mat_id;
	int					first_mtl_id;
}						t_obj;


#endif
