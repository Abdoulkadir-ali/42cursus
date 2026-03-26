/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 06:02:17 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 06:02:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	camera_move_forward(t_camera *camera, double speed)
{
	camera_move(camera, camera->transform.forward, speed);
}
