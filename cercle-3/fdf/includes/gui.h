/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:39 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 17:43:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include <mlx.h>
# include <string.h>

// Header imports
# include "define.h"
# include "geometry.h"
# include "graphics.h"
# include "libft.h"
# include "render.h"
# include "window.h"

typedef struct s_events	t_events;

typedef struct s_gui_args
{
	t_window			*window;
	t_camera			*camera;
	t_maps				*maps;
	t_render_config		*render_config;
	t_map				*map;
}						t_gui_args;

typedef struct s_gui
{
	t_window			*window;
	int					gui_style;
	t_maps				*maps;
	t_render_config		*render_config;
	t_camera			*camera;
	t_map				*map;
	int					fps;
	size_t				last_win_height;
}						t_gui;

/* ========== LAYOUT ENGINE CONTEXT ========== */
typedef struct s_layout
{
	t_gui				*gui;
	int					cursor_y;
	int					padding;
	int					panel_width;
	int					x_start;
}						t_layout;

/* ========== GUI STYLE ========== */
typedef struct s_gui_theme
{
	int					background;
	int					border;
	int					text_primary;
	int					text_secondary;
	int					accent;
	int					highlight;
}						t_gui_theme;

typedef struct s_colored_text
{
	char				*text;
	int					color;
}						t_colored_text;

/* ========== GUI FUNCTIONS ========== */
void					redraw_gui(t_events *events);
void					draw_panel_background(t_gui *gui);
void					clear_gui(t_gui *gui);

/* Text Helpers */
void					put_text(t_gui *gui, int x, int y, char *text);
void					put_key(t_gui *gui, int x, int y, char *text);
void					put_value(t_gui *gui, int x, int y, char *text);
void					put_colored(t_gui *gui, int x, int y,
							t_colored_text colored);

/* Formatting Helpers */
void					format_speed(double speed, char *buffer);
void					format_number(long long num, char *buffer);
void					format_float(double val, char *buffer);

/* Axis Indicator */
void					draw_axis_indicator(t_gui *gui);

/* Layout Engine API */
void					gui_layout_init(t_layout *l, t_gui *gui);
void					gui_layout_add_spacer(t_layout *l, int size);
void					gui_layout_title(t_layout *l, char *text);
void					gui_layout_label(t_layout *l, char *text);
void					gui_layout_key_value(t_layout *l, char *key, char *val);

/* Section Drawers (Updated to use t_layout) */
void					draw_controls_guide_layout(t_layout *l, t_gui *gui);
void					draw_performance_display_layout(t_layout *l,
							t_gui *gui);
void					draw_projection_display_layout(t_layout *l, t_gui *gui);
void					draw_speed_display_layout(t_layout *l, t_gui *gui);
void					draw_map_name_display_layout(t_layout *l, t_gui *gui);
void					draw_transform_stats(t_gui *gui);

void					cycle_gui_style(t_gui *gui);

t_gui_theme				get_gui_theme(t_gui_style style);
t_gui_theme				get_tron_blue_theme(void);
t_gui_theme				get_tron_orange_theme(void);
t_gui_theme				get_matrix_theme(void);
t_gui_theme				get_cyberpunk_theme(void);
t_gui_theme				get_neon_grid_theme(void);

t_gui					*init_gui(t_gui_args args);
int						init_gui_images(t_gui *gui);

#endif
