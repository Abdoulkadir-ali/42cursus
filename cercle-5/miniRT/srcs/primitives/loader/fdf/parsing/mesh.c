/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mesh_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 20:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

bool	fdf_init_mesh(t_mesh *mesh, int v_count, int i_count, const char *p)
{
	t_mesh_init	init;

	init.v_count = v_count;
	init.i_count = i_count;
	init.has_normals = true;
	init.has_uvs = true;
	if (!mesh_init(mesh, init))
		return (false);
	mesh->name = ft_strdup(p);
	return (true);
}
