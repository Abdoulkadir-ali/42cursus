/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 20:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static t_key_action	*get_keymap(void)
{
	static t_key_action	keymap[] = {
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

	return (keymap);
}

int	key_press(int keycode, t_gui *gui)
{
	t_key_action	*keymap;
	int				i;

	if (!gui->cam_ctrl.camera)
		return (0);
	/* Toggle physics simulation with P */
	if (keycode == XK_p || keycode == XK_P)
	{
		gui->physics_enabled = !gui->physics_enabled;
		gui->render.dirty = true;
		return (0);
	}
	/* Adjust ambient intensity with [ and ] */
	if (keycode == XK_bracketleft)
	{
		gui->ambient_intensity -= 0.05;
		if (gui->ambient_intensity < 0.0)
			gui->ambient_intensity = 0.0;
		gui->render.dirty = true;
		return (0);
	}
	if (keycode == XK_bracketright)
	{
		gui->ambient_intensity += 0.05;
		if (gui->ambient_intensity > 2.0)
			gui->ambient_intensity = 2.0;
		gui->render.dirty = true;
		return (0);
	}
	/* Adjust ambient color with R, G, B */
	if (keycode == XK_r)
	{
		int c = (gui->ambient_color >> 16) & 0xFF;
		c = (c > 0) ? c - 8 : 0;
		gui->ambient_color = (gui->ambient_color & 0xFF00FFFF) | (c << 16);
		gui->render.dirty = true;
		return (0);
	}
	if (keycode == XK_R)
	{
		int c = (gui->ambient_color >> 16) & 0xFF;
		c = (c < 255) ? c + 8 : 255;
		gui->ambient_color = (gui->ambient_color & 0xFF00FFFF) | (c << 16);
		gui->render.dirty = true;
		return (0);
	}
	if (keycode == XK_g)
	{
		int c = (gui->ambient_color >> 8) & 0xFF;
		c = (c > 0) ? c - 8 : 0;
		gui->ambient_color = (gui->ambient_color & 0xFFFF00FF) | (c << 8);
		gui->render.dirty = true;
		return (0);
	}
	if (keycode == XK_G)
	{
		int c = (gui->ambient_color >> 8) & 0xFF;
		c = (c < 255) ? c + 8 : 255;
		gui->ambient_color = (gui->ambient_color & 0xFFFF00FF) | (c << 8);
		gui->render.dirty = true;
		return (0);
	}
	if (keycode == XK_b)
	{
		int c = gui->ambient_color & 0xFF;
		c = (c > 0) ? c - 8 : 0;
		gui->ambient_color = (gui->ambient_color & 0xFFFFFF00) | c;
		gui->render.dirty = true;
		return (0);
	}
	if (keycode == XK_B)
	{
		int c = gui->ambient_color & 0xFF;
		c = (c < 255) ? c + 8 : 255;
		gui->ambient_color = (gui->ambient_color & 0xFFFFFF00) | c;
		gui->render.dirty = true;
		return (0);
	}
	keymap = get_keymap();
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
	t_key_action	*keymap;
	int				i;

	if (!gui->cam_ctrl.camera)
		return (0);
	keymap = get_keymap();
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
