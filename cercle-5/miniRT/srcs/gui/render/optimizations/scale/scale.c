/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 01:04:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"

void	adaptive_scale(t_gui *gui)
{
	long long	now;
	size_t		new_scale;

	if (gui->render.force_fullres)
		return ;
	now = gui->render.last_time;
	if (now - gui->render.scale_last_change < SCALE_COOLDOWN_MS)
		return ;
	new_scale = gui->render.scale;
	if (gui->render.fps < SCALE_FPS_LOW && new_scale < SCALE_MAX)
		new_scale++;
	else if (gui->render.fps > SCALE_FPS_HIGH && new_scale > SCALE_MIN)
		new_scale--;
	else
		return ;
	gui->render.scale = new_scale;
	gui->render.scale_last_change = now;
	gui->render.dirty = true;
}
