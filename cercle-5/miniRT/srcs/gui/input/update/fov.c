/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 16:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	update_fov(t_gui *gui, t_camera_controller *ctrl)
{
	if (ctrl->zooming_in)
	{
		ctrl->target_fov -= 1.0;
		clamp_fov(&ctrl->target_fov);
	}
	if (ctrl->zooming_out)
	{
		ctrl->target_fov += 1.0;
		clamp_fov(&ctrl->target_fov);
	}
	if (fabs(ctrl->target_fov - ctrl->camera->fov) > 1e-2)
	{
		ctrl->camera->fov += (ctrl->target_fov - ctrl->camera->fov)
			* ctrl->lerp_factor;
		gui->render.dirty = true;
		gui->render.proj_dirty = true;
	}
}
