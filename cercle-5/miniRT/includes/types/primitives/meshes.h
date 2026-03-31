/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meshes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:23:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/31 09:50:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_PRIMITIVES_MESHES_H
# define TYPES_PRIMITIVES_MESHES_H

# include "maths.h"

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

typedef struct s_mesh_geom
{
	t_vec3				*vertices;
	t_vec3				*normals;
	t_vec2				*uvs;
	int					vertex_count;
}						t_mesh_geom;

typedef struct s_mesh
{
	/* Vertex-Centric Data (Model A) */
	t_vertex			*vertices;
	int					vertex_count;
	t_triangle			*triangles;
	int					tri_count;

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

	/* Shared Data */
	int					mat_id;
	t_aabb				bbox;
	struct s_bvh		*bvh;
	char				*name;
	t_vec3				color;
	void				*extra;
}						t_mesh;

typedef struct s_mesh_group
{
	int					mesh_start;
	int					mesh_count;
	char				*name;
	t_transform			transform;
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

/* Parsing State Types (Moving from functions/ to types/) */
typedef struct s_obj			t_obj;
typedef struct s_fbx_ascii		t_fbx_ascii;
typedef struct s_fbx_bin		t_fbx_bin;

#endif
