/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/25 16:34:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "core.h"
# include "maths.h"
# include "objects.h"
# include "surface.h"
# include "physics.h"

/* --- Editor Color Constants --- */
# define COL_SELECTED   0x20D870U
# define COL_PANEL_HDR  0x1A1A28U
# define COL_ROW_HOVER  0x1E2030U
# define COL_ROW_SEL    0x2A3040U
# define COL_SLIDER_BG  0x1A1A20U
# define COL_SLIDER_FG  0xE0A820U
# define COL_BORDER     0x2A2A38U
# define COL_TEXT       0xE0E0E0U
# define COL_HOVER      0xF0F0F0U

/* --- Editor Layout Constants --- */
# define INSPECTOR_W    280
# define SCENE_PANEL_W  220
# define ROW_H          24
# define CRUD_PANEL_H   36
# define SLIDER_H       8
# define SLIDER_KNOB_W  3
# define SLIDER_KNOB_H  12
# define SLIDER_PAD     24
# define SLIDER_Y_OFF   13
# define SLIDER_VAL_X   46

# define CRUD_BTN_H     24
# define CRUD_BTN_W     52
# define CRUD_ADD_W     90
# define POPUP_W        360
# define POPUP_ITEM_H   36
# define POPUP_PAD      16
# define POPUP_TITLE_H  36
# define POPUP_FMT_H    36
# define POPUP_INPUT_H  36
# define POPUP_ERR_H    16
# define POPUP_BTN_H    36

# define COL_POPUP_DIM  0x0D0D14U
# define COL_POPUP_BG   0x1A1A28U
# define COL_POPUP_BTN  0x22222EU
# define COL_POPUP_BTN_OK 0x1A2A1AU
# define COL_POPUP_BTN_CANCEL 0x2A1A1AU
# define COL_POPUP_ERR  0xFF4444U
# define COL_POPUP_ERR_TEXT 0xFF6666U


# define SCENE_PANEL_PAD_X 12
# define SCENE_PANEL_PAD_Y 8
# define SCENE_PANEL_HDR_X 8
# define SCENE_PANEL_EMPTY_COL 0x505060

# define INSPECTOR_HDR_Y 50
# define INSPECTOR_TAB_Y 70
# define INSPECTOR_TAB_H 24
# define INSPECTOR_PAD   8
# define INSPECTOR_TAB_MIN_Y 60
# define INSPECTOR_TAB_MAX_Y 84

# define TR_PANEL_START_Y   104
# define TR_PANEL_STEP_Y    30

/* --- Slider Range Constants --- */
/* Transform */
# define SL_POS_MIN     -500.0
# define SL_POS_MAX      500.0
# define SL_ROT_MIN     -180.0
# define SL_ROT_MAX      180.0
# define SL_SCALE_MIN    0.0
# define SL_SCALE_MAX    100.0
/* Material */
# define SL_ROUGH_MIN    0.0
# define SL_ROUGH_MAX    1.0
# define SL_METAL_MIN    0.0
# define SL_METAL_MAX    1.0
# define SL_OPAC_MIN     0.0
# define SL_OPAC_MAX     1.0
# define SL_REFL_MIN     0.0
# define SL_REFL_MAX     1.0
# define SL_IOR_MIN      0.0
# define SL_IOR_MAX      180.0
# define SL_COL_MIN      0.0
# define SL_COL_MAX      255.0
# define SL_EMIT_MIN     0.0
# define SL_EMIT_MAX     255.0
/* Light */
# define SL_INTENSITY_MIN  0.0
# define SL_INTENSITY_MAX  5.0
# define SL_CUTOFF_MIN     0.0
# define SL_CUTOFF_MAX     90.0
/* Ambient */
# define SL_AMB_MIN      0.0
# define SL_AMB_MAX      2.0
/* Physics */
# define SL_MASS_MIN     0.01
# define SL_MASS_MAX     1000.0
# define SL_ELAST_MIN    0.0
# define SL_ELAST_MAX    1.0
# define SL_FRIC_MIN     0.0
# define SL_FRIC_MAX     1.0
# define MAX_INSPECT_TABS 4
/* 2. MODULE TYPES */

