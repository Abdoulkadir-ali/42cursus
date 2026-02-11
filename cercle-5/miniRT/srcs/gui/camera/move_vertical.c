/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 20:30:00 by abdoali          #+#    #+#             */
/*   Updated: 2026/02/11 20:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static void	camera_move(t_camera *camera, t_vec3 direction, double speed)
{
	camera->transform.pos = vec3_add(camera->transform.pos,
			vec3_scale(direction, speed));
}

void	camera_move_up(t_camera *camera, double speed)
{
	camera_move(camera, vec3(0, 1, 0), speed);
}

void	camera_move_down(t_camera *camera, double speed)
{
	camera_move(camera, vec3(0, 1, 0), -speed);
}
