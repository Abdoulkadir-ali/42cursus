/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 01:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

# include "objects/objects.h"
# include "objects/mesh.h"

typedef struct s_ray	t_ray;
typedef struct s_hit	t_hit;

typedef struct s_mesh_build_item
{
	int index; // Triangle index
	t_aabb			bbox;
	t_vec3			centroid;
}					t_mesh_build_item;

/* Prototypes */
bool	parse_obj(const char *path, t_scene *scene);
void	mesh_build_bvh(t_mesh *mesh);

#endif
