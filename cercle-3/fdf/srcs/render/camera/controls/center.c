/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 16:28:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	recenter_camera_on_resize(t_camera *cam, t_vec2 old_size,
		t_vec2 new_size)
{
	if (!cam)
		return ;
	cam->offset.x += (new_size.x - old_size.x) / 2.0;
	cam->offset.y += (new_size.y - old_size.y) / 2.0;
}
