/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_normals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

static t_vec3	fdf_vertex_normal(t_mesh *mesh, int x, int z, t_fdf_dim dim)
{
	int		idx;
	t_vec3	v[4];

	idx = z * dim.w + x;
	v[0] = mesh->vertices[idx];
	if (x > 0)
		v[0] = mesh->vertices[idx - 1];
	v[1] = mesh->vertices[idx];
	if (x < dim.w - 1)
		v[1] = mesh->vertices[idx + 1];
	v[2] = mesh->vertices[idx];
	if (z > 0)
		v[2] = mesh->vertices[idx - dim.w];
	v[3] = mesh->vertices[idx];
	if (z < dim.h - 1)
		v[3] = mesh->vertices[idx + dim.w];
	return (vec3_norm(vec3(v[0].y - v[1].y, 2.0, v[2].y - v[3].y)));
}

void	fdf_compute_normals(t_mesh *mesh, int w, int h)
{
	int	x;
	int	z;
	int	idx;

	z = -1;
	while (++z < h)
	{
		x = -1;
		while (++x < w)
		{
			idx = z * w + x;
			mesh->normals[idx] = fdf_vertex_normal(mesh, x, z, (t_fdf_dim){w,
					h});
		}
	}
}
