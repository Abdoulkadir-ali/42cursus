/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widget.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:59:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 19:59:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_WIDGET_H
# define GUI_WIDGET_H

# include "core.h"
# include "physics.h"
# include "maths.h"

typedef enum e_widget_type
{
	WIDGET_LABEL,
	WIDGET_BUTTON,
	WIDGET_CHECKBOX,
	WIDGET_SLIDER,
	WIDGET_COLOR_PICKER,
	WIDGET_PANEL
} t_widget_type;

typedef struct s_widget t_widget;

typedef void (*t_widget_callback)(t_widget *widget, struct s_gui *gui);

struct s_widget
{
	t_widget_type type;
	t_vec2i pos;
	t_vec2i size;
	char *label;
	int value;
	int color;
	double dvalue;
	double dmin;
	double dmax;
	void *target;
	t_widget_callback on_click;
	t_widget_callback on_change;
	void *userdata;
	t_widget *next;
};

typedef struct s_hover_cache
{
	int x;
	int y;
	bool active;
	bool hit;
	long last_frame;
}	t_hover_cache;

t_widget	*widget_create(t_widget_type type, t_vec2i pos, t_vec2i size,
		const char *label);
void	widget_add(struct s_gui *gui, t_widget *widget);
void	widget_draw_all(struct s_gui *gui);
void	widget_handle_mouse(struct s_gui *gui, int button, t_vec2i mouse);
void	widget_handle_key(struct s_gui *gui, int keycode);
void	widget_init_default(struct s_gui *gui);

void	widget_draw_checkbox(struct s_gui *gui, t_widget *w);
void	widget_draw_slider(struct s_gui *gui, t_widget *w);

#endif
