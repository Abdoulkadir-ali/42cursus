/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:00:00 by abdoali          ###   ########.fr       */
/*   Updated: 2026/02/11 20:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "profiler.h"

static void	setup_camera_transform(t_gui *gui, t_render_ctx *ctx)
{
	double	pitch;
	double	yaw;

	ctx->transform = gui->cam_ctrl.camera->transform;
	pitch = gui->cam_ctrl.transform.rotation.pitch;
	yaw = gui->cam_ctrl.transform.rotation.yaw;
	ctx->transform.forward = get_camera_forward(pitch, yaw);
	ctx->transform.right = vec3_norm(vec3_cross(ctx->transform.forward, vec3(0,
					1, 0)));
	if (vec3_mag_sq(ctx->transform.right) < 1e-6)
		ctx->transform.right = vec3(1, 0, 0);
	ctx->transform.up = vec3_cross(ctx->transform.right,
			ctx->transform.forward);
	gui->cam_ctrl.camera->transform = ctx->transform;
}

/*
** Sets up the rendering context.
*/
static void	setup_ctx(t_gui *gui, t_render_ctx *ctx)
{
	double	fov_rad;

	ctx->gui = gui;
	ctx->step = gui->render.scale;
	if (ctx->step < 1)
		ctx->step = 1;
	fov_rad = 70.0;
	if (gui->cam_ctrl.camera)
		fov_rad = gui->cam_ctrl.camera->fov;
	fov_rad = fov_rad * M_PI / 180.0;
	ctx->aspect_ratio = (double)gui->win.width / (double)gui->win.height;
	ctx->half_width = tan(fov_rad / 2.0);
	ctx->half_height = ctx->half_width / ctx->aspect_ratio;
	if (gui->cam_ctrl.camera)
		setup_camera_transform(gui, ctx);
	else
		ctx->transform = (t_transform){0};
}

static void	finish_render(t_gui *gui, t_render_ctx *ctx)
{
	upscale_image(gui);
	draw_ui_panels(gui);
	update_hover(gui, ctx);
	mlx_put_image_to_window(gui->win.mlx, gui->win.win,
		gui->win.disp_img, 0, 0);
	draw_ui_text(gui, &gui->cam_ctrl);
	draw_hover_text(gui);
}

/*
** Main render function.
*/
void	gui_render(t_gui *gui)
{
	t_render_ctx	ctx;

	PROF_RESET();
	setup_ctx(gui, &ctx);
	ctx.tiles_x = (gui->win.width + TILE_SIZE - 1) / TILE_SIZE;
	ctx.total_tiles = ctx.tiles_x * ((gui->win.height + TILE_SIZE - 1)
			/ TILE_SIZE);
	ctx.next_tile_id = 0;
	render_tiles(&ctx);
	PROF_PRINT();
	finish_render(gui, &ctx);
}
