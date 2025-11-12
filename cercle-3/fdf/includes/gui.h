/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:39 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 18:32:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include "vectors.h"
# include <mlx.h>

typedef struct s_data	t_data;

typedef struct s_image
{
	void				*img;
	char				*img_addr;
	int					img_bpp;
	int					img_line_len;
	int					img_endian;
}						t_image;

typedef struct s_window
{
	void				*mlx_ptr;
	void				*ptr;
	int					width;
	int					height;

	t_image				main_img;
	t_image				gui_img;
	float				*z_buffer;
}						t_window;

/* ========== GUI STYLE ========== */
typedef enum e_gui_style
{
	GUI_STYLE_TRON_BLUE,
	GUI_STYLE_TRON_ORANGE,
	GUI_STYLE_MATRIX,
	GUI_STYLE_CYBERPUNK,
	GUI_STYLE_NEON_GRID,
	GUI_STYLE_COUNT
}						t_gui_style;

typedef struct s_gui_theme
{
	int					background;
	int					border;
	int					text_primary;
	int					text_secondary;
	int					accent;
	int					highlight;
}						t_gui_theme;

/* ========== GUI CONSTANTS ========== */
# define GUI_PANEL_WIDTH 280
# define GUI_PADDING 15
# define GUI_LINE_HEIGHT 18
# define GUI_TITLE_HEIGHT 25

// Colors
# define GUI_BG_COLOR 0x1A1A1A
# define GUI_BORDER_COLOR 0x404040
# define GUI_TEXT_COLOR 0xE0E0E0
# define GUI_TITLE_COLOR 0x00D4FF
# define GUI_VALUE_COLOR 0x00FF88
# define GUI_KEY_COLOR 0xFFAA00

/* ========== GUI FUNCTIONS ========== */
int						init_gui(t_data *data);
void					render_gui(t_data *data);
void					draw_panel_background(t_data *data);
void					put_text(t_data *data, t_vec2 v, char *text);
void					put_key(t_data *data, t_vec2 v, char *text);
void					put_colored(t_data *d, t_vec2 v, char *text, int color);
void					put_value(t_data *data, t_vec2 v, char *text);
void					format_speed(double speed, char *buffer);
void					format_number(int num, char *buffer);
void					format_float(double val, char *buffer);
void					cycle_gui_style(t_data *data);
t_gui_theme				get_gui_theme(t_gui_style style);
int						get_gui_background_color(t_gui_style style);
int						get_gui_accent_color(t_gui_style style);
int						get_gui_border_color(t_gui_style style);
int						get_gui_text_color(t_gui_style style);
t_gui_theme				get_tron_blue_theme(void);
t_gui_theme				get_tron_orange_theme(void);
t_gui_theme				get_matrix_theme(void);
t_gui_theme				get_cyberpunk_theme(void);
t_gui_theme				get_neon_grid_theme(void);
void					draw_mouse_controls(t_data *data, int *y);
void					draw_keyboard_controls(t_data *data, int *y);
void					draw_action_keys(t_data *data, int *y);
void					draw_optimization_keys(t_data *data, int *y);
void					draw_controls_guide_at(t_data *data, int *y);
void					draw_speed_display_at(t_data *data, int *y);
void					draw_projection_display_at(t_data *data, int *y);
void					draw_map_name_display_at(t_data *data, int *y);
void					draw_performance_display_at(t_data *data, int *y);
void					draw_performance_header(t_data *data, int *y);
void					draw_performance_counts(t_data *data, int *y);
void					draw_performance_lod(t_data *data, int *y);
void					draw_performance_z_scale(t_data *data, int *y);
void					draw_performance_z_divisor(t_data *data, int *y);
void					draw_performance_invert_move(t_data *data, int *y);
void					draw_performance_depth_cull(t_data *data, int *y);
void					draw_performance_frustum(t_data *data, int *y);
void					draw_performance_depth(t_data *data, int *y);
void					draw_performance_algorithm(t_data *data, int *y);
void					draw_performance_spline_segments(t_data *data, int *y);
void					draw_performance_triangles(t_data *data, int *y);
void					draw_dampening_display(t_data *data);
void					draw_style_display(t_data *data);

#endif
