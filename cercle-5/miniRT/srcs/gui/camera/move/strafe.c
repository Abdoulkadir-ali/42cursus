/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strafe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 06:02:02 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 06:02:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	camera_move_left(t_camera *camera, double speed)
{
	camera_move(camera, camera->transform.right, -speed);
}

void	camera_move_right(t_camera *camera, double speed)
{
	camera_move(camera, camera->transform.right, speed);
}
