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

typedef struct s_scene	t_scene;

# include "objects/mesh.h"

typedef struct s_bone
{
	char	*name;
	int		parent;
	t_mat4	local_transform;
}				t_bone;

typedef struct s_skinned_mesh
{
	t_mesh	base;           // INHERITANCE: Re-use all mesh intersection code!
	t_bone	*skeleton;      // The hierarchy of bones
	t_mat4	*bone_matrices; // The current pose transformations
	int		bone_count;
}				t_skinned_mesh;

# include "libft.h"

/* .fbx specific parsing prototypes */
bool	parse_fbx(const char *path, t_scene *scene);

#endif
