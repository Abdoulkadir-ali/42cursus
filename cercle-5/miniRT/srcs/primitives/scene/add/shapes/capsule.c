/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 15:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	scene_add_capsule(t_scene *scene, t_capsule cap)
{
	int	mat_id;

	mat_id = scene_add_material(scene, cap.temp_color);
	if (mat_id < 0)
		return (false);
	cap.mat_id = mat_id;
	if (!DYNARRAY_ENSURE_INT(&scene->capsules, &scene->capsule_count,
			&scene->capsule_cap, sizeof(t_capsule)))
		return (false);
	scene->capsules[scene->capsule_count++] = cap;
	return (true);
}
