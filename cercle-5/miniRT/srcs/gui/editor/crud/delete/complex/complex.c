/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 15:05:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	delete_sel_rect_tri(t_scene *sc, t_selection *sel)
{
	if (sel->type == TYPE_TRI && sel->index < sc->tri_count)
	{
		ft_memmove(sc->tris + sel->index, sc->tris + sel->index + 1,
			(sc->tri_count - sel->index - 1) * sizeof(t_tri_shape));
		sc->tri_count--;
	}
	else if (sel->type == TYPE_RECT && sel->index < sc->rect_count)
	{
		ft_memmove(sc->rects + sel->index, sc->rects + sel->index + 1,
			(sc->rect_count - sel->index - 1) * sizeof(t_rect));
		sc->rect_count--;
	}
	else
		delete_sel_py_bx(sc, sel);
}

void	delete_sel_cy_co(t_scene *sc, t_selection *sel)
{
	if (sel->type == TYPE_CYLINDER && sel->index < sc->cylinder_count)
	{
		ft_memmove(sc->cylinders + sel->index, sc->cylinders + sel->index + 1,
			(sc->cylinder_count - sel->index - 1) * sizeof(t_cylinder));
		sc->cylinder_count--;
	}
	else if (sel->type == TYPE_CONE && sel->index < sc->cone_count)
	{
		ft_memmove(sc->cones + sel->index, sc->cones + sel->index + 1,
			(sc->cone_count - sel->index - 1) * sizeof(t_cone));
		sc->cone_count--;
	}
	else
		delete_sel_rect_tri(sc, sel);
}
