/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_widget.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:59:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 10:34:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_WIDGET_H
# define GUI_WIDGET_H

# include "t_maths.h"
# include "t_physics.h"

# define WIDGET_INPUT_BUF_SIZE	256
# define WIDGET_MSG_BTN_MAX		4
# define WIDGET_TITLE_H			18

struct s_gui;
typedef struct s_widget	t_widget;

typedef void			(*t_widget_callback)(t_widget *widget,
				struct s_gui *gui);

typedef enum e_widget_type
{
	WIDGET_LABEL,
	WIDGET_BUTTON,
	WIDGET_TOGGLE,
	WIDGET_CHECKBOX,
	WIDGET_SLIDER,
	WIDGET_INPUT_BOX,
	WIDGET_PROGRESS_BAR,
	WIDGET_SEPARATOR,
	WIDGET_COLOR_PICKER,
	WIDGET_MESSAGE_BOX,
	WIDGET_PANEL
}						t_widget_type;

typedef struct s_widget
{
	t_widget_type		type;
	t_vec2i				pos;
	t_vec2i				size;
	char				*label;
	int					value;
	int					color;
	double				dvalue;
	double				dmin;
	double				dmax;
	double				progress;
	void				*target;
	t_widget_callback	on_click;
	t_widget_callback	on_change;
	void				*userdata;
	t_widget			*next;
	/* draggable window */
	bool				draggable;
	bool				being_dragged;
	t_vec2i				drag_offset;
	/* focus / visibility */
	bool				focused;
	bool				visible;
	/* input box */
	char				input_buf[WIDGET_INPUT_BUF_SIZE];
	int					cursor_pos;
	/* message box */
	char				*msg_text;
	int					btn_count;
	const char			*btn_labels[WIDGET_MSG_BTN_MAX];
	t_widget_callback	btn_callbacks[WIDGET_MSG_BTN_MAX];
}						t_widget;

typedef struct s_hover_cache
{
	t_vec2i				mouse;
	bool				active;
	bool				hit;
	long				last_frame;
}						t_hover_cache;

t_widget				*widget_create(t_widget_type type, t_vec2i pos,
							t_vec2i size, const char *label);
void					widget_add(struct s_gui *gui, t_widget *widget);
void					widget_draw_all(struct s_gui *gui);
void					widget_handle_mouse(struct s_gui *gui, int button,
							t_vec2i mouse);
void					widget_handle_motion(struct s_gui *gui, t_vec2i mouse);
void					widget_handle_release(struct s_gui *gui);
void					widget_handle_key(struct s_gui *gui, int keycode);
void					widget_init_default(struct s_gui *gui);
t_widget				*widget_make_msgbox(const char *title,
							const char *msg, t_vec2i pos);

void					widget_draw_checkbox(struct s_gui *gui, t_widget *w);
void					widget_draw_slider(struct s_gui *gui, t_widget *w);
void					widget_draw_input(struct s_gui *gui, t_widget *w);
void					widget_draw_button(struct s_gui *gui, t_widget *w);
void					widget_draw_toggle(struct s_gui *gui, t_widget *w);
void					widget_draw_progress(struct s_gui *gui, t_widget *w);
void					widget_draw_separator(struct s_gui *gui, t_widget *w);
void					widget_draw_msgbox(struct s_gui *gui, t_widget *w);

#endif
