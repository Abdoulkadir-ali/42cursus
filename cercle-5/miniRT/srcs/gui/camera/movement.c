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

/*
** Moves camera forward along its look vector.
*/
void	camera_move_forward(t_camera *camera, double speed)
{
	camera->transform.pos = vec3_add(camera->transform.pos,
			vec3_scale(camera->transform.forward, speed));
}

/*
** Moves camera backward along its look vector.
*/
void	camera_move_backward(t_camera *camera, double speed)
{
	camera->transform.pos = vec3_sub(camera->transform.pos,
			vec3_scale(camera->transform.forward, speed));
}

/*
** Moves camera left along its right vector.
*/
void	camera_move_left(t_camera *camera, double speed)
{
	camera->transform.pos = vec3_sub(camera->transform.pos,
			vec3_scale(camera->transform.right, speed));
}

/*
** Moves camera right along its right vector.
*/
void	camera_move_right(t_camera *camera, double speed)
{
	camera->transform.pos = vec3_add(camera->transform.pos,
			vec3_scale(camera->transform.right, speed));
}

/*
** Moves camera up along the global up vector.
*/
void	camera_move_up(t_camera *camera, double speed)
{
	t_vec3	world_up;

	world_up = vec3(0, 1, 0);
	camera->transform.pos = vec3_add(camera->transform.pos, vec3_scale(world_up,
				speed));
}

/*
** Moves camera down along the global up vector.
*/
void	camera_move_down(t_camera *camera, double speed)
{
	t_vec3	world_up;

	world_up = vec3(0, 1, 0);
	camera->transform.pos = vec3_sub(camera->transform.pos, vec3_scale(world_up,
				speed));
}