/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/02 17:17:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"

static int	handle_cam_rotation(t_app *app, t_camera *c)
{
	t_input	*in;

	in = &app->input;
	if (in->rmb_cam_drag && (in->mouse_dx | in->mouse_dy) && app->ui.active_id == 0)
	{
		app->scene.cam_yaw -= in->mouse_dx * app->set.controls.mouse_sens;
		app->scene.cam_pitch -= in->mouse_dy * app->set.controls.mouse_sens;
		if (app->scene.cam_pitch > 1.5533f)
			app->scene.cam_pitch = 1.5533f;
		if (app->scene.cam_pitch < -1.5533f)
			app->scene.cam_pitch = -1.5533f;
		camera_from_yaw_pitch(c, app->scene.cam_yaw, app->scene.cam_pitch);
		return (1);
	}
	return (0);
}

static int	handle_cam_movement(t_app *app, t_camera *c, float dt)
{
	t_input	*in;
	float	speed;
	int		moved;

	in = &app->input;
	moved = 0;
	speed = app->set.controls.move_speed * dt;
	if (key_held(in, XK_Shift_L))
		speed *= 4.0f;
	if (key_held(in, XK_w) || key_held(in, KEY_Z) || key_held(in, XK_z) || \
		key_held(in, XK_W))
	{
		c->pos = v3_add(c->pos, v3_mul(c->dir, speed));
		moved = 1;
	}
	if (key_held(in, XK_s) || key_held(in, XK_S))
	{
		c->pos = v3_sub(c->pos, v3_mul(c->dir, speed));
		moved = 1;
	}
	if (key_held(in, XK_a) || key_held(in, XK_q) || key_held(in, XK_A) || \
		key_held(in, XK_Q))
	{
		c->pos = v3_sub(c->pos, v3_mul(c->right, speed));
		moved = 1;
	}
	if (key_held(in, XK_d) || key_held(in, XK_D))
	{
		c->pos = v3_add(c->pos, v3_mul(c->right, speed));
		moved = 1;
	}
	if (key_held(in, KEY_SPACE) || key_held(in, XK_e) || key_held(in, XK_E))
	{
		c->pos = v3_add(c->pos, v3_mul(c->up, speed));
		moved = 1;
	}
	if (key_held(in, KEY_LCTRL))
	{
		c->pos = v3_sub(c->pos, v3_mul(c->up, speed));
		moved = 1;
	}
	return (moved);
}

static int	handle_cam_fov(t_app *app, t_camera *c, float dt)
{
	t_input	*in;
	int		moved;

	in = &app->input;
	moved = 0;
	if (key_held(in, KEY_PLUS))
	{
		c->fov = ft_clampf(c->fov - 30.0f * dt, 5.0f, 175.0f);
		moved = 1;
	}
	if (key_held(in, KEY_MINUS))
	{
		c->fov = ft_clampf(c->fov + 30.0f * dt, 5.0f, 175.0f);
		moved = 1;
	}
	return (moved);
}

void	update_camera(t_app *app)
{
	t_camera	*c;
	float		dt;
	int			changed;
	int			ui_dragging;

	c = &app->scene.cam;
	dt = (float)app->time.frame_dt;
	if (dt > 0.1f)
		dt = 0.1f;
	ui_dragging = (app->input.mouse_left && app->ui.active_id != 0);
	changed = 0;
	changed |= handle_cam_rotation(app, c);
	changed |= handle_cam_movement(app, c, dt);
	changed |= handle_cam_fov(app, c, dt);
	if (changed)
		camera_setup(c, app->img.w, app->img.h);
	if (changed || ui_dragging)
	{
		app->dirty = 1;
		app->moving = 1;
	}
	else
		app->moving = 0;
}