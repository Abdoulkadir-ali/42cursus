/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prims.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:21:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 15:47:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "debug.h"

void	delete_sel_prims(t_scene *sc, t_selection *sel)
{
	size_t	idx;

	DBG_INFO_MSG(DBG_CH_EDITOR, "delete_prims: type=%d idx=%d\n",
		sel->type, sel->index);
	if (!sel->active)
	{
		DBG_ERR_MSG(DBG_CH_EDITOR, "delete_prims: nothing to delete\n");
		return ;
	}
	idx = (size_t)sel->index;
	if ((sel->type == TYPE_SPHERE || sel->type == TYPE_PLANE)
		&& idx < sc->primitives.count)
		scene_remove_primitive(sc, idx);
}
