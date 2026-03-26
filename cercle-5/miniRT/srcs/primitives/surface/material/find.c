/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 04:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "surface.h"
#include "scene.h"

/**
 * @brief Finds a material by name in the scene.
 * @param sc Pointer to the scene.
 * @param name Name of the material to find.
 * @return int Index of the material, or -1 if not found.
 */
int	scene_find_material(t_scene *sc, const char *name)
{
	int	i;

	if (!name)
		return (-1);
	i = 0;
	while (i < sc->mat_count)
	{
		if (sc->materials[i].name
			&& ft_strcmp(sc->materials[i].name, name) == 0)
			return (i);
		i++;
	}
	return (-1);
}
