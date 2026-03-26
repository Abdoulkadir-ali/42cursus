/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backward.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 06:02:17 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 15:32:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	camera_move_backward(t_camera *camera, double speed)
{
	camera_move(camera, camera->transform.forward, -speed);
}
