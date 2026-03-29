/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metadata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:06:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 17:06:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include <time.h>

/**
 * @brief Initializes metadata for a loaded FDF (Heightmap) asset.
 */
void	init_metadata_fdf(t_mesh_asset_metadata *meta, t_fdf *f,
			const char *path)
{
	if (!meta || !f)
		return ;
	ft_memset(meta, 0, sizeof(t_mesh_asset_metadata));
	meta->name = ft_strdup(path);
	meta->file_path = ft_strdup(path);
	meta->vertex_count = f->mesh.vertex_count;
	meta->tri_count = f->mesh.tri_count;
	meta->grid_w = f->width;
	meta->grid_h = f->height;
	meta->import_time = time(NULL);
}
