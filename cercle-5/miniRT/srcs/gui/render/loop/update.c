/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 19:01:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	update_animations(t_gui *gui, double delta)
{
	(void)gui;
	(void)delta;
}

void	update_physics_step(t_gui *gui, double delta)
{
	double	fixed_dt;
	int		steps;

	if (!gui || !gui->scene || !gui->physics_enabled)
		return ;
	if (gui->phys_fixed_dt > 0.0)
		fixed_dt = gui->phys_fixed_dt;
	else
		fixed_dt = 1.0 / 60.0;
	if (delta > fixed_dt * 3.0)
		delta = fixed_dt * 3.0;
	gui->phys_accumulator += delta;
	steps = 0;
	while (gui->phys_accumulator >= fixed_dt && steps < 3)
	{
		update_physics(gui->scene, &gui->phys_engine, fixed_dt);
		gui->phys_accumulator -= fixed_dt;
		steps++;
	}
	if (steps > 0)
		gui->render.dirty = true;
}

void	update_ambient(t_gui *gui)
{
	t_ambient	*amb;

	if (!gui->scene)
		return ;
	amb = &gui->scene->ambient;
	amb->rgb.x = ((gui->ambient_color >> 16) & 0xFF) / 255.0
		* gui->ambient_intensity;
	amb->rgb.y = ((gui->ambient_color >> 8) & 0xFF) / 255.0
		* gui->ambient_intensity;
	amb->rgb.z = (gui->ambient_color & 0xFF) / 255.0 * gui->ambient_intensity;
	amb->brightness = gui->ambient_intensity;
}

int	gui_update(t_gui *gui)
{
	double	delta;
#ifdef PROFILE_BUILD
	static int	_prof_frames = 0;
	if (++_prof_frames > 5)
		mlx_loop_end(gui->win.mlx);
#endif
#ifdef TIME_LOOP
	struct timeval _tv0, _tv1;
# define T0() gettimeofday(&_tv0, NULL)
# define T1(label) do { gettimeofday(&_tv1, NULL); \
	printf(label ": %ldms\n", \
		(_tv1.tv_sec - _tv0.tv_sec) * 1000 + (_tv1.tv_usec - _tv0.tv_usec) / 1000); \
	fflush(stdout); } while (0)
#else
# define T0()
# define T1(label)
#endif

	T0(); delta = update_delta(gui); T1("update_delta");
	T0(); gui_update_input(gui); T1("gui_update_input");
	T0(); update_animations(gui, delta); T1("update_animations");
	T0(); update_physics_step(gui, delta); T1("update_physics_step");
	if (gui->render.dirty)
	{
		T0(); gui_render(gui); T1("gui_render");
		T0(); upscale_image(gui); T1("upscale_image");
		T0(); optimize_frames(gui, delta); T1("optimize_frames");
		gui->render.dirty = false;
	}
	T0(); mlx_put_image_to_window(gui->win.mlx, gui->win.win, gui->win.disp_img, 0, 0); T1("mlx_put");
	T0(); draw_ui_text(gui, &gui->cam_ctrl); T1("draw_ui_text");
	return (0);
}
