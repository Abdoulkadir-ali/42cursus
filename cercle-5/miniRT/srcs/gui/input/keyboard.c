/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/04 02:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/*
** Forward movement action.
*/
static void	move_forward_press(t_gui *gui)
{
	gui->cam_ctrl.moving_forward = true;
}

static void	move_forward_release(t_gui *gui)
{
	gui->cam_ctrl.moving_forward = false;
}

/*
** Backward movement action.
*/
static void	move_backward_press(t_gui *gui)
{
	gui->cam_ctrl.moving_backward = true;
}

static void	move_backward_release(t_gui *gui)
{
	gui->cam_ctrl.moving_backward = false;
}

/*
** Left movement action.
*/
static void	move_left_press(t_gui *gui)
{
	gui->cam_ctrl.moving_left = true;
}

static void	move_left_release(t_gui *gui)
{
	gui->cam_ctrl.moving_left = false;
}

/*
** Right movement action.
*/
static void	move_right_press(t_gui *gui)
{
	gui->cam_ctrl.moving_right = true;
}

static void	move_right_release(t_gui *gui)
{
	gui->cam_ctrl.moving_right = false;
}

/*
** Up movement action (Space).
*/
static void	move_up_press(t_gui *gui)
{
	gui->cam_ctrl.moving_up = true;
}

static void	move_up_release(t_gui *gui)
{
	gui->cam_ctrl.moving_up = false;
}

/*
** Down movement action (Shift).
*/
static void	move_down_press(t_gui *gui)
{
	gui->cam_ctrl.moving_down = true;
}

static void	move_down_release(t_gui *gui)
{
	gui->cam_ctrl.moving_down = false;
}

/*
** Zoom in action.
*/
static void	zoom_in_press(t_gui *gui)
{
	gui->cam_ctrl.zooming_in = true;
}

static void	zoom_in_release(t_gui *gui)
{
	gui->cam_ctrl.zooming_in = false;
}

/*
** Zoom out action.
*/
static void	zoom_out_press(t_gui *gui)
{
	gui->cam_ctrl.zooming_out = true;
}

static void	zoom_out_release(t_gui *gui)
{
	gui->cam_ctrl.zooming_out = false;
}

/*
** Speed control actions.
*/
static void	speed_up_press(t_gui *gui)
{
	gui->cam_ctrl.move_speed += 0.1;
	if (gui->cam_ctrl.move_speed > 10.0)
		gui->cam_ctrl.move_speed = 10.0;
}

static void	speed_down_press(t_gui *gui)
{
	gui->cam_ctrl.move_speed -= 0.1;
	if (gui->cam_ctrl.move_speed < 0.1)
		gui->cam_ctrl.move_speed = 0.1;
}

/*
** Map switching and exit actions.
*/
static void	map_next_press(t_gui *gui)
{
	gui_next_map(gui);
}

static void	exit_press(t_gui *gui)
{
	mlx_loop_end(gui->win.mlx);
}

// Keymap array
static t_key_action	g_keymap[] = {
	{XK_w, move_forward_press, move_forward_release},
	{XK_z, move_forward_press, move_forward_release},
	{XK_s, move_backward_press, move_backward_release},
	{XK_a, move_left_press, move_left_release},
	{XK_q, move_left_press, move_left_release},
	{XK_d, move_right_press, move_right_release},
	{XK_n, map_next_press, NULL},
	{XK_Up, speed_up_press, NULL},
	{XK_Down, speed_down_press, NULL},
	{XK_Left, move_left_press, move_left_release},
	{XK_Right, move_right_press, move_right_release},
	{XK_space, move_up_press, move_up_release},
	{XK_Shift_L, move_down_press, move_down_release},
	{XK_plus, zoom_in_press, zoom_in_release},
	{XK_equal, zoom_in_press, zoom_in_release},
	{XK_minus, zoom_out_press, zoom_out_release},
	{XK_Escape, exit_press, NULL},
	{0, NULL, NULL}
};

/*
** Handles key press events.
*/
int	key_press(int keycode, t_gui *gui)
{
	int	i;

	if (!gui->cam_ctrl.camera)
		return (0);
	i = 0;
	while (g_keymap[i].key != 0)
	{
		if (g_keymap[i].key == keycode && g_keymap[i].press_action)
		{
			g_keymap[i].press_action(gui);
			return (0);
		}
		i++;
	}
	return (0);
}

/*
** Handles key release events.
*/
int	key_release(int keycode, t_gui *gui)
{
	int	i;

	if (!gui->cam_ctrl.camera)
		return (0);
	i = 0;
	while (g_keymap[i].key != 0)
	{
		if (g_keymap[i].key == keycode && g_keymap[i].release_action)
		{
			g_keymap[i].release_action(gui);
			return (0);
		}
		i++;
	}
	return (0);
}