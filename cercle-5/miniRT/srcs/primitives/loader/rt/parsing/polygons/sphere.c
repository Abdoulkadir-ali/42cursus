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
	t_prim_params	params;
	t_vec3			color;

	ft_memset(&params, 0, sizeof(t_prim_params));
	if (!parse_vec3(p, &params.pos))
		return (false);
	params.radius = (float)parse_double(p) / 2.0f;
	if (!parse_vec3(p, &color))
		return (false);
	params.mat_id = scene_add_material(scene, color);
	return (scene_add_primitive(scene, params, PRIM_SPHERE));
}
