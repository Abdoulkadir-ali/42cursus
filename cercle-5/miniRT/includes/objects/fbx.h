/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/07 21:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FBX_H
# define FBX_H

# include "libft.h"
# include "objects/mesh.h"
# include <fcntl.h>

typedef struct s_scene t_scene;

typedef struct s_bone_weight
{
	int		bone_ids[4];
	double	weights[4];
}			t_bone_weight;

typedef struct s_bone
{
	char	*name;
	int		parent;
	t_mat4	local_transform;
	t_mat4	bind_pose;
	t_mat4	inv_bind_pose;
}			t_bone;

typedef struct s_skinned_mesh
{
	t_mesh base;            // INHERITANCE: Re-use all mesh intersection code!
	t_vec3 *base_vertices;  // Original un-posed vertices
	t_bone *skeleton;       // The hierarchy of bones
	t_mat4 *bone_matrices;  // The current pose transformations (Global Space)
	t_bone_weight *weights; // Per-vertex weights
	t_transform transform;  // Object space -> World space
	int		bone_count;
	int vertex_count; // Count of vertices in 'base' affected by skinning
}			t_skinned_mesh;

/* .fbx specific parsing prototypes */
bool		parse_fbx_ascii(const char *path, t_scene *scene);
bool		parse_fbx_binary(const char *path, t_scene *scene);
bool		parse_fbx(const char *path, t_scene *scene);

#endif
