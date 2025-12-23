/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 12:22:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 23:12:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	handle_1(int keycode, t_events *events)
{
	(void)keycode;
	if (!events || !events->camera)
		return (0);
	events->camera->target_rotation = create_vec3d(0, M_PI / 2, 0);
	return (1);
}

int	handle_2(int keycode, t_events *events)
{
	(void)keycode;
	if (!events || !events->camera)
		return (0);
	events->camera->target_rotation = create_vec3d(M_PI / 2, 0, 0);
	return (1);
}

int	handle_3(int keycode, t_events *events)
{
	(void)keycode;
	if (!events || !events->camera)
		return (0);
	events->camera->target_rotation = create_vec3d(0, 0, 0);
	return (1);
}
