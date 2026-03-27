/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 08:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

bool	fdf_load(const char *path, t_raw_model *out)
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
	out->meshes = malloc(sizeof(t_mesh));
	if (out->meshes)
	{
		out->meshes[0] = mesh;
		out->mesh_count = 1;
	}
	return (out->mesh_count > 0);
}
