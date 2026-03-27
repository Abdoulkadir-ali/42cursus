/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 02:05:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Parses a cylinder for the 100% DOD SoA primitive array.
 */
bool	parse_cylinder(t_scene *scene, t_parser *p)
{
	t_primitive_array	data;
	t_vec3				color;

	ft_memset(&data, 0, sizeof(t_primitive_array));
	if (!parse_vec3(p, &data.positions[0]))
		return (false);
	if (!parse_vec3(p, &data.axes[0]))
		return (false);
	data.radii[0] = (float)parse_double(p) / 2.0f;
	data.heights[0] = (float)parse_double(p);
	if (!parse_vec3(p, &color))
		return (false);
	data.axes[0] = vec3_norm(data.axes[0]);
	data.mat_ids[0] = (uint16_t)scene_add_material(scene, color);
	return (scene_add_primitive(scene, data, PRIM_CYLINDER));
}
