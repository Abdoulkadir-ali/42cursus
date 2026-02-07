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

typedef struct s_key_action
{
	int				key;
	void			(*press_action)(t_gui *gui);
	void			(*release_action)(t_gui *gui);
}					t_key_action;

// Action functions
static void	move_forward_press(t_gui *gui)
{
	gui->move_forward_count++;
	gui->moving_forward = (gui->move_forward_count > 0);
}

static void	move_forward_release(t_gui *gui)
{
	gui->move_forward_count--;
	gui->moving_forward = (gui->move_forward_count > 0);
}

static void	move_backward_press(t_gui *gui)
{
	gui->move_backward_count++;
	gui->moving_backward = (gui->move_backward_count > 0);
}

static void	move_backward_release(t_gui *gui)
{
	gui->move_backward_count--;
	gui->moving_backward = (gui->move_backward_count > 0);
}

static void	move_left_press(t_gui *gui)
{
	gui->move_left_count++;
	gui->moving_left = (gui->move_left_count > 0);
}

static void	move_left_release(t_gui *gui)
{
	gui->move_left_count--;
	gui->moving_left = (gui->move_left_count > 0);
}

static void	move_right_press(t_gui *gui)
{
	gui->move_right_count++;
	gui->moving_right = (gui->move_right_count > 0);
}

static void	move_right_release(t_gui *gui)
{
	gui->move_right_count--;
	gui->moving_right = (gui->move_right_count > 0);
}

static void	move_up_press(t_gui *gui)
{
	gui->move_up_count++;
	gui->moving_up = (gui->move_up_count > 0);
}

static void	move_up_release(t_gui *gui)
{
	gui->move_up_count--;
	gui->moving_up = (gui->move_up_count > 0);
}

static void	move_down_press(t_gui *gui)
{
	gui->move_down_count++;
	gui->moving_down = (gui->move_down_count > 0);
}

static void	move_down_release(t_gui *gui)
{
	gui->move_down_count--;
	gui->moving_down = (gui->move_down_count > 0);
}

static void	zoom_in_press(t_gui *gui)
{
	gui->zoom_in_count++;
	gui->zooming_in = (gui->zoom_in_count > 0);
}

static void	zoom_in_release(t_gui *gui)
{
	gui->zoom_in_count--;
	gui->zooming_in = (gui->zoom_in_count > 0);
}

static void	zoom_out_press(t_gui *gui)
{
	gui->zoom_out_count++;
	gui->zooming_out = (gui->zoom_out_count > 0);
}

static void	zoom_out_release(t_gui *gui)
{
	gui->zoom_out_count--;
	gui->zooming_out = (gui->zoom_out_count > 0);
}

static void	speed_up_press(t_gui *gui)
{
	gui->move_speed += 0.01;
	if (gui->move_speed > 2.0)
		gui->move_speed = 2.0;
}

static void	speed_down_press(t_gui *gui)
{
	gui->move_speed -= 0.01;
	if (gui->move_speed < 0.001)
		gui->move_speed = 0.001;
}

static void	exit_press(t_gui *gui)
{
	mlx_loop_end(gui->mlx);
}

// Keymap
static t_key_action	keymap[] = {
	{XK_w, move_forward_press, move_forward_release},
	{XK_s, move_backward_press, move_backward_release},
	{XK_a, move_left_press, move_left_release},
	{XK_d, move_right_press, move_right_release},
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
	{0, NULL, NULL} // Sentinel
};

int	key_press(int keycode, t_gui *gui)
{
	int	i;

	if (!gui->camera)
		return (0);
	i = 0;
	while (keymap[i].key != 0)
	{
		if (keymap[i].key == keycode && keymap[i].press_action)
		{
			keymap[i].press_action(gui);
			return (0);
		}
		i++;
	}
	return (0);
}

int	key_release(int keycode, t_gui *gui)
{
	int	i;

	if (!gui->camera)
		return (0);
	i = 0;
	while (keymap[i].key != 0)
	{
		if (keymap[i].key == keycode && keymap[i].release_action)
		{
			keymap[i].release_action(gui);
			return (0);
		}
		i++;
	}
	return (0);
}