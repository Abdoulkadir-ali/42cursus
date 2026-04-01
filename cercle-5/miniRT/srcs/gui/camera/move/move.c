/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:03:28 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 20:03:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	camera_move(t_camera *camera, t_vec3 direction, double speed)
{
	camera->transform.pos = vec3_add(camera->transform.pos,
			vec3_scale(direction, speed));
}
