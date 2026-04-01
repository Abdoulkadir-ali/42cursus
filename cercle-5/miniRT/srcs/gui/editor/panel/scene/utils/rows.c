/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rows.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 19:33:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int	count_scene_rows(t_scene *sc)
{
	int	total;

	total = sc->light_count + sc->sphere_count + sc->plane_count;
	total += sc->cylinder_count + sc->cone_count + sc->tri_count;
	total += sc->rect_count + sc->pyramid_count;
	total += sc->box_count + sc->capsule_count;
	total += count_mesh_entries(sc);
	return (total);
}
