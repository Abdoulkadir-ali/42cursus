/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:43:49 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:24:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Toggle inverted movement for camera translation controls.
 * @param keycode Unused X11 keycode.
 * @param events Event context owning the camera state.
 * @return Always `1`.
 */
int	handle_i(int keycode, t_events *events)
{
	(void)keycode;
	events->camera->invert_movement = !events->camera->invert_movement;
	return (1);
}
