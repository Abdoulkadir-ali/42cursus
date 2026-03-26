/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:24:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 16:15:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	editor_delete_selected(t_gui *gui)
{
	t_selection	*sel;
	t_scene		*sc;
	int			i;

	if (!gui->scene || !gui->selection.active)
		return ;
	sel = &gui->selection;
	sc = gui->scene;
	i = sel->index;
	if (handle_delete_light(sc, sel, i))
	{
		clear_selection(gui);
		rebuild_bvh(gui);
		gui->render.dirty = true;
		return ;
	}
	delete_sel_prims(sc, sel);
	delete_sel_solids(sc, sel);
	delete_sel_extras(sc, sel);
	clear_selection(gui);
	rebuild_bvh(gui);
	gui->render.dirty = true;
}
