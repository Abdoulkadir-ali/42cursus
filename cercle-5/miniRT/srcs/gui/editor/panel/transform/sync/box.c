/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_box.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 05:05:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "gui.h"

/**
 * @brief Synchronizes box half-extents with its current scale transform.
 * @param gui Pointer to the GUI context.
 */
void	box_scale_sync(t_gui *gui)
{
	t_box	*bx;

	if (!gui->selection.active || gui->selection.type != TYPE_BOX)
		return ;
	bx = &gui->scene->boxes[gui->selection.index];
	bx->half_extents = bx->transform.scale;
}
