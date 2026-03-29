/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metadata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 17:05:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include <time.h>

/**
 * @brief Initializes metadata for a loaded FBX asset.
 * Fills the cold t_mesh_asset_metadata structure with info from the FBX loader.
 */
void	init_metadata_fbx(t_mesh_asset_metadata *meta, t_fbx *f,
			const char *path)
{
	if (!meta || !f)
		return ;
	ft_memset(meta, 0, sizeof(t_mesh_asset_metadata));
	meta->name = ft_strdup(path); // Default to path, can be refined later
	meta->file_path = ft_strdup(path);
	meta->vertex_count = f->vc;
	meta->tri_count = f->rc / 3;
	meta->bone_count = 0; // To be filled by skeletal parser if applicable
	meta->anim_count = f->anim_count;
	meta->import_time = time(NULL);
}
