/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:24:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 10:29:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "debug.h"

void	editor_delete_selected(t_gui *gui)
{
	t_selection	*sel;
	t_scene		*sc;
	int			i;

	if (!gui->scene || !gui->selection->active)
		return ;
	pthread_rwlock_wrlock(&gui->scene_lock);
	sel = gui->selection;
	sc = gui->scene;
	i = sel->index;
	DBG_INFO_MSG(DBG_CH_EDITOR, "editor_delete: type=%d idx=%d prims_before=%zu\n",
		sel->type, sel->index, sc->primitives.count);
	if (handle_delete_light(sc, sel, i))
	{
		clear_selection(gui);
		rebuild_bvh(gui);
		pthread_rwlock_unlock(&gui->scene_lock);
		gui->render.dirty = true;
		return ;
	}
	delete_sel_prims(sc, sel);
	delete_sel_solids(sc, sel);
	delete_sel_extras(sc, sel);
	clear_selection(gui);
	rebuild_bvh(gui);
	DBG_INFO_MSG(DBG_CH_EDITOR, "editor_delete done: prims_after=%zu\n",
		sc->primitives.count);
	pthread_rwlock_unlock(&gui->scene_lock);
}
