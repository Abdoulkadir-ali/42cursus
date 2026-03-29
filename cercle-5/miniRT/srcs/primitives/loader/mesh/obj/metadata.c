/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metadata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:11:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 17:11:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include <time.h>

/**
 * @brief Initializes metadata for a loaded OBJ asset.
 * Captures geometry statistics directly from the OBJ parser result.
 */
void	init_metadata_obj(t_mesh_asset_metadata *meta, t_obj *obj,
			const char *path)
{
	if (!meta || !obj)
		return ;
	ft_memset(meta, 0, sizeof(t_mesh_asset_metadata));
	meta->name = ft_strdup(path);
	meta->file_path = ft_strdup(path);
	meta->vertex_count = obj->out_v_count;
	meta->tri_count = obj->out_i_count / 3;
	meta->import_time = time(NULL);
}
