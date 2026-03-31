/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_triangulate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_triangulate(t_mesh *mesh, int w, int h)
{
	int	tri;
	int	p[2];
	int	idx;

	tri = 0;
	p[1] = -1;
	while (++p[1] < h - 1)
	{
		p[0] = -1;
		while (++p[0] < w - 1)
		{
			idx = p[1] * w + p[0];
			mesh->triangles[tri].v[0] = idx;
			mesh->triangles[tri].v[1] = idx + w;
			mesh->triangles[tri].v[2] = idx + 1;
			tri++;
			mesh->triangles[tri].v[0] = idx + 1;
			mesh->triangles[tri].v[1] = idx + w;
			mesh->triangles[tri].v[2] = idx + w + 1;
			tri++;
		}
	}
}
