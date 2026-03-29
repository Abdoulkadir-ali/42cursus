/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:14:58 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 15:47:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "debug.h"

void	delete_sel_extras(t_scene *sc, t_selection *sel)
{
	size_t	idx;

	DBG_INFO_MSG(DBG_CH_EDITOR, "delete_extras: type=%d idx=%d\n",
		sel->type, sel->index);
	if (!sel->active)
	{
		DBG_ERR_MSG(DBG_CH_EDITOR, "delete_extras: nothing to delete\n");
		return ;
	}
	idx = (size_t)sel->index;
	if ((sel->type == TYPE_RECT || sel->type == TYPE_PYRAMID
			|| sel->type == TYPE_BOX || sel->type == TYPE_CAPSULE)
		&& idx < sc->primitives.count)
		scene_remove_primitive(sc, idx);
}
