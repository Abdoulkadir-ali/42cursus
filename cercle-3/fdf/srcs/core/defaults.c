/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:24:22 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 15:36:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	init_defaults(t_data *data)
{
	data->graphics->render_config.render_mode = RENDER_LINES;
	data->graphics->render_config.lod_level = DEFAULT_LOD_LEVEL;
	data->graphics->render_config.use_depth_culling = 0;
	data->graphics->render_config.fill_triangles = 1;
}