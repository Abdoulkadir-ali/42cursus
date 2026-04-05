/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 14:50:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <stdatomic.h>

int	gui_update(t_gui *gui)
{
#ifdef PROFILE_BUILD
	static int	_prof_frames = 0;
	if (++_prof_frames > 5)
		mlx_loop_end(gui->win.mlx);
#endif
	gui->render.ui_buf_idx = atomic_load(&gui->render.front_idx);
	gui_update_input(gui);
	mlx_put_image_to_window(gui->win.mlx, gui->win.win,
		gui->win.disp_imgs[gui->render.ui_buf_idx], 0, 0);
	draw_ui_text(gui, &gui->cam_ctrl);
	return (0);
}
