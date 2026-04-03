/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:33:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_index	scene_clone_material(t_scene *scene, size_t src_id)
{
	t_index	id;

	if (src_id >= scene->mat_count)
		return (index_error());
	id = scene_material_allocate_slot(scene);
	if (id.error)
		return (index_error());
	scene->materials[id.i] = scene->materials[src_id];
	if (scene->materials[src_id].name)
		scene->materials[id.i].name = ft_strdup(scene->materials[src_id].name);
	else
		scene->materials[id.i].name = NULL;
	return (id);
}