typedef struct s_selection
{
	t_type	type;
	int		index;
	bool	active;
	t_aabb	bbox;
}	t_selection;

typedef enum e_inspect_tab
{
	TAB_TRANSFORM,
	TAB_MATERIAL,
	TAB_OBJECT,
	TAB_LIGHT,
	TAB_PHYSICS,
	TAB_INFO
}	t_inspect_tab;

typedef struct s_inspector
{
	bool			visible;
	t_inspect_tab	tab;
	int				x;
	int				width;
}	t_inspector;

typedef struct s_scene_panel
{
	bool	visible;
	int		width;
	int		scroll;
	int		hovered_row;
}	t_scene_panel;

typedef struct s_btn_rect
{
	t_vec2i pos;
	t_vec2i size;
}   t_btn_rect;

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
	void		(*on_change)(struct s_gui *gui);
}	t_slider_arg;


typedef struct s_vec3_label_arg
{
    int			x;
    int			y;
    const char	*label;
    t_vec3		v;
}               t_vec3_label_arg;

typedef struct s_bool_label_arg
{
    int			x;
    int			y;
    const char	*label;
    bool		val;
}               t_bool_label_arg;

typedef struct s_slider_state
{
	bool			dragging;
	int				drag_start_x;
	double			drag_start_val;
	double			*value_ptr;
	double			dmin;
	double			dmax;
	int				track_x;
	int				track_w;
	void			(*on_change)(struct s_gui *gui);
	struct s_widget	*target;
}	t_slider_state;


typedef struct s_mesh_snap
{
	t_transform		transform;
	int				mat_id;
	t_physics_body	phys;
}	t_mesh_snap;

typedef struct s_group_snap
{
	t_transform		transform;
	t_vec3			pivot;
	t_physics_body	phys;
}	t_group_snap;

typedef struct s_scene_snap
{
	t_sphere	*spheres;	int	sphere_count;
	t_plane		*planes;	int	plane_count;
	t_cylinder	*cylinders;	int	cylinder_count;
	t_cone		*cones;		int	cone_count;
	t_light		*lights;	int	light_count;
	t_material	*materials;	int	mat_count;
	t_mesh_snap	*meshes;	int	mesh_count;
	int			mesh_group_count;
	t_group_snap	*groups;	int	group_count;
	t_box		*boxes;		int	box_count;
	t_capsule	*capsules;	int	capsule_count;
	t_rect		*rects;		int	rect_count;
	t_pyramid	*pyramids;	int	pyramid_count;
	t_tri_shape	*tris;		int	tri_count;
	t_ambient	ambient;
	t_camera	camera;
	int			ambient_color;
	double		ambient_intensity;
}	t_scene_snap;


/* 3. FUNCTION PROTOTYPES */

/* srcs/gui/editor/selection.c */
void		select_object(struct s_gui *gui, t_type type, int index);
void		clear_selection(struct s_gui *gui);
t_material	*get_selected_material(struct s_gui *gui);
void		pick_at_mouse(struct s_gui *gui, t_vec2i mouse);
void		rebuild_bvh(struct s_gui *gui);

/* srcs/gui/editor/scene_panel.c */
void		editor_init(struct s_gui *gui);
void		draw_scene_panel_bg(struct s_gui *gui);
void		draw_scene_panel_text(struct s_gui *gui);
bool		scene_panel_handle_click(struct s_gui *gui, t_vec2i mouse);
bool		scene_panel_handle_scroll(struct s_gui *gui, int button);

/* srcs/gui/editor/inspector.c */
const char	*type_name_str(t_type type);
void		draw_inspector_bg(struct s_gui *gui);
void		draw_inspector_text(struct s_gui *gui);
bool		inspector_handle_click(struct s_gui *gui, t_vec2i mouse);

