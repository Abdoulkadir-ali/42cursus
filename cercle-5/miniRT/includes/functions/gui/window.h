/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:01:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 12:19:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_FUNCTIONS_WINDOW_H
# define GUI_FUNCTIONS_WINDOW_H

# include "types.h"
# include "mlx.h"
#include <X11/Xlib.h>

# define PANEL_RADIUS 6
# define COL_BG 0x0A0A12
# define COL_ACCENT 0xE0A820
# define COL_FPS 0x20E060
# define COL_TEXT 0xD0D0D8
# define COL_HOVER 0x20C8D0
# define COL_BORDER 0x333340

/* Toggle Colors */
# define COL_INSP_OFF_BG 0x402020
# define COL_INSP_OFF_TEXT 0xFF5050
# define COL_INSP_ON_BG 0x206040
# define COL_INSP_ON_TEXT 0x40FF80

/* CRUD & Modal Colors */
# define COL_MODAL_BG 0x0D0D14
# define COL_POPUP_BG 0x1A1A28
# define COL_CRUD_BG 0x12121C
# define COL_CRUD_BTN_BG 0x22222E
# define COL_CRUD_BTN_POPUP 0x2A2A3A
# define COL_CRUD_BTN_DEL 0x38161A

/* UI Shades & Accents */
# define COL_UI_GRAY 0x505060
# define COL_UI_DARK_GRAY 0x404050
# define COL_UI_MUTED 0x606070
# define COL_UI_BLUE 0x60A0E0
# define COL_UI_LIGHT_BLUE 0xA0C8FF
# define COL_UI_BLACK 0x000000

/* Component Specific */
# define COL_SCENE_ITEM_BG 0x141420
# define COL_SCENE_ITEM_ALT 0x0E0E1A
# define COL_WIDGET_TITLE 0x1A1A2A
# define COL_MSGBOX_BG 0x12121E
# define COL_KNOB 0xE0E0E0
# define COL_ERROR 0xFF4444
# define COL_RED_SOFT 0xFF6666

/* Prototypes */
t_gui	*gui_init(t_scene *scene, void *mlx);
void			gui_destroy(t_gui *gui);
void			gui_loop(t_gui *gui);
int						gui_window_resize(t_vec2s size, t_gui *gui);
int				gui_resize_hook(t_gui *gui);
int				gui_window_close(t_gui *gui);
void			gui_draw_string(t_gui *gui, const char *str, t_vec2i pos,
					unsigned int color);
void			draw_panel(t_gui *gui, t_panel panel);
void			draw_ui_panels(t_gui *gui);
void			draw_ui_pixels(t_gui *gui);
void			draw_ui_strings(t_gui *gui, t_camera_controller *ctrl);
void			draw_ui_help(t_gui *gui, int *y);
void			draw_ui_status(t_gui *gui, int *y);
void			draw_ui_object(t_gui *gui);


#endif
