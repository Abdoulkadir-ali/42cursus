/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
/**
 * @brief Synchronizes capsule radius and height with its transform scale.
 * @param gui Pointer to the GUI context.
 */
void	capsule_dims_sync(t_gui *gui)
{
	t_capsule	*cap;

	if (!gui->selection->active || gui->selection->type != TYPE_CAPSULE)
		return ;
	cap = &gui->scene->capsules[gui->selection->index];
	cap->radius = cap->transform.scale.x;
	cap->half_height = cap->transform.scale.y;
	cap->transform.scale.z = cap->transform.scale.x;
}
