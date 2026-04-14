/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_meshes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:23:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 01:27:56 by abdoali          ###   ########.fr       */
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
	size_t				bone_ids[4];
	float				bone_weights[4];
}						t_vertex;

typedef struct s_triangle
{
	size_t				v[3];
}						t_triangle;

typedef struct s_bone_weight
{
	size_t				bone_indices[4];
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
	size_t				*indices;
	size_t				vertex_count;
	size_t				tri_count;
	size_t				index_count;
}						t_mesh_geom;

typedef struct s_mesh_group
{
	size_t				mesh_start;
	size_t				mesh_count;
	size_t				start;
	size_t				sub_count;
	t_vec3				pivot;
	char				*name;
	char				*path;
	t_transform			transform;
	t_physics_body		phys;
}						t_mesh_group;

typedef struct s_bone
{
	char				*name;
	t_index				parent;
	size_t				node_idx;
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
	size_t				left_or_first;
	size_t				count;
	size_t				axis;
	size_t				depth;
}						t_mbvh_node;

typedef struct s_bin
{
	t_aabb				bounds;
	size_t				count;
}						t_bin;

typedef struct s_bvh_bins
{
	struct s_mbvh		*bvh;
	size_t				first;
	size_t				count;
	size_t				axis;
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
	size_t				left_counts[BVH_BINS];
	size_t				axis;
	double				pos;
	double				best_cost;
	size_t				i;
	double				split_pos;
	size_t				right_count;
	t_aabb				right_box;
	t_index				best_axis;
}						t_bvh_split;

typedef struct s_bvh_eval
{
	struct s_mbvh		*bvh;
	struct s_mbvh_node	*node;
	struct s_bvh_split	*s;
	size_t				first;
	size_t				count;
	size_t				axis;
}						t_bvh_eval;

typedef struct s_bvh_find
{
	struct s_mbvh		*bvh;
	struct s_mbvh_node	*node;
	size_t				first;
	size_t				count;
	struct s_bvh_split	*out;
	t_bvh_split			s;
}						t_bvh_find;

typedef struct s_bvh_try
{
	struct s_mbvh		*bvh;
	struct s_mbvh_node	*node;
	size_t				first;
	size_t				count;
	struct s_bvh_split	*split;
	size_t				*mid;
	bool				*error;
}						t_bvh_try;

typedef struct s_mesh_build_item
{
	t_aabb				bbox;
	t_vec3				centroid;
	size_t				index;
}						t_mesh_build_item;

typedef struct s_mbvh
{
	t_mesh				*mesh;
	t_mesh_build_item	*items;
	t_mbvh_node			*nodes;
	size_t				node_count;
	size_t				max_depth;
}						t_mbvh;

typedef struct s_mesh_anim
{
	t_index	idx;
	double	time;
	double	speed;
	bool	looping;
	bool	paused;
}						t_mesh_anim;

typedef struct s_mesh
{
	/* Vertex-Centric Data (Model A) */
	t_vertex			*vertices;
	size_t				vertex_count;
	t_triangle			*triangles;
	size_t				tri_count;
	size_t				*indices;
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
	size_t				bone_count;
	t_mat4				*bone_matrices;
	t_mesh_anim			anim;

	/* Physics and Intersection (BVH) */
	struct s_mbvh_node	*bvh_nodes;
	size_t				*bvh_indices;
	size_t				bvh_node_count;
	struct s_collider	collider;
	size_t				mat_id;
	size_t				mat_slots[4];
	int					active_slot;
	bool					is_fdf;
	t_index					group_id;
	t_aabb				bbox;
	struct s_bvh		*bvh;
	char				*name;
	t_index				node_idx;
	t_mat4				node_transform;
	t_vec3				color;
	void				*extra;
	t_physics_body		phys;
	t_vec3				edit_snap_pivot;
	t_mat4				scene_mat;
	t_mat4				scene_rot_mat;
	bool				has_scene_transform;
	bool				bvh_dirty;
	t_transform			transform;
	t_mat4				scene_transform;
}						t_mesh;

typedef struct s_skinned_mesh
{
	t_mesh				base;
	t_bone				*bones;
	size_t				bone_count;
	t_mat4				global_inverse;
	t_bone				*skeleton;
	t_mat4				*bone_matrices;
	size_t				vertex_count;
	t_vec3				*base_vertices;
	t_bone_weight		*weights;
}						t_skinned_mesh;

typedef struct s_mesh_resource
{
	size_t				mesh_count;
	size_t				mesh_cap;
	t_mesh				*meshes;
	size_t				group_count;
	size_t				group_cap;
	t_mesh_group		*groups;
	size_t				mat_count;
	size_t				mat_cap;
	struct s_material	*materials;
	size_t				clip_count;
	size_t				clip_cap;
	struct s_animation	*clips;
	size_t				anim_count;
	size_t				anim_cap;
	t_skinned_mesh		*animated;
}						t_mesh_resource;

typedef struct s_mesh_info
{
	char				*path;
	t_transform			transform;
	t_vec3				color;
	t_vec3				emission;
	double				sb_stiffness;
	double				sb_damping;
}						t_mesh_info;

