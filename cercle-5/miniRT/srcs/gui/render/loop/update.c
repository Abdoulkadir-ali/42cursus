/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 16:32:59 by abdoali          ###   ########.fr       */
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

	delta = update_delta(gui);
	// ft_print_debug("LOOP: START INPUT\n");
	gui_update_input(gui);
	// ft_print_debug("LOOP: START ANIM\n");
	update_animations(gui, delta);
	// ft_print_debug("LOOP: START PHYS\n");
	update_physics_step(gui, delta);
	if (gui->render.dirty)
	{
		// ft_print_debug("LOOP: START RENDER (DIRTY)\n");
		gui_render(gui);
		// ft_print_debug("LOOP: START UPSCALE\n");
		upscale_image(gui);
		gui->render.dirty = false;
	}
	// ft_print_debug("LOOP: START MLX PUT\n");
	mlx_put_image_to_window(gui->win.mlx, gui->win.win, gui->win.disp_img, 0, 0);
	// ft_print_debug("LOOP: START UI TEXT\n");
	draw_ui_text(gui, &gui->cam_ctrl);
	// ft_print_debug("LOOP: FINISHED\n");
	return (0);
}
