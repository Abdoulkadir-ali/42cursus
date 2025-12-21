/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/17 21:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	recenter_camera_on_resize(t_camera *cam, int old_w, int old_h,
		int new_w, int new_h)
{
	if (!cam)
		return ;
	cam->offset.x += (new_w - old_w) / 2.0;
	cam->offset.y += (new_h - old_h) / 2.0;
}
