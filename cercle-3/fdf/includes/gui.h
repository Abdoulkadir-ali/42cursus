/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:39 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/25 22:26:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include <mlx.h>
# include <string.h>

// Header imports

# include "geometry.h"
# include "graphics.h"
# include "libft.h"
# include "primitives.h"
# include "render.h"
# include "window.h"

# define AXIS_SIZE 40
# define AXIS_MARGIN 20
# define AXIS_SIZE 40
# define AXIS_MARGIN 20

typedef struct s_events	t_events;

typedef struct s_axis_info
{
	t_vec3d				axis;
	int					color;
	char				label;
}						t_axis_info;

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

typedef struct s_point_stats_ctx
{
	size_t				total;
	size_t				active;
	int					level;
	double				multiplier;
	float				lod;
}						t_point_stats_ctx;

typedef struct s_colored_text
{
	char				*text;
	int					color;
}						t_colored_text;

/* ========== GUI FUNCTIONS ========== */
void					redraw_gui(t_events *events);
void					draw_panel_background(t_gui *gui);
void					clear_gui(t_gui *gui);
void					draw_rect(t_gui *gui, t_vec2 pos, t_vec2 size,
							int color);

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
int						normalize_angle(double radians);

/* Axis Indicator */
void					draw_axis_indicator(t_gui *gui);
void					draw_axis_line(t_gui *gui, t_vec2 center, t_vec3d axis,
							int color);
void					draw_axis_labels(t_gui *gui, t_vec2 center);
void					draw_rotation_section(t_layout *l);
void					draw_mouse_controls(t_layout *l);
void					draw_keyboard_controls(t_layout *l);
void					draw_combos_section(t_layout *l, t_gui *gui);
void					draw_optimizations_section(t_layout *l);

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
void					draw_map_layout(t_layout *l, t_gui *gui);
void					display_point_stats(t_layout *l, t_gui *gui,
							char *buffer);
void					display_toggle_options(t_layout *l, t_gui *gui,
							char *buffer);
void					display_algorithm_info(t_layout *l, t_gui *gui);
void					display_tesselation_info(t_layout *l, t_gui *gui,
							char *buffer);
void					display_fps_stats(t_layout *l, t_gui *gui,
							char *buffer);
void					display_pos_stats(t_layout *l, t_gui *gui,
							char *buffer);
void					display_rot_stats(t_layout *l, t_gui *gui,
							char *buffer);
void					display_scale_stats(t_layout *l, t_gui *gui,
							char *buffer);
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
