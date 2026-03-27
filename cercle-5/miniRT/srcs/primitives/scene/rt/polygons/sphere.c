/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 00:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/**
 * @brief Dispatch parsing of a sphere to the object layer and add it to the scene.
 * Rule 2: Scene layer manages material resolution and addition.
 */
bool	parse_sphere(t_scene *scene, t_parser *p)
{
	t_parse_obj	parsed;

	parsed = rt_parse_sphere_obj(p);
	if (parsed.type != TYPE_SPHERE)
		return (false);
	/* Finalize: Scene manages materials */
	parsed.data.sphere.mat_id = scene_add_material(scene, 
			parsed.data.sphere.temp_color);
	if (parsed.data.sphere.mat_id < 0)
		return (false);
	return (scene_add_sphere(scene, parsed.data.sphere));
}
