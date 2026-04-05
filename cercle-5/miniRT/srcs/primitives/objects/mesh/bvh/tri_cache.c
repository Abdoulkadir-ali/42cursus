/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_cache.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 12:33:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

void	mesh_build_tri_cache(t_mesh *mesh)
{
	size_t			i;
	size_t			*idx;
	t_tri_precomp	*tc;

	if (mesh->tri_cache)
		free(mesh->tri_cache);
	mesh->tri_cache = malloc(sizeof(t_tri_precomp) * mesh->tri_count);
	if (!mesh->tri_cache)
		return ;
	i = 0;
	while (i < mesh->tri_count)
	{
		tc = &mesh->tri_cache[i];
		idx = &mesh->bvh_indices[i * 3];
		tc->v0 = mesh->vertices[idx[0]].pos;
		tc->e1 = vec3_sub(mesh->vertices[idx[1]].pos, tc->v0);
		tc->e2 = vec3_sub(mesh->vertices[idx[2]].pos, tc->v0);
		i++;
	}
}
