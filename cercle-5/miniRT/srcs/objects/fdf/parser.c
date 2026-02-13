/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "raytracing.h"

/**
 * Main parser for FDF files. Converts heightmap to mesh.
 */
bool	parse_fdf(const char *path, t_scene *scene)
{
	t_mesh	mesh;
	int		v[4];

	if (!fdf_get_dimensions(path, &v[0], &v[1]))
		return (false);
	if (!fdf_init_mesh(&mesh, v[0] * v[1], (v[0] - 1) * (v[1] - 1) * 6, path))
		return (false);
	fdf_fill_data(path, &mesh, v[0], v[1]);
	fdf_compute_normals(&mesh, v[0], v[1]);
	fdf_compute_uvs(&mesh, v[0], v[1]);
	fdf_triangulate(&mesh, v[0], v[1]);
	mesh_build_bvh(&mesh);
	if (!scene_add_mesh(scene, mesh))
	{
		mesh_free(&mesh);
		return (false);
	}
	return (true);
}
