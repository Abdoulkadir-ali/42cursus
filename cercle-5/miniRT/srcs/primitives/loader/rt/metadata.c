/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metadata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 17:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include <time.h>

/**
 * @brief Initializes metadata for analytical primitive shapes (Sphere, Box, etc.).
 * Captures the original parameters from the RT shape description.
 */
void	init_metadata_shape(t_primitive_metadata *meta,
			t_rt_shape *shape)
{
	if (!meta || !shape)
		return ;
	ft_memset(meta, 0, sizeof(t_primitive_metadata));
	meta->name = ft_strdup("Primitive"); // Placeholder, usually overridden by GUI
	meta->file_path = NULL; // Analytical shapes don't have file paths
	meta->orig_px = (float)shape->params.pos.x;
	meta->orig_py = (float)shape->params.pos.y;
	meta->orig_pz = (float)shape->params.pos.z;
	meta->orig_ax = (float)shape->params.axis.x;
	meta->orig_ay = (float)shape->params.axis.y;
	meta->orig_az = (float)shape->params.axis.z;
	meta->orig_radii = (float)shape->params.radius;
	meta->orig_heights = (float)shape->params.height;
	meta->import_time = time(NULL);
}
