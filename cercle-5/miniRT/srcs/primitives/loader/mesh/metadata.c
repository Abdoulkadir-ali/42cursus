/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metadata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 17:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include <time.h>

/**
 * @brief Initializes base metadata for a generic mesh asset.
 */
void	init_metadata_mesh_asset(t_mesh_asset_metadata *meta, const char *name,
			const char *path)
{
	if (!meta)
		return ;
	ft_memset(meta, 0, sizeof(t_mesh_asset_metadata));
	if (name)
		meta->name = ft_strdup(name);
	if (path)
		meta->file_path = ft_strdup(path);
	meta->import_time = time(NULL);
}

/**
 * @brief Initializes metadata for a specific mesh instance placed in the scene.
 * Captures the original transform from the hot SoA t_mesh structure.
 */
void	init_metadata_mesh_instance(t_mesh_instance_metadata *meta,
			t_mesh *instance, const char *name)
{
	if (!meta || !instance)
		return ;
	ft_memset(meta, 0, sizeof(t_mesh_instance_metadata));
	if (name)
		meta->name = ft_strdup(name);
	meta->orig_transform = mat4_transform(instance->transform);
	meta->asset_id = instance->asset_id;
	meta->import_time = time(NULL);
}
