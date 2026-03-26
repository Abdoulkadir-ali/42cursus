/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 15:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	scene_add_mesh(t_scene *scene, t_mesh mesh)
{
	if (!DYNARRAY_ENSURE_INT(&scene->meshes, &scene->mesh_count,
			&scene->mesh_cap, sizeof(t_mesh)))
		return (false);
	if (vec3_mag_sq(mesh.transform.scale) < SCALE_EPSILON)
		mesh.transform.scale = vec3(1, 1, 1);
	scene->meshes[scene->mesh_count++] = mesh;
	return (true);
}
