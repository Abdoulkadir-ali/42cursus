/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metadata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:08:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 17:08:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include <time.h>

/**
 * @brief Initializes metadata for a material.
 * Captures texture paths and original physical parameters for GUI resets.
 */
void	init_metadata_material(t_material_metadata *meta,
			const t_material *mat)
{
	if (!meta || !mat)
		return ;
	ft_memset(meta, 0, sizeof(t_material_metadata));
	if (mat->name)
		meta->name = ft_strdup(mat->name);
	if (mat->albedo_map.path)
		meta->albedo_path = ft_strdup(mat->albedo_map.path);
	if (mat->bump_map.path)
		meta->normal_path = ft_strdup(mat->bump_map.path);
	if (mat->roughness_map.path)
		meta->roughness_path = ft_strdup(mat->roughness_map.path);
	if (mat->metallic_map.path)
		meta->metallic_path = ft_strdup(mat->metallic_map.path);
	meta->orig_roughness = (float)mat->roughness;
	meta->orig_metallic = (float)mat->metallic;
	meta->orig_reflectivity = (float)mat->reflectivity;
	meta->orig_transparency = (float)mat->transparency;
	meta->orig_albedo = mat->albedo_map.color_a;
	meta->orig_emission = mat->emission;
	meta->import_time = time(NULL);
}
