/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:30:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/25 16:51:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static t_key_action *get_keymap(void)
{
    static t_key_action keymap[] = {
        {XK_w, move_forward_press, move_forward_release},
        {XK_z, move_forward_press, move_forward_release},
        {XK_s, move_backward_press, move_backward_release},
        {XK_a, move_left_press, move_left_release},
        {XK_q, move_left_press, move_left_release},
        {XK_d, move_right_press, move_right_release},
        {XK_n, map_next_press, NULL},
        {XK_p, map_prev_press, NULL},
        {XK_P, map_prev_press, NULL},
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
        {XK_f, fullres_toggle, NULL},
        {0, NULL, NULL}
    };

    return (keymap);
}

static bool	handle_special_key(int keycode, t_gui *gui)
{
    if (keycode == XK_Shift_L || keycode == XK_Shift_R)
        gui->crud.shift_held = true;
    if (popup_handle_key(gui, keycode))
        return (true);
    if (keycode == XK_Escape && gui->crud.popup != POPUP_NONE)
    {
        gui->crud.popup = POPUP_NONE;
        gui->render.dirty = true;
        return (true);
    }
    if (keycode == XK_x || keycode == XK_X)
    {
        gui->physics_enabled = !gui->physics_enabled;
        gui->render.dirty = true;
        return (true);
    }
    if (keycode == XK_r)
    {
        scene_reset(gui);
        return (true);
    }
    return (false);
}

int	key_press(int keycode, t_gui *gui)
{
    t_key_action *keymap;
    size_t i;

    if (!gui->cam_ctrl.camera)
        return (0);
    if (handle_special_key(keycode, gui))
        return (0);
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
