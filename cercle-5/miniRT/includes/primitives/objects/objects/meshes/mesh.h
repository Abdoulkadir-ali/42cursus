/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:15:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
# define MESH_H

# include "surface.h"

typedef struct s_mesh			t_mesh;
typedef struct s_mesh_group		t_mesh_group;
typedef struct s_mesh_resource	t_mesh_resource;
typedef struct s_bone			t_bone;
typedef struct s_skinned_mesh	t_skinned_mesh;
typedef struct s_vertex			t_vertex;
typedef struct s_triangle		t_triangle;

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

typedef struct s_mesh
{
	t_vertex			*vertices;
	int					vertex_count;
	t_triangle			*triangles;
	int					triangle_count;
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
	int					parent_idx;
	t_mat4				offset_matrix;
	t_mat4				transform;
}						t_bone;

typedef struct s_skinned_mesh
{
	t_mesh				base;
	t_bone				*bones;
	int					bone_count;
	t_mat4				global_inverse;
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
	t_material			*materials;
}						t_mesh_resource;

/* Resource Factory (srcs/objects/meshes/resource.c) */
bool					mesh_resource_add_mesh(t_mesh_resource *res,
							t_mesh mesh);
int						mesh_resource_add_material(t_mesh_resource *res,
							const char *name);
void					mesh_resource_init(t_mesh_resource *res);
void					mesh_resource_free(t_mesh_resource *res);

#endif
