/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 09:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "gui.h"
# include "rt.h"

/* ── Selection ───────────────────────────────────────────────────────────── */
typedef struct s_selection
{
	t_type		type;
	int			index;
	bool		active;
	t_aabb		bbox;
}	t_selection;

/* ── Inspector ───────────────────────────────────────────────────────────── */
typedef enum e_inspect_tab
{
	TAB_TRANSFORM,
	TAB_MATERIAL,
	TAB_OBJECT,
	TAB_LIGHT,
	TAB_PHYSICS,
	TAB_INFO,
}	t_inspect_tab;

typedef struct s_inspector
{
	bool			visible;
	t_inspect_tab	tab;
	int				x;
	int				width;
}	t_inspector;

/* ── Scene panel ─────────────────────────────────────────────────────────── */
typedef struct s_scene_panel
{
	bool		visible;
	int			width;
	int			scroll;
	int			hovered_row;
}	t_scene_panel;

/* ── Button rect ─────────────────────────────────────────────────────────── */
typedef struct s_btn_rect
{
	int			x;
	int			y;
	int			w;
	int			h;
}	t_btn_rect;

/* ── Inline slider ───────────────────────────────────────────────────────── */
typedef struct s_islider
{
	const char	*label;
	double		min;
	double		max;
	double		*ptr;
}	t_islider;

typedef struct s_slider_arg
{
	t_vec2i		pos;
	t_islider	sl;
	void		(*on_change)(t_gui *gui);
}	t_slider_arg;

/* ── Label helpers ───────────────────────────────────────────────────────── */
typedef struct s_vec3_label_arg
{
	int			x;
	int			y;
	const char	*label;
	t_vec3		v;
}	t_vec3_label_arg;

typedef struct s_bool_label_arg
{
	int			x;
	int			y;
	const char	*label;
	bool		val;
}	t_bool_label_arg;

/* ── Slider drag state ───────────────────────────────────────────────────── */
typedef struct s_slider_state
{
	bool		dragging;
	int			drag_start_x;
	double		drag_start_val;
	double		*value_ptr;
	double		dmin;
	double		dmax;
	int			track_x;
	int			track_w;
	void		(*on_change)(t_gui *gui);
	t_widget	*target;
}	t_slider_state;

/* ── Undo snapshots ──────────────────────────────────────────────────────── */
typedef struct s_mesh_snap
{
	t_transform		transform;
	int				mat_id;
	t_physics_body	phys;
	int				current_anim;
	double			anim_time;
}	t_mesh_snap;

typedef struct s_group_snap
{
	t_transform		transform;
	t_vec3			pivot;
	t_physics_body	phys;
}	t_group_snap;

typedef struct s_scene_snap
{
	t_primitive_array	prims;
	t_tri_array			tris;
	t_light				*lights;
	size_t				light_count;
	t_material			*materials;
	size_t				mat_count;
	t_ambient			ambient;
	t_camera			camera;
}	t_scene_snap;

/* ── CRUD UI ─────────────────────────────────────────────────────────────── */
typedef struct s_crud_ui
{
	t_popup_step	popup;
	t_mesh_fmt		mesh_fmt;
	char			path_buf[512];
	int				path_len;
	bool			path_error;
	bool			shift_held;
	t_vec2i			pos;
	int				w;
	int				h;
}	t_crud_ui;

/* ── Hover cache ─────────────────────────────────────────────────────────── */
typedef struct s_hover_cache
{
	int			x;
	int			y;
	bool		active;
	bool		hit;
	long		last_frame;
}	t_hover_cache;

/* ── Selection ───────────────────────────────────────────────────────────── */
void	select_object(t_gui *gui, t_type type, int index);
void	clear_selection(t_gui *gui);
t_material	*get_selected_material(t_gui *gui);
void	pick_at_mouse(t_gui *gui, t_vec2i mouse);
void	rebuild_bvh(t_gui *gui);

/* ── Scene panel ─────────────────────────────────────────────────────────── */
void	editor_init(t_gui *gui);
void	draw_scene_panel_bg(t_gui *gui);
void	draw_scene_panel_text(t_gui *gui);
bool	scene_panel_handle_click(t_gui *gui, t_vec2i mouse);
bool	scene_panel_handle_scroll(t_gui *gui, int button);

/* ── Inspector ───────────────────────────────────────────────────────────── */
const char	*type_name_str(t_type type);
void	draw_inspector_bg(t_gui *gui);
void	draw_inspector_text(t_gui *gui);
bool	inspector_handle_click(t_gui *gui, t_vec2i mouse);

