/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:01:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 18:43:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_FUNCTIONS_WINDOW_H
# define GUI_FUNCTIONS_WINDOW_H

# include "types.h"
# include "mlx.h"


# define PANEL_RADIUS 6
# define COL_BG 0x0A0A12
# define COL_ACCENT 0xE0A820
# define COL_FPS 0x20E060
# define COL_TEXT 0xD0D0D8
# define COL_HOVER 0x20C8D0
# define COL_BORDER 0x333340

/* Prototypes */
t_gui	*gui_init(t_scene *scene, void *mlx);
void			gui_destroy(t_gui *gui);
void			gui_loop(t_gui *gui);
int				gui_window_resize(t_vec2i size, t_gui *gui);
int				gui_window_close(t_gui *gui);
void			gui_draw_string(t_gui *gui, const char *str, t_vec2i pos,
					unsigned int color);
void			draw_panel(t_gui *gui, t_panel panel);
void			draw_ui_panels(t_gui *gui);
void			draw_ui_help(t_gui *gui, int *y);
void			draw_ui_status(t_gui *gui, int *y);
void			draw_ui_object(t_gui *gui);
void			draw_ui_text(t_gui *gui, t_camera_controller *ctrl);
void			draw_hover_text(t_gui *gui);

#endif
