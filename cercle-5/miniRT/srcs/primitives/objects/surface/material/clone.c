/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 18:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

int	scene_clone_material(t_scene *scene, int src_id)
{
	int	id;

	if ((size_t)src_id == (size_t)-1 || (size_t)src_id >= scene->mat_count)
		return (-1);
	id = scene_material_allocate_slot(scene);
	if (id < 0)
		return (-1);
	scene->materials[id] = scene->materials[src_id];
	if (scene->materials[src_id].name)
		scene->materials[id].name = ft_strdup(scene->materials[src_id].name);
	else
		scene->materials[id].name = NULL;
	return (id);
}
