/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 13:41:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	delete_sel_cy_co(t_scene *sc, t_selection *sel)
{
	size_t	i;

	i = sel->index;
	if (sel->type == TYPE_CYLINDER && i < sc->cylinder_count)
	{
		ft_memmove(sc->cylinders + i, sc->cylinders + i + 1,
			(sc->cylinder_count - i - 1) * sizeof(t_cylinder));
		sc->cylinder_count--;
	}
	else if (sel->type == TYPE_CONE && i < sc->cone_count)
	{
		ft_memmove(sc->cones + i, sc->cones + i + 1,
			(sc->cone_count - i - 1) * sizeof(t_cone));
		sc->cone_count--;
	}
	else if (sel->type == TYPE_TRI && i < sc->tri_count)
	{
		ft_memmove(sc->tris + i, sc->tris + i + 1,
			(sc->tri_count - i - 1) * sizeof(t_tri_shape));
		sc->tri_count--;
	}
	else if (sel->type == TYPE_RECT && i < sc->rect_count)
	{
		ft_memmove(sc->rects + i, sc->rects + i + 1,
			(sc->rect_count - i - 1) * sizeof(t_rect));
		sc->rect_count--;
	}
	else if (sel->type == TYPE_PYRAMID && i < sc->pyramid_count)
	{
		ft_memmove(sc->pyramids + i, sc->pyramids + i + 1,
			(sc->pyramid_count - i - 1) * sizeof(t_pyramid));
		sc->pyramid_count--;
	}
	else if (sel->type == TYPE_BOX && i < sc->box_count)
	{
		ft_memmove(sc->boxes + i, sc->boxes + i + 1,
			(sc->box_count - i - 1) * sizeof(t_box));
		sc->box_count--;
	}
	else if (sel->type == TYPE_CAPSULE && i < sc->capsule_count)
	{
		ft_memmove(sc->capsules + i, sc->capsules + i + 1,
			(sc->capsule_count - i - 1) * sizeof(t_capsule));
		sc->capsule_count--;
	}
}
