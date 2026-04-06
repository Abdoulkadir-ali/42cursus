/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mesh_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	fdf_init_mesh(t_mesh *mesh, size_t v_count, size_t i_count, const char *p)
{
	ft_memset(mesh, 0, sizeof(t_mesh));
	mesh->vertices = ft_calloc(v_count, sizeof(t_vertex));
	mesh->indices = ft_calloc(i_count, sizeof(unsigned int));
	if (!mesh->vertices || !mesh->indices)
	{
		mesh_free(mesh);
		return (false);
	}
	mesh->name = ft_strdup(p);
	mesh->vertex_count = v_count;
	mesh->tri_count = i_count / 3;
	return (true);
}
