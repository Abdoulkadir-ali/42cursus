/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_uvs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_compute_uvs(t_mesh *mesh, int w, int h)
{
	int	i;

	i = 0;
	while (i < w * h)
	{
		mesh->vertices[i].uv.x = (mesh->vertices[i].pos.x + w / 2.0) / (double)w;
		mesh->vertices[i].uv.y = (mesh->vertices[i].pos.z + h / 2.0) / (double)h;
		i++;
	}
}
