/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_cache.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:26:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	mesh_build_tri_cache(t_mesh *mesh)
{
	int				i;
	int				*idx;
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
		tc->v0 = mesh->vertices[idx[0]];
		tc->e1 = vec3_sub(mesh->vertices[idx[1]], tc->v0);
		tc->e2 = vec3_sub(mesh->vertices[idx[2]], tc->v0);
		i++;
	}
}
