/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangulate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 23:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Generates 3D vertices from the FDF height grid.
 */
static void	set_v(t_fdf *f)
{
	int		y;
	int		x;
	int		idx;

	y = 0;
	while (y < f->height)
	{
		x = 0;
		while (x < f->width)
		{
			idx = y * f->width + x;
			f->mesh.vertices[idx].x = (double)x;
			f->mesh.vertices[idx].y = f->grid[idx];
			f->mesh.vertices[idx].z = (double)y;
			f->mesh.vertices[idx].w = 1.0;
			x++;
		}
		y++;
	}
}

/**
 * @brief Builds triangle indices for the FDF grid mesh.
 */
static void	set_i(t_fdf *f)
{
	int	y;
	int	x;
	int	idx;
	int	ii;

	y = 0;
	ii = 0;
	while (y < f->height - 1)
	{
		x = 0;
		while (x < f->width - 1)
		{
			idx = y * f->width + x;
			f->mesh.indices[ii++] = idx;
			f->mesh.indices[ii++] = idx + f->width;
			f->mesh.indices[ii++] = idx + 1;
			f->mesh.indices[ii++] = idx + 1;
			f->mesh.indices[ii++] = idx + f->width;
			f->mesh.indices[ii++] = idx + f->width + 1;
			x++;
		}
		y++;
	}
}

/**
 * @brief Orchestrates FDF grid triangulation into a t_mesh.
 */
bool	fdf_triangulate(t_fdf *f)
{
	f->mesh.vertex_count = f->width * f->height;
	f->mesh.tri_count = (f->width - 1) * (f->height - 1) * 2;
	f->mesh.vertices = malloc(sizeof(t_vec3) * f->mesh.vertex_count);
	f->mesh.indices = malloc(sizeof(int) * f->mesh.tri_count * 3);
	if (f->mesh.vertices == NULL || f->mesh.indices == NULL)
	{
		if (f->mesh.vertices != NULL)
			free(f->mesh.vertices);
		if (f->mesh.indices != NULL)
			free(f->mesh.indices);
		return (false);
	}
	set_v(f);
	set_i(f);
	f->mesh.name = ft_strdup(f->path);
	return (true);
}
