/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/02 18:13:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "core.h"

static void	handle_kb_focus(int key, t_app *app)
{
	int	len;

	len = strlen(app->ui.input_buf);
	if (key == XK_Return || key == XK_KP_Enter)
		app->ui.kb_focus = 0;
	else if (key == XK_BackSpace && len > 0)
		app->ui.input_buf[len - 1] = '\0';
	else if (len < 31 && ((key >= '0' && key <= '9') || key == '.'
			|| key == '-' || key == ','))
	{
		if (key == ',')
			app->ui.input_buf[len] = '.';
		else
			app->ui.input_buf[len] = (char)key;
		app->ui.input_buf[len + 1] = '\0';
	}
}

static void	handle_shortcuts(int key, t_app *app)
{
	char	path[64];
	long	t;

	if (key == XK_Tab)
		app->set.controls.show_gui = !app->set.controls.show_gui;
	if (key == 'p')
	{
		t = (long)time_ms_now();
		snprintf(path, sizeof(path), "screenshot_%ld.png", t);
		if (render_screenshot(app, path) == 0)
			fprintf(stderr, "saved %s\n", path);
	}
}

int	on_keydown(int key, t_app *app)
{
	if (app->ui.kb_focus)
		return (handle_kb_focus(key, app), 0);
	if (key == XK_Escape)
		return (on_close(app));
	handle_shortcuts(key, app);
	if (ui_handle_key(app, key))
		return (0);
	if (key == KEY_UP)
		app->set.controls.move_speed = ft_clampf(app->set.controls.move_speed * 1.25f, 0.1, 5000);
	if (key == KEY_DOWN)
		app->set.controls.move_speed = ft_clampf(app->set.controls.move_speed * 0.8f, 0.1, 5000);
	if (key == KEY_RIGHT)
		app->set.controls.mouse_sens = ft_clampf(app->set.controls.mouse_sens * 1.25f, 1e-4, 0.5);
	if (key == KEY_LEFT)
		app->set.controls.mouse_sens = ft_clampf(app->set.controls.mouse_sens * 0.8f, 1e-4, 0.5);
	if (key == XK_Delete && app->selected != 0x7fffffff)
	{
		scene_group_delete(&app->scene, app->selected);
		app->selected = 0x7fffffff;
		bvh_rebuild(app);
		phys_rebuild_body_table(app);
		app->dirty = 1;
	}
	key_set(&app->input, key, 1);
	return (0);
}

int	on_keyup(int key, t_app *app)
{
	key_set(&app->input, key, 0);
	return (0);
}

static void	handle_mouse_wheel(int btn, t_app *app)
{
	int		delta;
	float	dz;

	delta = 1;
	if (btn == 4)
		delta = -1;
	if (app->ui.consume_input)
		app->input.mouse_wheel = delta;
	else if (key_held(&app->input, KEY_LCTRL))
	{
		app->scene.cam.fov = ft_clampf(app->scene.cam.fov - delta * 2.0f, 20.0f, 180.0f);
		app->dirty = 1;
	}
	else
	{
		dz = delta * 3.0f;
		app->scene.cam.pos = v3_add(app->scene.cam.pos,
				v3_mul(app->scene.cam.dir, dz * 0.5f));
		app->dirty = 1;
	}
}

int	on_mousedown(int btn, int x, int y, t_app *app)
{
	app->input.mouse_x = x;
	app->input.mouse_y = y;
	if (btn == 1)
	{
		app->input.mouse_left = 1;
		if (app->ui.consume_input)
			app->input.mouse_left_clicked = 1;
	}
	if (btn == 2)
		app->input.mouse_middle = 1;
	if (btn == 3)
	{
		app->input.mouse_right = 1;
		if (!app->ui.consume_input)
		{
			app->input.rmb_cam_drag = 1;
			app->input.rmb_press_x = x;
			app->input.rmb_press_y = y;
			app->input.rmb_drag_dist = 0;
			app->input.last_mx = x;
			app->input.last_my = y;
			app->input.first_motion = 1;
		}
	}
	if (btn == 4 || btn == 5)
		handle_mouse_wheel(btn, app);
	return (0);
}

int	on_mouseup(int btn, int x, int y, t_app *app)
{
	int	id;

	(void)x;
	(void)y;
	if (btn == 1)
	{
		app->input.mouse_left = 0;
		if (!app->input.lmb_cam_drag && app->input.lmb_drag_dist <= 5
			&& !app->ui.consume_input)
		{
			id = pick_at(app, app->input.mouse_x, app->input.mouse_y);
			app->selected = id;
		}
		app->input.lmb_cam_drag = 0;
		app->input.lmb_drag_dist = 0;
	}
	if (btn == 2)
	{
		app->input.mouse_middle = 0;
		app->input.mouse_middle_clicked = 1;
	}
	if (btn == 3)
	{
		app->input.mouse_right = 0;
		if (app->input.rmb_cam_drag && app->input.rmb_drag_dist <= 5)
			app->input.mouse_right_clicked = 1;
		app->input.rmb_cam_drag = 0;
	}
	return (0);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	on_mousemove(int x, int y, t_app *app)
{
	int	dx;
	int	dy;

	app->input.mouse_x = x;
	app->input.mouse_y = y;
	if (app->input.lmb_cam_drag || app->input.rmb_cam_drag)
	{
		if (app->input.first_motion)
		{
			app->input.last_mx = x;
			app->input.last_my = y;
			app->input.first_motion = 0;
		}
		dx = x - app->input.last_mx;
		dy = y - app->input.last_my;
		app->input.mouse_dx += dx;
		app->input.mouse_dy += dy;
		app->input.last_mx = x;
		app->input.last_my = y;
		if (app->input.lmb_cam_drag)
			app->input.lmb_drag_dist += ft_abs(dx) + ft_abs(dy);
		if (app->input.rmb_cam_drag)
			app->input.rmb_drag_dist += ft_abs(dx) + ft_abs(dy);
	}
	return (0);
}

int	on_close(t_app *app)
{
	app->running = 0;
	mlx_loop_end(app->mlx);
	return (0);
}