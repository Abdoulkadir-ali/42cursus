/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 03:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

// Helper to recompute right/up vectors if needed, 
// but for now we assume forward is updated and we use global up (0,1,0) 
// to compute right.

void	camera_move_forward(t_camera *camera, double speed)
{
	camera->pos = vec3_add(camera->pos, vec3_scale(camera->forward, speed));
}

void	camera_move_backward(t_camera *camera, double speed)
{
	camera->pos = vec3_sub(camera->pos, vec3_scale(camera->forward, speed));
}

void	camera_move_left(t_camera *camera, double speed)
{
	t_vec3	world_up = vec3(0, 1, 0);
	t_vec3	right = vec3_norm(vec3_cross(camera->forward, world_up));
	camera->pos = vec3_sub(camera->pos, vec3_scale(right, speed));
}

void	camera_move_right(t_camera *camera, double speed)
{
	t_vec3	world_up = vec3(0, 1, 0);
	t_vec3	right = vec3_norm(vec3_cross(camera->forward, world_up));
	camera->pos = vec3_add(camera->pos, vec3_scale(right, speed));
}

void	camera_move_up(t_camera *camera, double speed)
{
	t_vec3	world_up = vec3(0, 1, 0);
	camera->pos = vec3_add(camera->pos, vec3_scale(world_up, speed));
}

void	camera_move_down(t_camera *camera, double speed)
{
	t_vec3	world_up = vec3(0, 1, 0);
	camera->pos = vec3_sub(camera->pos, vec3_scale(world_up, speed));
}