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
	t_sphere	sphere;
	t_vec3		color;
	double		diameter;

	ft_memset(&sphere, 0, sizeof(t_sphere));
	if (!parse_vec3(p, &sphere.transform.pos))
		return (false);
	diameter = parse_double(p);
	if (!parse_vec3(p, &color))
		return (false);
	sphere.radius = diameter / 2.0;
	sphere.radius_sq = sphere.radius * sphere.radius;
	sphere.mat_id = scene_add_material(scene, color);
	if (sphere.mat_id < 0)
		return (false);
	return (scene_add_sphere(scene, sphere));
}
