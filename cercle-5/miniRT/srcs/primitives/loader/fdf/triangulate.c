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

#include "loader.h"

void	fdf_triangulate(t_mesh *mesh, int w, int h)
{
	int	p[4];
	int	idx;

	p[3] = 0;
	p[1] = -1;
	while (++p[1] < h - 1)
	{
		p[0] = -1;
		while (++p[0] < w - 1)
		{
			idx = p[1] * w + p[0];
			mesh->indices[p[3]++] = idx;
			mesh->indices[p[3]++] = idx + w;
			mesh->indices[p[3]++] = idx + 1;
			mesh->indices[p[3]++] = idx + 1;
			mesh->indices[p[3]++] = idx + w;
			mesh->indices[p[3]++] = idx + w + 1;
		}
	}
}
