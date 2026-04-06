/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widget.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:59:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 12:33:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_FUNCTIONS_WIDGET_H
# define GUI_FUNCTIONS_WIDGET_H

# include "gui.h"

bool		hit_titlebar(t_widget *w, t_vec2i m);
bool		hit_body(t_widget *w, t_vec2i m);
bool		handle_msgbox_click(struct s_gui *gui, t_widget *w, t_vec2i m);
t_widget	*widget_create(t_widget_type type, t_vec2i pos, t_vec2s size,
		const char *label);
t_widget	*widget_make_msgbox(const char *title, const char *msg,
		t_vec2i pos);
void		widget_add(struct s_gui *gui, t_widget *widget);
void		widget_draw_all(struct s_gui *gui);
void		widget_handle_mouse(struct s_gui *gui, int button, t_vec2i mouse);
void		widget_handle_motion(struct s_gui *gui, t_vec2i mouse);
void		widget_handle_release(struct s_gui *gui);
void		widget_handle_key(struct s_gui *gui, int keycode);
void		widget_init_default(struct s_gui *gui);

void		widget_draw_checkbox(struct s_gui *gui, t_widget *w);
void		widget_draw_slider(struct s_gui *gui, t_widget *w);
void		widget_draw_input(struct s_gui *gui, t_widget *w);
void		widget_draw_button(struct s_gui *gui, t_widget *w);
void		widget_draw_toggle(struct s_gui *gui, t_widget *w);
void		widget_draw_progress(struct s_gui *gui, t_widget *w);
void		widget_draw_separator(struct s_gui *gui, t_widget *w);
void		widget_draw_msgbox(struct s_gui *gui, t_widget *w);

void		slider_begin_drag(struct s_gui *gui, t_widget *w, int mouse_x);
void		slider_update_drag(struct s_gui *gui, int mouse_x);
void		slider_end_drag(struct s_gui *gui);
bool		slider_handle_click(struct s_gui *gui, t_widget *w, t_vec2i mouse);

void		gui_label(struct s_gui *gui, const char *text, t_vec2i pos);
void			gui_panel(struct s_gui *gui, t_vec2i pos, t_vec2s size,
		const char *title);

#endif
