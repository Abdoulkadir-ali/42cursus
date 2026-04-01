/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 20:05:47 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 20:05:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	setup_camera_transform(t_gui *gui, t_render *render)
{
	double	pitch;
	double	yaw;

	render->transform = gui->cam_ctrl.camera->transform;
	pitch = gui->cam_ctrl.transform.rotation.pitch;
	yaw = gui->cam_ctrl.transform.rotation.yaw;
	render->transform.forward = get_camera_forward(pitch, yaw);
	render->transform.right = vec3_norm(vec3_cross(render->transform.forward,
				vec3(0, 1, 0)));
	if (vec3_mag_sq(render->transform.right) < 1e-6)
		render->transform.right = vec3(1, 0, 0);
	render->transform.up = vec3_cross(render->transform.right,
			render->transform.forward);
	gui->cam_ctrl.camera->transform = render->transform;
}

/*
** Sets up the rendering context.
*/
static void	setup(t_gui *gui, t_render *render)
{
	double	fov_rad;

	render->gui = gui;
	render->step = gui->render.scale;
	if (render->step < 1)
		render->step = 1;
	fov_rad = 70.0;
	if (gui->cam_ctrl.camera)
		fov_rad = gui->cam_ctrl.camera->fov;
	fov_rad = fov_rad * M_PI / 180.0;
	render->aspect_ratio = (double)gui->win.size.x / (double)gui->win.size.y;
	render->half_width = tan(fov_rad / 2.0);
	render->half_height = render->half_width / render->aspect_ratio;
	if (gui->cam_ctrl.camera)
		setup_camera_transform(gui, render);
	else
		render->transform = (t_transform){0};
}

static void	finish_render(t_gui *gui, t_render *render)
{
	upscale_image(gui);
	draw_ui_panels(gui);
	update_hover(gui, render);
	draw_ui_text(gui, &gui->cam_ctrl);
	draw_hover_text(gui);
	mlx_put_image_to_window(gui->win.mlx, gui->win.win,
		gui->win.disp_img, 0, 0);
}

/*
** Main render function.
*/
void	gui_render(t_gui *gui)
{
	t_render	render;

	PROF_RESET();
	setup(gui, &render);
	render.tiles_count.x = (gui->win.size.x + TILE_SIZE - 1) / TILE_SIZE;
	render.tiles_count.y = (gui->win.size.y + TILE_SIZE - 1) / TILE_SIZE;
	render.total_tiles = render.tiles_count.x * render.tiles_count.y;
	render.next_tile_id = 0;
	render_tiles(&render);
	PROF_PRINT();
	finish_render(gui, &render);
}
