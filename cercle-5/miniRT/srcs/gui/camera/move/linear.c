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

void	camera_move_forward(t_camera *camera, double speed)
{
	camera_move(camera, camera->transform.forward, speed);
}

void	camera_move_backward(t_camera *camera, double speed)
{
	camera_move(camera, camera->transform.forward, -speed);
}
