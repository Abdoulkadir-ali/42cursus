/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:45:12 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 23:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief DOD Injection of the generated FDF mesh into the scene.
 */
static bool	scene_add_fdf(t_scene *scene, t_fdf *fdf)
{
	if (fdf->mesh.vertex_count > 0)
	{
		scene_add_mesh(scene, fdf->mesh);
		return (true);
	}
	return (false);
}

/**
 * @brief FDF parsing pipeline: Single-pass Grid extraction -> Triangulation.
 * Relies entirely on the parser without manual seeking.
 */
bool	parse_fdf(t_scene *scene, t_parser *p)
{
	t_fdf	fdf;
	bool	res;

	ft_memset(&fdf, 0, sizeof(t_fdf));
	fdf.path = p->path;
	if (fdf_parse_grid_single_pass(&fdf, p) == false)
		return (false);
	if (fdf_triangulate(&fdf) == false)
	{
		if (fdf.grid != NULL)
			free(fdf.grid);
		return (false);
	}
	fdf_compute_normals(&fdf);
	fdf_gen_uvs(&fdf);
	res = scene_add_fdf(scene, &fdf);
	if (fdf.grid != NULL)
		free(fdf.grid);
	return (res);
}
