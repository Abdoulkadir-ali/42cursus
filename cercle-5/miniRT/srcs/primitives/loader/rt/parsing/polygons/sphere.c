/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 01:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Parses a sphere for the 100% DOD SoA primitive array.
 */
bool	parse_sphere(t_scene *scene, t_parser *p)
{
	t_primitive_array	data;
	t_vec3				color;
	float				diameter;

	ft_memset(&data, 0, sizeof(t_primitive_array));
	if (!parse_vec3(p, &data.positions[0]))
		return (false);
	diameter = (float)parse_double(p);
	if (!parse_vec3(p, &color))
		return (false);
	data.radii[0] = diameter / 2.0f;
	data.mat_ids[0] = (uint16_t)scene_add_material(scene, color);
	return (scene_add_primitive(scene, data, PRIM_SPHERE));
}
