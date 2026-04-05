/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 23:43:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <stdatomic.h>

int	gui_update(t_gui *gui)
{
	void	*blit;
	size_t	i;

	i = 0;
#ifdef PROFILE_BUILD
	static int	_prof_frames = 0;
	if (++_prof_frames > 5)
		mlx_loop_end(gui->win.mlx);
#endif
	gui_update_input(gui);
	blit = atomic_load(&gui->render.blit_img);
	if (blit)
		mlx_put_image_to_window(gui->win.mlx, gui->win.win, blit, 0, 0);
	if (gui->render.disp_destroy_pending)
	{
		__sync_synchronize();
		i = 0;
		while (i < 3)
		{
			if (gui->render.old_disp_imgs[i] && gui->render.old_disp_imgs[i] != blit)
				mlx_destroy_image(gui->win.mlx, gui->render.old_disp_imgs[i]);
			gui->render.old_disp_imgs[i] = NULL;
			i++;
		}
		gui->render.disp_destroy_pending = 0;
	}
	draw_ui_strings(gui, &gui->cam_ctrl);
	return (0);
}
