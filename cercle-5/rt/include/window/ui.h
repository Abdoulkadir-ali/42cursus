/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/02 17:11:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include "maths.h"
# include "widget.h"

# define UI_PAD 10
# define UI_LINE_H 18
# define UI_PANEL_W 280
# define UI_SIDEBAR_W 300

typedef struct s_widget
{
	int		slider_active_id;
	int		initialized;
	int		*drag_x;
	int		*drag_y;
	int		anchor_mx;
	float	start_v;
}			t_widget;

typedef struct s_ui_theme
{
	unsigned int	bg;
	unsigned int	bg2;
	unsigned int	header;
	unsigned int	border;
	unsigned int	text;
	unsigned int	text_dim;
	unsigned int	btn;
	unsigned int	btn_hov;
	unsigned int	btn_act;
	unsigned int	accent;
}					t_ui_theme;

typedef struct s_ui_state
{
	int			next_id;
	int			hot_id;
	int			active_id;
	int			mx;
	int			my;
	int			mouse_left;
	int			mouse_left_prev;
	int			consume_input;
	int			drag_active;
	int			panel_x;
	int			panel_y;
	int			panel_w;
	int			cursor_x;
	int			cursor_y;
	int			active_item;
	int			hot_item;
	int			kb_focus;
	char		input_buf[32];
	t_ui_theme	theme;
	t_widget	widget;
	int			show_settings;
	int			show_animation;
	int			settings_tab;
	int			tab_clicked;
	int			obj_tab;
	int			scroll_y;
	int			scissor_y0;
	int			scissor_y1;
}				t_ui_state;

typedef struct s_panel_layout
{
	int	settings_x;
	int	settings_y;
	int	settings_h;
	int	inspector_x;
	int	inspector_y;
	int	inspector_h;
	int	scene_x;
	int	scene_y;
	int	scene_h;
	int	physics_x;
	int	physics_y;
	int	physics_h;
	int	animation_x;
	int	animation_y;
	int	animation_h;
	int	xfm_x;
	int	xfm_y;
	int	xfm_h;
	int	obj_phys_x;
	int	obj_phys_y;
	int	obj_phys_h;
	int	obj_mat_x;
	int	obj_mat_y;
	int	obj_mat_h;
	int	scene_scroll;
	int	obj_scroll;
	int	theme_preset;
}		t_panel_layout;

static inline int	pt_in(t_vec2i p, t_vec2i pos, t_vec2i size)
{
	return (p.x >= pos.x && p.x < pos.x + size.x
		&& p.y >= pos.y && p.y < pos.y + size.y);
}

extern t_panel_layout	g_layout;

struct s_app;

void	layout_load(void);
void	layout_save(void);

/* Core UI */
void	ui_begin(struct s_app *app);
int		ui_handle_key(struct s_app *app, int key);
void	ui_end(struct s_app *app);
void	ui_draw_all(struct s_app *app);

/* Layout */
void	ui_panel_begin(struct s_app *app, int x, int y, int h, int w,
			const char *title);
void	ui_panel_begin_p(struct s_app *app, int *x, int *y, int *h,
			int w, const char *title);
void	ui_panel_end(struct s_app *app, int *h);
void	ui_scroll_begin(struct s_app *app, int h, int *scroll_y);
void	ui_scroll_end(struct s_app *app, int *scroll_y);

/* Widgets */
void	ui_label(struct s_app *app, const char *s);
void	ui_section(struct s_app *app, const char *s);
void	ui_label_value(struct s_app *app, const char *k, const char *v);
int		ui_button(struct s_app *app, const char *label);
int		ui_button_at(struct s_app *app, t_vec2i pos, t_vec2i size,
			const char *label);
int		ui_tab(struct s_app *app, const char *label, int selected, int bw);
int		ui_checkbox(struct s_app *app, const char *label, int *v);
static inline int	ui_checkbox_b(struct s_app *app, const char *label, bool *v)
{
	int	tmp;
	int	ret;

	tmp = (int)*v;
	ret = ui_checkbox(app, label, &tmp);
	*v = (bool)tmp;
	return (ret);
}
int		ui_slider_f(struct s_app *app, const char *label, float *v,
			float lo, float hi);
int		ui_slider_i(struct s_app *app, const char *label, int *v,
			int lo, int hi);
int		ui_log_f(struct s_app *app, const char *label, float *v,
			float lo, float hi);
float	ui_drag_f(struct s_app *app, const char *label, float sens);
int		ui_color_swatch(struct s_app *app, const char *label, t_vec3 *v);
int		ui_color_swatch_hex(struct s_app *app, const char *label,
			unsigned int *col);
void	ui_set_theme(struct s_app *app, int preset);
int		ui_num_input(struct s_app *app, const char *label, float *v,
			unsigned int label_col, int bw);
int		ui_vec3_edit(struct s_app *app, const char *label, t_vec3 *v);
int		ui_select_row(struct s_app *app, const char *label, int selected);

/* Drawing primitives */
void	gfx_pixel_blend(struct s_app *app, int x, int y, unsigned int rgba);
void	gfx_fill_rect(struct s_app *app, int x, int y, int w, int h,
			unsigned int c);
void	gfx_rect_outline(struct s_app *app, int x, int y, int w, int h,
			unsigned int c);
void	gfx_text(struct s_app *app, int x, int y, const char *s,
			unsigned int c);
int		gfx_text_width(const char *s);
void	gfx_outline_object(struct s_app *app, int target);

#endif
