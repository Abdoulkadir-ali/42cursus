/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 13:41:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	editor_delete_selected(t_gui *gui)
{
	t_selection	*sel;
	t_scene		*sc;
	size_t		i;

	if (!gui || !gui->scene || !gui->selection.active)
		return ;
	sel = &gui->selection;
	sc = gui->scene;
	i = sel->index;
	if (sel->type == TYPE_LIGHT && i < sc->light_count)
	{
		ft_memmove(sc->lights + i, sc->lights + i + 1,
			(sc->light_count - i - 1) * sizeof(t_light));
		sc->light_count--;
	}
	else
	{
		delete_sel_sp_pl(sc, sel);
		delete_sel_cy_co(sc, sel);
	}
	clear_selection(gui);
	{ t_cmd _c; ft_memset(&_c, 0, sizeof(_c)); _c.type = CMD_REBUILD_BVH; cmd_enqueue(gui, _c); }
}
