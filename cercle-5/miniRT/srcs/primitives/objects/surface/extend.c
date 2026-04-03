/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:19:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_index	scene_material_allocate_slot(t_scene *scene)
{
	if (!DYNARRAY_ENSURE_INT(&scene->materials, &scene->mat_count,
			&scene->mat_cap, sizeof(t_material)))
		return (init_index(0, true));
	return (init_index(scene->mat_count++, false));
}
