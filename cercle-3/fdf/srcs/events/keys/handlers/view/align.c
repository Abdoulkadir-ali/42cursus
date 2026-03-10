/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:22:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:24:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Snap the camera target rotation to the first preset view.
 * @param keycode Unused X11 keycode.
 * @param events Event context owning the camera state.
 * @return `1` when applied, otherwise `0`.
 */
int	handle_1(int keycode, t_events *events)
{
	(void)keycode;
	if (!events || !events->camera)
		return (0);
	events->camera->target_rotation = create_vec3d(0, M_PI / 2, 0);
	return (1);
}

/**
 * @brief Snap the camera target rotation to the second preset view.
 * @param keycode Unused X11 keycode.
 * @param events Event context owning the camera state.
 * @return `1` when applied, otherwise `0`.
 */
int	handle_2(int keycode, t_events *events)
{
	(void)keycode;
	if (!events || !events->camera)
		return (0);
	events->camera->target_rotation = create_vec3d(M_PI / 2, 0, 0);
	return (1);
}

/**
 * @brief Snap the camera target rotation to the third preset view.
 * @param keycode Unused X11 keycode.
 * @param events Event context owning the camera state.
 * @return `1` when applied, otherwise `0`.
 */
int	handle_3(int keycode, t_events *events)
{
	(void)keycode;
	if (!events || !events->camera)
		return (0);
	events->camera->target_rotation = create_vec3d(0, 0, 0);
	return (1);
}
