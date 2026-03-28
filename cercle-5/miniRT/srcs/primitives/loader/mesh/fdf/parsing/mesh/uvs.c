/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uvs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 07:38:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Generates UV coordinates for the FDF grid mesh.
 */
void	fdf_gen_uvs(t_fdf *f)
{
	size_t	i;

	f->mesh.uvs = malloc(sizeof(t_vec2) * f->mesh.vertex_count);
	if (f->mesh.uvs == NULL)
		return ;
	i = 0;
	while (i < f->mesh.vertex_count)
	{
		f->mesh.uvs[i].x = f->mesh.vertices[i].x / (double)f->width;
		f->mesh.uvs[i].y = f->mesh.vertices[i].z / (double)f->height;
		i++;
	}
}
