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

bool	fdf_init_mesh(t_mesh *mesh, int v_count, int i_count, const char *p)
{
	ft_memset(mesh, 0, sizeof(t_mesh));
	mesh->vertices = ft_calloc(v_count, sizeof(t_vec3));
	mesh->normals = ft_calloc(v_count, sizeof(t_vec3));
	mesh->uvs = ft_calloc(v_count, sizeof(t_vec2));
	mesh->indices = ft_calloc(i_count, sizeof(int));
	if (!mesh->vertices || !mesh->normals || !mesh->uvs || !mesh->indices)
	{
		mesh_free(mesh);
		return (false);
	}
	mesh->name = ft_strdup(p);
	mesh->tri_count = i_count / 3;
	return (true);
}
