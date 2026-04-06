/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 01:24:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_SETTINGS_H
# define GUI_SETTINGS_H

# include "editor.h"

# define SETTINGS_W			400
# define SETTINGS_H			580
# define SETTINGS_BTN_W		88
# define SETTINGS_BTN_H		22
# define SETTINGS_TAB_COUNT	3
# define SETTINGS_HDR_H		36
# define SETTINGS_TABS_H	28
# define SETTINGS_CONTENT_Y	(SETTINGS_HDR_H + SETTINGS_TABS_H)
# define SETTINGS_ROW_H		30

/* Inline radio descriptor — analogous to t_islider */
typedef struct s_iradio
{
	const char		*label;
	bool			*ptr;
	void			(*on_change)(struct s_gui *);
}	t_iradio;

/* srcs/gui/settings/settings.c */
void	settings_init(struct s_gui *gui);
void	settings_open(struct s_gui *gui);
void	settings_close(struct s_gui *gui);
void	draw_settings(struct s_gui *gui);
bool	settings_handle_click(struct s_gui *gui, t_vec2i mouse);
void	settings_handle_drag(struct s_gui *gui, t_vec2i mouse);
void	settings_end_drag(struct s_gui *gui);

/* srcs/gui/settings/utils.c */
void	draw_radio_row(struct s_gui *gui, t_panel pan, t_iradio r);t_iradio	init_iradio(const char *label, bool *ptr,
			void (*on_change)(t_gui *));bool	try_radio_click(struct s_gui *gui, t_vec2i mouse, t_panel pan,
			t_iradio r);
void	draw_settings_slider(struct s_gui *gui, t_vec2i pos, t_islider sl);
bool	try_settings_slider_click(struct s_gui *gui, t_vec2i mouse,
					t_vec2i pos, t_islider sl);

/* srcs/gui/settings/tabs/window.c */
void	draw_settings_window_tab(struct s_gui *gui, t_vec2i o);
bool	click_settings_window_tab(struct s_gui *gui, t_vec2i mouse, t_vec2i o);

/* srcs/gui/settings/tabs/physics.c */
void	draw_settings_physics_tab(struct s_gui *gui, t_vec2i o);
bool	click_settings_physics_tab(struct s_gui *gui, t_vec2i mouse, t_vec2i o);

/* srcs/gui/settings/tabs/raytracer.c */
void	draw_settings_raytracer_tab(struct s_gui *gui, t_vec2i o);
bool	click_settings_raytracer_tab(struct s_gui *gui, t_vec2i mouse,
			t_vec2i o);
void	apply_preset(struct s_gui *gui, t_rt_preset p);
void	on_color_change(struct s_gui *gui);

#endif
