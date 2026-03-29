/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   injection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 07:44:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 13:44:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"
#include "debug.h"

int	scene_add_material(t_scene *scene, const t_material *mat)
{
	if (!DYNARRAY_ENSURE_INT(&scene->materials, &scene->mat_count,
			&scene->mat_cap, sizeof(t_material)))
		return (-1);
	scene->materials[scene->mat_count] = *mat;
	if (mat->name)
		scene->materials[scene->mat_count].name = ft_strdup(mat->name);
	if (mat->name)
		DBG_INFO_MSG(DBG_CH_PARSER, "scene_add_material: '%s' slot=%d\n",
			mat->name, scene->mat_count);
	return (scene->mat_count++);
}

int	scene_add_material_from_color(t_scene *scene, t_vec3 color)
{
	t_material	m;

	DBG_TRACE_MSG(DBG_CH_PARSER, "scene_add_material_from_color: entry\n");
	ft_memset(&m, 0, sizeof(t_material));
	m.name = NULL;
	m.albedo_map.type = TEX_SOLID;
	m.albedo_map.color_a = color;
	m.specular = 0.3;
	m.shininess = 16.0;
	material_apply_preset(&m, color);
	return (scene_add_material(scene, &m));
}
