/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_forward.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 16:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static t_key_action	*get_keymap(void)
{
	static t_key_action	keymap[] = {
	{XK_z, move_forward_press, move_forward_release},
	{XK_s, move_backward_press, move_backward_release},
	{XK_q, move_left_press, move_left_release},
	{XK_d, move_right_press, move_right_release},
	
	{XK_a, auto_fullres_toggle, NULL},
	{XK_n, map_next_press, NULL},
	{XK_p, map_prev_press, NULL},
	{XK_Up, speed_up_press, NULL},
	{XK_Down, speed_down_press, NULL},
	{XK_Left, move_left_press, move_left_release},
	{XK_Right, move_right_press, move_right_release},
	{XK_space, move_up_press, move_up_release},
	{XK_Shift_L, move_down_press, move_down_release},
	{XK_plus, zoom_in_press, zoom_in_release},
	{XK_equal, zoom_in_press, zoom_in_release},
	{XK_f, fullres_toggle, NULL},
	{XK_b, bake_toggle, NULL},
	{XK_Escape, exit_press, NULL},
	{0, NULL, NULL}};

	return (keymap);
}

static void	handle_misc_keys(int code, t_gui *gui)
{
	if (code == XK_Escape && gui->crud.popup != POPUP_NONE)
	{
		gui->crud.popup = POPUP_NONE;
		gui->render.dirty = true;
	}
	else if (code == XK_x || code == XK_X)
	{
		gui->physics_enabled = !gui->physics_enabled;
		gui->render.dirty = true;
	}
	else if (code == XK_r)
		scene_reset(gui);
}

static bool	handle_input_capture(t_gui *gui, int keycode)
{
	if (gui->slider_state.insp_edit.active)
	{
		insp_input_key(gui, keycode);
		if (keycode != XK_Escape)
			return (true);
	}
	if (gui->focused_widget)
	{
		widget_handle_key(gui, keycode);
		if (keycode != XK_Escape)
			return (true);
	}
	return (false);
}

int	key_press(int keycode, t_gui *gui)
{
	t_key_action	*keymap;
	size_t			i;

	if (!gui->cam_ctrl.camera)
		return (0);
	if (keycode == XK_Shift_L || keycode == XK_Shift_R)
		gui->crud.shift_held = true;
	if (handle_input_capture(gui, keycode))
		return (0);
	if (popup_handle_key(gui, keycode))
		return (0);
	handle_misc_keys(keycode, gui);
	keymap = get_keymap();
	i = 0;
	while (keymap[i].key != 0)
	{
		if (keymap[i].key == keycode && keymap[i].press_action)
			return (keymap[i].press_action(gui), 0);
		i++;
	}
	return (0);
}

int	key_release(int keycode, t_gui *gui)
{
	t_key_action	*keymap;
	size_t			i;

	if (!gui->cam_ctrl.camera)
		return (0);
	if (keycode == XK_Shift_L || keycode == XK_Shift_R)
		gui->crud.shift_held = false;
	keymap = get_keymap();
	i = 0;
	while (keymap[i].key != 0)
	{
		if (keymap[i].key == keycode && keymap[i].release_action)
			return (keymap[i].release_action(gui), 0);
		i++;
	}
	return (0);
}
