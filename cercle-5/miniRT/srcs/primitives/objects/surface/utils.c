/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 03:08:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 03:08:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions/primitives/objects/surface.h"
#include "scene.h"

static bool	mat_needs_uv(t_material *m)
{
	return (m->albedo_map.type != TEX_SOLID
		|| m->roughness_map.type != TEX_SOLID
		|| m->metallic_map.type != TEX_SOLID);
}

void	scene_init_uv_flags(t_scene *scene)
{
	size_t		i;
	t_material	*m;

	i = 0;
	while (i < scene->sphere_count)
	{
		m = &scene->materials[scene->spheres[i].mat_slots[
			scene->spheres[i].active_slot]];
		scene->spheres[i].needs_uv = mat_needs_uv(m);
		i++;
	}
	i = 0;
	while (i < scene->plane_count)
	{
		m = &scene->materials[scene->planes[i].mat_slots[
			scene->planes[i].active_slot]];
		scene->planes[i].needs_uv = mat_needs_uv(m);
		i++;
	}
}