/* ── Transform panel ─────────────────────────────────────────────────────── */
t_transform	*get_selected_transform(t_gui *gui);
void	draw_transform_panel(t_gui *gui, int x);
bool	transform_panel_handle_click(t_gui *gui, t_vec2i mouse);
void	mesh_transform_sync(t_gui *gui);
void	sphere_scale_sync(t_gui *gui);
void	box_scale_sync(t_gui *gui);
void	capsule_dims_sync(t_gui *gui);
void	build_tr_sliders(t_transform *tr, t_type type,
		t_islider *sl, int *count);

/* ── Material panel ──────────────────────────────────────────────────────── */
void	draw_material_panel_text(t_gui *gui, int x);
bool	material_panel_handle_click(t_gui *gui, t_vec2i mouse);
void	build_mat_sliders(t_material *mat, t_islider *sl, int *count);

/* ── Slider row ──────────────────────────────────────────────────────────── */
void	draw_slider_row(t_gui *gui, t_slider_arg arg);
bool	try_islider_click(t_gui *gui, t_vec2i mouse, t_slider_arg arg);

/* ── CRUD ────────────────────────────────────────────────────────────────── */
void	editor_add_sphere(t_gui *gui);
void	editor_add_plane(t_gui *gui);
void	editor_add_cylinder(t_gui *gui);
void	editor_add_cone(t_gui *gui);
void	editor_add_light(t_gui *gui);
void	editor_add_tri(t_gui *gui);
void	editor_add_rect(t_gui *gui);
void	editor_add_pyramid(t_gui *gui);
void	editor_add_box(t_gui *gui);
void	editor_add_capsule(t_gui *gui);
void	editor_add_obj(t_gui *gui, const char *path);
void	editor_add_glb(t_gui *gui, const char *path);
void	editor_delete_selected(t_gui *gui);

bool	handle_delete_light(t_scene *sc, t_selection *sel, int i);
void	delete_sel_prims(t_scene *sc, t_selection *sel);
void	delete_sel_solids(t_scene *sc, t_selection *sel);
void	delete_sel_extras(t_scene *sc, t_selection *sel);

t_transform	make_obj_transform(t_vec3 pos, t_vec3 fwd, t_vec3 scl);
t_vec3		cam_fwd_pos(t_gui *gui, double dist);

/* ── CRUD UI ─────────────────────────────────────────────────────────────── */
void	draw_crud_buttons(t_gui *gui);
bool	crud_handle_click(t_gui *gui, t_vec2i mouse);

/* ── Popup ───────────────────────────────────────────────────────────────── */
void	draw_popup(t_gui *gui);
bool	popup_handle_click(t_gui *gui, t_vec2i mouse);
bool	popup_handle_key(t_gui *gui, int keycode);
void	update_popup_rect(t_gui *gui);
void	popup_load_mesh(t_gui *gui);

bool	phit(t_vec2i m, t_vec2i pos, t_vec2i size);
void	draw_modal_bg(t_gui *gui);
void	draw_popup_btn(t_gui *gui, t_vec2i pos, t_vec2i size,
		const char *lbl, int bg);
void	draw_popup_shape(t_gui *gui);
bool	click_popup_shape(t_gui *gui, t_vec2i mouse);
void	draw_popup_mesh_fmt(t_gui *gui);
bool	click_popup_mesh_fmt(t_gui *gui, t_vec2i mouse);
void	draw_popup_mesh_path(t_gui *gui);
bool	click_popup_mesh_path(t_gui *gui, t_vec2i mouse);
char	popup_shift_char(int keycode);

/* ── Physics panel ───────────────────────────────────────────────────────── */
void	draw_physics_panel(t_gui *gui, t_physics_body *phys, int x);
bool	physics_panel_handle_click(t_gui *gui, t_vec2i mouse,
		t_physics_body *phys);
void	build_phys_sliders(t_physics_body *phys, t_islider out[3]);

/* ── Light panel ─────────────────────────────────────────────────────────── */
void	draw_light_panel(t_gui *gui, int x);
bool	light_panel_handle_click(t_gui *gui, t_vec2i mouse);
void	draw_ambient_panel(t_gui *gui, int x);
bool	ambient_panel_handle_click(t_gui *gui, t_vec2i mouse);
void	build_light_sliders(t_light *lt, t_islider *sl, int *count);

/* ── Mesh info panel ─────────────────────────────────────────────────────── */
void			draw_mesh_info_panel(t_gui *gui, int x);
t_physics_body	*get_selected_physics(t_gui *gui);
int				get_tabs(t_type type, t_inspect_tab tabs[4],
					const char *labels[4]);

/* ── Scene snapshot ──────────────────────────────────────────────────────── */
void	scene_snapshot(t_scene_snap *snap, t_gui *gui);
void	scene_snap_free(t_scene_snap *snap);
void	scene_reset(t_gui *gui);

/* ── Label drawing helpers ───────────────────────────────────────────────── */
void	draw_vec3_label(t_gui *gui, const t_vec3_label_arg *a);
void	draw_bool_label(t_gui *gui, const t_bool_label_arg *a);

#endif
