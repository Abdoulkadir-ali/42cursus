/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 12:56:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	sphere_scale_sync(t_gui *gui)
{
	t_sphere	*s;
	t_scene		*sc;
	double		r;

	if (!gui->selection.active || gui->selection.type != TYPE_SPHERE)
		return ;
	sc = gui->scene;
	if (gui->selection.index >= sc->sphere_count)
		return ;
	s = &sc->spheres[gui->selection.index];
	r = fmax(fmax(gui->transform.scale.x, gui->transform.scale.y),
			gui->transform.scale.z);
	if (r < 0.01)
		r = 0.01;
	s->radius_sq = r * r;
}
