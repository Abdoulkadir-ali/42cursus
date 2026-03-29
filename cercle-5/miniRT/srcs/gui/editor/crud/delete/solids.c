/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solids.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:22:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 15:47:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	delete_sel_solids(t_scene *sc, t_selection *sel)
{
	size_t	idx;

	if (!sel->active)
		return ;
	idx = (size_t)sel->index;
	if ((sel->type == TYPE_CYLINDER || sel->type == TYPE_CONE)
		&& idx < sc->primitives.count)
		scene_remove_primitive(sc, idx);
	else if (sel->type == TYPE_TRI && idx < sc->tri_soa.count)
		scene_remove_tri(sc, idx);
}
