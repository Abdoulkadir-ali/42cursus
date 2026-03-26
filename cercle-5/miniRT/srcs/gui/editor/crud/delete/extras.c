/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:14:58 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:41:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	delete_sel_extras(t_scene *sc, t_selection *sel)
{
	int	i;

	i = sel->index;
	if (sel->type == TYPE_RECT && i < sc->rect_count)
	{
		ft_memmove(sc->rects + i, sc->rects + i + 1, (sc->rect_count - i - 1)
			* sizeof(t_rect));
		sc->rect_count--;
		return ;
	}
	if (sel->type == TYPE_PYRAMID && i < sc->pyramid_count)
	{
		ft_memmove(sc->pyramids + i, sc->pyramids + i + 1, (sc->pyramid_count
				- i - 1) * sizeof(t_pyramid));
		sc->pyramid_count--;
		return ;
	}
	if (sel->type == TYPE_BOX && i < sc->box_count)
	{
		ft_memmove(sc->boxes + i, sc->boxes + i + 1, (sc->box_count - i - 1)
			* sizeof(t_box));
		sc->box_count--;
		return ;
	}
	if (sel->type == TYPE_CAPSULE && i < sc->capsule_count)
	{
		ft_memmove(sc->capsules + i, sc->capsules + i + 1, (sc->capsule_count
				- i - 1) * sizeof(t_capsule));
		sc->capsule_count--;
		return ;
	}
}
