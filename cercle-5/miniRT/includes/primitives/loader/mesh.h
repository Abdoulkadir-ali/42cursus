/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 04:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 07:23:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_LOADER_H
# define MESH_LOADER_H

# include "parser.h"
# include "scene.h"
# include "material.h"


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

/* --- INJECTION --- */
bool	scene_add_mesh(t_scene *scene, t_mesh mesh);

#endif