/* srcs/gui/editor/transform_panel.c */
t_transform	*get_selected_transform(struct s_gui *gui);
void		draw_transform_panel(struct s_gui *gui, int x);

/* srcs/gui/editor/material_panel.c */
void		draw_material_panel_text(struct s_gui *gui, int x);
bool		material_panel_handle_click(struct s_gui *gui, t_vec2i mouse);

/* material panel helpers */
void		build_mat_sliders(t_material *mat, t_islider *sl, int *count);

/* srcs/gui/editor/transform_panel.c */
bool		transform_panel_handle_click(struct s_gui *gui, t_vec2i mouse);

/* transform panel helpers and callbacks */
void		mesh_transform_sync(struct s_gui *gui);
void		sphere_scale_sync(struct s_gui *gui);
void		box_scale_sync(struct s_gui *gui);
void		capsule_dims_sync(struct s_gui *gui);
void		build_tr_sliders(t_transform *tr, t_type type,
			t_islider *sl, int *count);

/* srcs/gui/editor/slider_inline.c */
void		draw_slider_row(struct s_gui *gui, t_slider_arg arg);
bool		try_islider_click(struct s_gui *gui, t_vec2i mouse,
				t_slider_arg arg);
void		update_inline_drag(struct s_gui *gui, int mouse_x);
void		end_inline_drag(struct s_gui *gui);

/* srcs/gui/editor/crud.c */
void		editor_add_sphere(struct s_gui *gui);
void		editor_add_plane(struct s_gui *gui);
void		editor_add_cylinder(struct s_gui *gui);
void		editor_add_cone(struct s_gui *gui);
void		editor_add_light(struct s_gui *gui);
void		editor_add_tri(struct s_gui *gui);
void		editor_add_rect(struct s_gui *gui);
void		editor_add_pyramid(struct s_gui *gui);
void		editor_add_box(struct s_gui *gui);
void		editor_add_capsule(struct s_gui *gui);
void		editor_add_obj(struct s_gui *gui, const char *path);
void		editor_add_glb(struct s_gui *gui, const char *path);
void		editor_delete_selected(struct s_gui *gui);

/* delete helpers (crud/delete/) */
bool		handle_delete_light(t_scene *sc, t_selection *sel, int i);
void		delete_sel_prims(t_scene *sc, t_selection *sel);
void		delete_sel_solids(t_scene *sc, t_selection *sel);
void		delete_sel_extras(t_scene *sc, t_selection *sel);

/* crud helpers */
t_transform	make_obj_transform(t_vec3 pos, t_vec3 fwd, t_vec3 scl);
t_vec3		cam_fwd_pos(struct s_gui *gui, double dist);

/* srcs/gui/editor/crud_ui.c */
void		draw_crud_buttons(struct s_gui *gui);
bool		crud_handle_click(struct s_gui *gui, t_vec2i mouse);

/* srcs/gui/editor/popup.c */
void		draw_popup(struct s_gui *gui);
bool		popup_handle_click(struct s_gui *gui, t_vec2i mouse);
bool		popup_handle_key(struct s_gui *gui, int keycode);
void		update_popup_rect(struct s_gui *gui);
void		popup_load_mesh(struct s_gui *gui);

/* Internal Popup Helpers */
bool		phit(t_vec2i m, t_vec2i pos, t_vec2i size);
void		draw_modal_bg(struct s_gui *gui);
void		draw_popup_btn(struct s_gui *gui, t_vec2i pos, t_vec2i size,
				const char *lbl, int bg);
