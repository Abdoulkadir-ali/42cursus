/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 12:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	handle_scroll(int button, t_gui *gui)
{
	if (scene_panel_handle_scroll(gui, button))
		return ;
	if (button == Button4)
	{
		gui->cam_ctrl.target_fov -= ZOOM_SPEED;
		clamp_fov(&gui->cam_ctrl.target_fov);
		gui->render.dirty = true;
	}
	else if (button == Button5)
	{
		gui->cam_ctrl.target_fov += ZOOM_SPEED;
		clamp_fov(&gui->cam_ctrl.target_fov);
		gui->render.dirty = true;
	}
}
