/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:57:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "debug.h"

static void	setup_camera_transform(t_gui *gui, t_render *ctx)
{
	t_camera_controller	*ctrl;

	ctrl = &gui->cam_ctrl;
	ctx->transform = ctrl->camera->transform;
	ctx->transform.forward = ctrl->transform.forward;
	ctx->transform.right = ctrl->transform.right;
	ctx->transform.up = ctrl->transform.up;
	ctx->transform.pos = ctrl->transform.pos;
	ctrl->camera->transform = ctx->transform;
}

/*
** Sets up the rendering context.
*/
static void	update_proj_cache(t_gui *gui)
{
	double	fov_rad;

	fov_rad = 70.0;
	if (gui->cam_ctrl.camera)
		fov_rad = gui->cam_ctrl.camera->fov;
	fov_rad = fov_rad * M_PI / 180.0;
	gui->render.cached_aspect = (double)gui->win.size.x
		/ (double)gui->win.size.y;
	gui->render.cached_half_w = tan(fov_rad / 2.0);
	gui->render.cached_half_h = gui->render.cached_half_w
		/ gui->render.cached_aspect;
	gui->render.proj_dirty = false;
}

static void	setup_ctx(t_gui *gui, t_render *ctx)
{
	ctx->gui = gui;
	ctx->step = gui->render.scale;
	if (ctx->step < 1)
		ctx->step = 1;
	if (gui->render.proj_dirty)
		update_proj_cache(gui);
	ctx->half_width = gui->render.cached_half_w;
	ctx->half_height = gui->render.cached_half_h;
	ctx->aspect_ratio = gui->render.cached_aspect;
	ctx->px_step_x = 2.0 * ctx->half_width * ctx->aspect_ratio
		/ gui->win.size.x;
	ctx->px_step_y = 2.0 * ctx->half_height * ctx->aspect_ratio
		/ gui->win.size.y;
	ctx->px_off_x = ctx->half_width * ctx->aspect_ratio;
	ctx->px_off_y = ctx->half_height * ctx->aspect_ratio;
	if (gui->cam_ctrl.camera)
		setup_camera_transform(gui, ctx);
	else
		ctx->transform = (t_transform){0};
}

static void	finish_render(t_gui *gui, t_render *ctx)
{
	upscale_image(gui);
	draw_ui_panels(gui);
	update_hover(gui, ctx);
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
	t_render	ctx;
	t_scene			*scene;

	scene = gui->scene;
	if (gui->rt.baked_version != scene->version)
	{
		DBG_INFO_MSG(DBG_CH_RENDER,
			"gui_render: BVH sync (scene v%d)\n", scene->version);
		raytrace_engine_sync(&gui->rt, scene, gui->win.size.x,
			gui->win.size.y);
	}
	DBG_TRACE_MSG(DBG_CH_RENDER, "frame start (fps=%.1f scale=%d)\n",
		gui->render.fps, gui->render.scale);
	PROF_RESET();
	setup_ctx(gui, &ctx);
	ctx.tiles_x = (gui->win.size.x + TILE_SIZE - 1) / TILE_SIZE;
	ctx.total_tiles = ctx.tiles_x * ((gui->win.size.y + TILE_SIZE - 1)
			/ TILE_SIZE);
	ctx.next_tile_id = 0;
	render_tiles(&ctx);
	PROF_PRINT();
	finish_render(gui, &ctx);
}
