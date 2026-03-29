/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metadata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:07:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 17:07:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include <time.h>

/**
 * @brief Initializes metadata for a loaded GLB (Binary glTF) asset.
 * Summarizes all meshes contained within the GLB file.
 */
void	init_metadata_glb(t_mesh_asset_metadata *meta, t_glb *g,
			const char *path)
{
	int	i;

	if (!meta || !g)
		return ;
	ft_memset(meta, 0, sizeof(t_mesh_asset_metadata));
	meta->name = ft_strdup(path);
	meta->file_path = ft_strdup(path);
	i = 0;
	while (i < g->mesh_count)
	{
		meta->vertex_count += g->meshes[i].vertex_count;
		meta->tri_count += g->meshes[i].tri_count;
		i++;
	}
	meta->bone_count = 0; // GLB skeletons handled in skeletal parser
	meta->anim_count = g->anim_count;
	meta->import_time = time(NULL);
}
