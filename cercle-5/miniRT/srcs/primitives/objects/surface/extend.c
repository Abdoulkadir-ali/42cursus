/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 18:42:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

int	scene_material_allocate_slot(t_scene *scene)
{
	if (!DYNARRAY_ENSURE_INT(&scene->materials, &scene->mat_count,
			&scene->mat_cap, sizeof(t_material)))
		return (-1);
	return (scene->mat_count++);
}