typedef struct s_mesh_init
{
	size_t				v_count;
	size_t				i_count;
	bool				has_normals;
	bool				has_uvs;
}						t_mesh_init;

typedef struct s_occ
{
	double				dist;
	size_t				top;
	size_t				stack[64];
	bool				occluded;
}						t_occ;

typedef struct s_occ_child
{
	size_t				left_idx;
	size_t				right_idx;
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
	size_t				tri;
}						t_mesh_hit;

typedef struct s_hit_calc
{
	t_mesh_hit			*in;
	size_t				*idx;
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
	size_t				tri;
	double				t;
	t_vec2				uv;
}						t_leaf;

typedef struct s_child
{
	size_t				left_idx;
	size_t				right_idx;
	bool				hit_l;
	bool				hit_r;
	double				tl_min;
	double				tl_max;
	double				tr_min;
	double				tr_max;
}						t_child;

typedef struct s_fbx_bin_node
{
	size_t			end_offset;
	size_t			num_properties;
	size_t			property_list_len;
	uint8_t				name_len;
	char				name[1024];
}						t_fbx_bin_node;

typedef enum e_fbx_type
{
	FBX_TYPE_VERTICES = 0,
	FBX_TYPE_INDICES = 1,
	FBX_TYPE_NORMALS = 2,
	FBX_TYPE_UVS = 3
}	t_fbx_type;

typedef struct s_fbx_data
{
	t_vec3				*v;
	t_vec3				*vn;
	t_vec2				*vu;
	int					*ri;
	t_vec2s				rv;			/* x=rc (raw index count), y=vc (vertex count) */
	t_vec2s				nu;			/* x=nc (normal count),    y=uc (uv count)     */
}						t_fbx_data;

typedef struct s_fbx_flat_params
{
	int					*raw;
	t_vec3				*n;
	t_vec2				*u;
	t_vec2s				rv;			/* x=raw_c (raw index count), y=vc (vertex count) */
	t_vec2s				nu;			/* x=nc (normal count),       y=uc (uv count)     */
}						t_fbx_flat_params;

typedef struct s_fbx_build
{
	t_mesh				*m;
	int					*raw;
	t_vec3				*n;
	t_vec2				*u;
	t_vertex			*vertices;
	t_triangle			*triangles;
	size_t				*v;
	size_t				tc;
	t_vec2s				rv;			/* x=raw_c (raw index count), y=vc (vertex count) */
	t_vec2s				nu;			/* x=nc (normal count),       y=uc (uv count)     */
	t_vec2s				cur;		/* x=vp (output vertex pos),  y=ps (parse pos)   */
	bool				use_v_n;
	bool				use_v_u;
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
	size_t			*count;
	size_t				elem_sz;
	size_t			div;
}						t_fbx_array_req;

typedef struct s_fbx_array
{
	size_t			arr_len;
	size_t			encoding;
	size_t			comp_len;
	size_t				actual_sz;
	char				type;
}						t_fbx_array;

typedef struct s_fbx_bin
{
	int					fd;
	size_t			version;
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
	t_vec2s				rv;			/* x=rc (raw index count), y=vc (vertex count) */
	t_vec2s				nu;			/* x=nc (normal count),    y=uc (uv count)     */
	char				*buf;
	char				*p;
	char				*end;
	size_t				buf_size;
	t_index				mat_id;
	const char			*path;
}						t_fbx_ascii;

/* Removed redundant t_fdf and t_fdf_dim definitions - use t_fdf.h */

typedef struct s_glb_header
{
	size_t			magic;
	size_t			version;
	size_t			length;
}						t_glb_header;

typedef struct s_chunk_header
{
	size_t			length;
	size_t			type;
}						t_chunk_header;

typedef struct s_accessor
{
	size_t				buffer_view;
	size_t				byte_offset;
	int					component_type;
	size_t				count;
	char				type[16];
}						t_accessor;

typedef struct s_buffer_view
{
	size_t				buffer;
	size_t				byte_offset;
	size_t				byte_length;
	size_t				byte_stride;
}						t_buffer_view;

typedef struct s_extract
{
	char				*bin;
	t_accessor			*acc;
	t_buffer_view		*bv;
	void				*dst;
	size_t				dst_stride;
	size_t				ext_stride;
	size_t				elem_size;
	size_t				count;
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
	size_t				count;
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
	size_t				node_idx;
	t_anim_path			path;
	size_t				sampler_idx;
}						t_anim_channel;

typedef struct s_animation
{
	char				*name;
	t_anim_channel		*channels;
	size_t				channel_count;
	t_anim_sampler		*samplers;
	size_t				sampler_count;
	double				max_time;
	double				current_time;
}						t_animation;

typedef struct s_obj_face
{
	int					vi[32];
	int					vti[32];
	int					vni[32];
	size_t				count;
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

	size_t				*out_i;
	size_t				out_i_count;
	size_t				out_i_cap;

	t_aabb				bbox;
	t_index				current_mat_id;
	t_index				first_mtl_id;
}						t_obj;


#endif
