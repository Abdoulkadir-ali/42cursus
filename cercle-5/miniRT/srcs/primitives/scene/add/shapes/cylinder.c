/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 13:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	scene_add_cylinder(t_scene *scene, t_cylinder cylinder)
{
	if (!DYNARRAY_ENSURE_INT(&scene->cylinders, &scene->cylinder_count,
			&scene->cylinder_cap, sizeof(t_cylinder)))
		return (false);
	if (vec3_mag_sq(cylinder.transform.scale) < SCALE_EPSILON)
		cylinder.transform.scale = vec3(1, 1, 1);
	scene->cylinders[scene->cylinder_count++] = cylinder;
	return (true);
}
