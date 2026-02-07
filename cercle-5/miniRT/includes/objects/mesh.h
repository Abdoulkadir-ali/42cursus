/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 20:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/07 21:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
# define MESH_H

# include "maths.h"

// Forward declaration of BVH for internal mesh optimization
struct s_bvh;

typedef struct s_vertex
{
	t_vec3	pos;
	t_vec3	normal;
	t_vec2	uv;
}				t_vertex;

typedef struct s_triangle
{
	int		indices[3];
}				t_triangle;

typedef struct s_mesh
{
	char			*name;
	t_vec3			*vertices;
	t_vec3			*normals;
	t_vec2			*uvs;
	int				*indices;
	int				tri_count;
	t_aabb			bbox;
	struct s_bvh	*internal_bvh;
	int				mat_id;
}				t_mesh;

#endif
