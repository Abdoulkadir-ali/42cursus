/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_sphere.c                                      :+:      :+:    :+:   */
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
 * @brief Synchronizes sphere uniform scale and inverse transform.
 * @param gui Pointer to the GUI context.
 */
void	sphere_scale_sync(t_gui *gui)
{
	t_sphere	*sp;
	t_transform	tr;

	if (!gui->selection.active || gui->selection.type != TYPE_SPHERE)
		return ;
	sp = &gui->scene->spheres[gui->selection.index];
	sp->transform.scale.y = sp->transform.scale.x;
	sp->transform.scale.z = sp->transform.scale.x;
	sp->radius_sq = sp->transform.scale.x * sp->transform.scale.x;
	tr.pos = sp->transform.pos;
	tr.scale = sp->transform.scale;
	tr.rotation = (t_rotator){0, 0, 0};
	sp->inv_transform = mat4_inverse_transform(tr);
}
