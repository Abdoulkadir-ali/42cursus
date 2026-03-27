/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 23:05:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Approximates the normal of an FDF grid vertex using neighbor slopes.
 */
static t_vec3	get_n(t_fdf *f, int x, int z)
{
	t_vec3	v[4];
	int		idx;

	idx = z * f->width + x;
	v[0] = f->mesh.vertices[idx];
	if (x > 0)
		v[0] = f->mesh.vertices[idx - 1];
	v[1] = f->mesh.vertices[idx];
	if (x < f->width - 1)
		v[1] = f->mesh.vertices[idx + 1];
	v[2] = f->mesh.vertices[idx];
	if (z > 0)
		v[2] = f->mesh.vertices[idx - f->width];
	v[3] = f->mesh.vertices[idx];
	if (z < f->height - 1)
		v[3] = f->mesh.vertices[idx + f->width];
	return (vec3_norm(vec3(v[0].y - v[1].y, 2.0, v[2].y - v[3].y)));
}

/**
 * @brief Computes all vertex normals for the FDF grid mesh.
 */
void	fdf_compute_normals(t_fdf *f)
{
	int	x;
	int	z;
	int	idx;

	f->mesh.normals = malloc(sizeof(t_vec3) * f->mesh.vertex_count);
	if (f->mesh.normals == NULL)
		return ;
	z = 0;
	while (z < f->height)
	{
		x = 0;
		while (x < f->width)
		{
			idx = z * f->width + x;
			f->mesh.normals[idx] = get_n(f, x, z);
			x++;
		}
		z++;
	}
}
