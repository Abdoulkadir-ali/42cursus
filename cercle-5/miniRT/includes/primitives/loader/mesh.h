/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 04:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 07:52:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_LOADER_H
# define MESH_LOADER_H

# include "parser.h"
# include "scene.h"
# include "material.h"

/* --- Mesh initialization parameters --- */
typedef struct s_mesh_init
{
	int		v_count;
	int		i_count;
	bool	has_normals;
	bool	has_uvs;
}				t_mesh_init;

/**
 * @brief Unified dispatcher for non raytrace-native assets.
 * Handles format identification (OBJ, GLB, FBX, FDF) and scene injection.
 * Materials are created via scene_add_material() from material/inject.c
 */
bool	load_mesh_file(t_scene *scene, const char *path);
bool	mesh_load_from_file(t_mesh *mesh, const char *path);

/**
 * @brief Injected mesh loader for .rt scene file commands.
 * Applies transform/color/emission overrides to loaded meshes.
 */
bool	load_injected_mesh(t_scene *scene, const char *path,
			t_transform transform, t_vec3 color, t_vec3 emission);

/* --- Mesh lifecycle --- */
bool	mesh_init(t_mesh *mesh, t_mesh_init init);
void	init_mesh(t_mesh *mesh, const char *path);
void	mesh_free(t_mesh *mesh);

/* --- INJECTION --- */
bool	scene_add_mesh(t_scene *scene, t_mesh mesh);

#endif
