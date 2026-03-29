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

void	delete_sel_extras(t_scene *sc, t_selection *sel)
{
	size_t	idx;

	if (!sel->active)
		return ;
	idx = (size_t)sel->index;
	if ((sel->type == TYPE_RECT || sel->type == TYPE_PYRAMID
			|| sel->type == TYPE_BOX || sel->type == TYPE_CAPSULE)
		&& idx < sc->primitives.count)
		scene_remove_primitive(sc, idx);
}
