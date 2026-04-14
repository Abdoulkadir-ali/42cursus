/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emissive.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 15:12:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/*
** Checks if a material emission is strong enough to count as a light source.
*/
bool	is_emissive(t_scene *sc, size_t mat_id)
{
	t_material	*mat;
	t_vec3		e;

	if (mat_id >= sc->mat_count)
		return (false);
	mat = &sc->materials[mat_id];
	if (mat->temperature > 0.0)
		return (true);
	e = mat->emission;
	return ((e.x * e.x + e.y * e.y + e.z * e.z) > 1.0);
}
