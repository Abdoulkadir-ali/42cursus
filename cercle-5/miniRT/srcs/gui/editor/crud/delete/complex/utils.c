/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 15:05:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	delete_sel_py_bx(t_scene *sc, t_selection *sel)
{
	if (sel->type == TYPE_PYRAMID && sel->index < sc->pyramid_count)
	{
		ft_memmove(sc->pyramids + sel->index, sc->pyramids + sel->index + 1,
			(sc->pyramid_count - sel->index - 1) * sizeof(t_pyramid));
		sc->pyramid_count--;
	}
	else if (sel->type == TYPE_BOX && sel->index < sc->box_count)
	{
		ft_memmove(sc->boxes + sel->index, sc->boxes + sel->index + 1,
			(sc->box_count - sel->index - 1) * sizeof(t_box));
		sc->box_count--;
	}
	else if (sel->type == TYPE_CAPSULE && sel->index < sc->capsule_count)
	{
		ft_memmove(sc->capsules + sel->index, sc->capsules + sel->index + 1,
			(sc->capsule_count - sel->index - 1) * sizeof(t_capsule));
		sc->capsule_count--;
	}
}