void		draw_popup_shape(struct s_gui *gui);
bool		click_popup_shape(struct s_gui *gui, t_vec2i mouse);
void		draw_popup_mesh_fmt(struct s_gui *gui);
bool		click_popup_mesh_fmt(struct s_gui *gui, t_vec2i mouse);
void		draw_popup_mesh_path(struct s_gui *gui);
bool		click_popup_mesh_path(struct s_gui *gui, t_vec2i mouse);
char		popup_shift_char(int keycode);
void		draw_physics_panel(struct s_gui *gui, t_physics_body *phys, int x);
bool		physics_panel_handle_click(struct s_gui *gui, t_vec2i mouse,
			t_physics_body *phys);

/* physics panel helpers */
void		build_phys_sliders(t_physics_body *phys, t_islider out[3]);

/* srcs/gui/editor/light_panel.c */
void		draw_light_panel(struct s_gui *gui, int x);
bool		light_panel_handle_click(struct s_gui *gui, t_vec2i mouse);
void		draw_ambient_panel(struct s_gui *gui, int x);
bool		ambient_panel_handle_click(struct s_gui *gui, t_vec2i mouse);

/* shared helpers for light panel */
void		build_light_sliders(t_light *lt, t_islider *sl, int *count);

/* srcs/gui/editor/mesh_info_panel.c */
void		draw_mesh_info_panel(struct s_gui *gui, int x);
t_physics_body	*get_selected_physics(t_gui *gui);
int				get_tabs(t_type type, t_inspect_tab tabs[4],
					const char *labels[4]);


void		scene_snapshot(t_scene_snap *snap, struct s_gui *gui);
void		scene_snap_free(t_scene_snap *snap);
void		scene_reset(struct s_gui *gui);

/* Global UI Helpers */
void		fill_rect(struct s_gui *gui, int x, int y, int w, int h,
				unsigned int col);

/* Internal Snapshot Helpers */
void		snap_array(void **dst, void *src, int count, size_t sz);
void		snap_sphere(t_scene_snap *s, t_scene *sc);
void		snap_plane(t_scene_snap *s, t_scene *sc);
void		snap_cylinder(t_scene_snap *s, t_scene *sc);
void		snap_cone(t_scene_snap *s, t_scene *sc);
void		snap_light(t_scene_snap *s, t_scene *sc);
void		snap_box(t_scene_snap *s, t_scene *sc);
void		snap_capsule(t_scene_snap *s, t_scene *sc);
void		snap_rect(t_scene_snap *s, t_scene *sc);
void		snap_pyramid(t_scene_snap *s, t_scene *sc);
void		snap_tri(t_scene_snap *s, t_scene *sc);
void		snap_mesh(t_scene_snap *s, t_scene *sc);
void		snap_material(t_scene_snap *s, t_scene *sc);

/* Internal Reset Helpers */
void		reset_sphere(t_scene *sc, t_scene_snap *s);
void		reset_plane(t_scene *sc, t_scene_snap *s);
void		reset_cylinder(t_scene *sc, t_scene_snap *s);
void		reset_cone(t_scene *sc, t_scene_snap *s);
void		reset_light(t_scene *sc, t_scene_snap *s);
void		reset_box(t_scene *sc, t_scene_snap *s);
void		reset_capsule(t_scene *sc, t_scene_snap *s);
void		reset_rect(t_scene *sc, t_scene_snap *s);
void		reset_pyramid(t_scene *sc, t_scene_snap *s);
void		reset_tri(t_scene *sc, t_scene_snap *s);
void		reset_mesh(t_scene *sc, t_scene_snap *s);
void		reset_material(t_scene *sc, t_scene_snap *s);

/* Internal Inspector Helpers */
t_physics_body	*get_selected_physics(struct s_gui *gui);
int				get_tabs(t_type type, t_inspect_tab tabs[4],
					const char *labels[4]);

/* Internal Scene Panel Helpers */
int				count_scene_rows(t_scene *sc);
void			row_to_object(struct s_gui *gui, int r, t_type *ty, int *idx);
const char		*row_type_prefix(t_type type);
void			draw_one_row(struct s_gui *gui, int y_px, t_type ty, int idx);

#endif
