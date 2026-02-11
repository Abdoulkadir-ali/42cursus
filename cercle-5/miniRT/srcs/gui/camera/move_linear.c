/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_linear.c                                      :+:      :+:    :+:   */
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

void	camera_move_forward(t_camera *camera, double speed)
{
	camera_move(camera, camera->transform.forward, speed);
}

void	camera_move_backward(t_camera *camera, double speed)
{
	camera_move(camera, camera->transform.forward, -speed);
}
