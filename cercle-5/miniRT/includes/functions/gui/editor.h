/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/31 09:49:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "physics.h"
# include "helpers.h"
# include "types.h"

/* --- Editor Color Constants --- */
# define COL_SELECTED 0x20D870
# define COL_PANEL_HDR 0x1A1A28
# define COL_ROW_HOVER 0x1E2030
# define COL_ROW_SEL 0x2A3040
# define COL_SLIDER_BG 0x1A1A20
# define COL_SLIDER_FG 0xE0A820

/* --- Editor Layout Constants --- */
# define INSPECTOR_W 280
# define SCENE_PANEL_W 220
# define ROW_H 24
# define CRUD_PANEL_H 36
# define CRUD_BTN_H 24
# define CRUD_BTN_W 52
# define CRUD_ADD_W 90
# define POPUP_W 360
# define POPUP_ITEM_H 36
# define POPUP_PAD 16

/* --- Slider Range Constants --- */
/* Transform */
# define SL_POS_MIN -500.0
# define SL_POS_MAX 500.0
# define SL_ROT_MIN -180.0
# define SL_ROT_MAX 180.0
# define SL_SCALE_MIN 0.0
# define SL_SCALE_MAX 100.0
/* Material */
# define SL_ROUGH_MIN 0.0
# define SL_ROUGH_MAX 1.0
# define SL_METAL_MIN 0.0
# define SL_METAL_MAX 1.0
# define SL_OPAC_MIN 0.0
# define SL_OPAC_MAX 1.0
# define SL_REFL_MIN 0.0
# define SL_REFL_MAX 1.0
# define SL_IOR_MIN 0.0
# define SL_IOR_MAX 180.0
# define SL_COL_MIN 0.0
# define SL_COL_MAX 255.0
# define SL_EMIT_MIN 0.0
# define SL_EMIT_MAX 255.0
/* Light */
# define SL_INTENSITY_MIN 0.0
# define SL_INTENSITY_MAX 5.0
# define SL_CUTOFF_MIN 0.0
# define SL_CUTOFF_MAX 90.0
/* Ambient */
# define SL_AMB_MIN 0.0
# define SL_AMB_MAX 2.0
/* Physics */
# define SL_MASS_MIN 0.01
# define SL_MASS_MAX 1000.0
# define SL_ELAST_MIN 0.0
# define SL_ELAST_MAX 1.0
# define SL_FRIC_MIN 0.0
# define SL_FRIC_MAX 1.0

/* 2. MODULE TYPES */

typedef struct s_selection
{
	t_type			type;
	int				index;
	bool			active;
	t_aabb			bbox;
}					t_selection;

typedef enum e_inspect_tab
{
	TAB_TRANSFORM,
	TAB_MATERIAL,
	TAB_OBJECT,
	TAB_LIGHT,
	TAB_PHYSICS,
	TAB_INFO
}					t_inspect_tab;

typedef struct s_inspector
{
	bool			visible;
	t_inspect_tab	tab;
	t_vec2i			pos;
	int				width;
}					t_inspector;

typedef struct s_scene_panel
{
	bool			visible;
	int				width;
	int				scroll;
	int				hovered_row;
}					t_scene_panel;

typedef struct s_islider
{
	const char		*label;
	double			min;
	double			max;
	double			*ptr;
}					t_islider;

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
}					t_slider_state;

/* srcs/gui/editor/scene_reset.c */

typedef struct s_mesh_sync
{
	t_mat4	sr;
	t_mat4	r;
	t_vec3	piv;
	t_vec3	pos;
}					t_mesh_sync;

typedef struct s_mesh_snap
{
	t_transform		transform;
	int				mat_id;
	t_physics_body	phys;
}					t_mesh_snap;

typedef struct s_group_snap
{
	t_transform		transform;
	t_vec3			pivot;
	t_physics_body	phys;
}					t_group_snap;

typedef struct s_scene_snap
{
	t_sphere		*spheres;
	int				sphere_count;
	t_plane			*planes;
	int				plane_count;
	t_cylinder		*cylinders;
	int				cylinder_count;
	t_cone			*cones;
	int				cone_count;
	t_light			*lights;
	int				light_count;
	t_material		*materials;
	int				mat_count;
	t_mesh_snap		*meshes;
	int				mesh_count;
	int				mesh_group_count;
	t_group_snap	*groups;
	int				group_count;
	t_box			*boxes;
	int				box_count;
	t_capsule		*capsules;
	int				capsule_count;
	t_rect			*rects;
	int				rect_count;
	t_pyramid		*pyramids;
	int				pyramid_count;
	t_tri_shape		*tris;
	int				tri_count;
	t_ambient		ambient;
	t_camera		camera;
	int				ambient_color;
	double			ambient_intensity;
}					t_scene_snap;

void				scene_snap_take(t_scene_snap *snap, struct s_gui *gui);
void				scene_snap_free(t_scene_snap *snap);
void				scene_reset(struct s_gui *gui);

/* srcs/gui/editor/panel/transform/sync.c */
void				transform_selection_sync(t_gui *gui);
void				transform_panel_sync(t_gui *gui);

/* srcs/gui/editor/panel/transform/sliders.c */
void				build_tr_sliders(t_gui *gui, int type, int *y);

/* srcs/gui/editor/panel/transform/mesh.c */
void				mesh_transform_sync(t_gui *gui);

/* srcs/gui/editor/panel/transform/sphere.c */
void				sphere_scale_sync(t_gui *gui);

/* srcs/gui/editor/panel/transform/transform.c */
void				transform_panel(t_gui *gui);

/* 3. FUNCTION PROTOTYPES */

/* srcs/gui/editor/selection.c */
void				select_object(struct s_gui *gui, t_type type, int index);
void				clear_selection(struct s_gui *gui);
t_material			*get_selected_material(struct s_gui *gui);
void				pick_at_mouse(struct s_gui *gui, t_vec2i mouse);
void				rebuild_bvh(struct s_gui *gui);

/* srcs/gui/editor/scene_panel.c */
void				editor_init(struct s_gui *gui);
void				draw_scene_panel_bg(struct s_gui *gui);
void				draw_scene_panel_text(struct s_gui *gui);
bool				scene_panel_handle_click(struct s_gui *gui, t_vec2i mouse);
bool				scene_panel_handle_scroll(struct s_gui *gui, int button);

/* srcs/gui/editor/inspector.c */
const char			*type_name_str(t_type type);
void				draw_inspector_bg(struct s_gui *gui);
void				draw_inspector_text(struct s_gui *gui);
bool				inspector_handle_click(struct s_gui *gui, t_vec2i mouse);

/* srcs/gui/editor/transform_panel.c */
t_transform			*get_selected_transform(struct s_gui *gui);
void				draw_transform_panel(struct s_gui *gui, int x);

/* srcs/gui/editor/material_panel.c */
void				draw_material_panel_text(struct s_gui *gui, int x);
bool				material_panel_handle_click(struct s_gui *gui,
						t_vec2i mouse);

/* srcs/gui/editor/transform_panel.c */
bool				transform_panel_handle_click(struct s_gui *gui,
						t_vec2i mouse);

/* srcs/gui/editor/slider_inline.c */
void				draw_slider_row(struct s_gui *gui, t_vec2i pos,
						t_islider sl);
bool				try_islider_click(struct s_gui *gui, t_vec2i mouse,
						t_vec2i pos, t_islider sl,
						void (*on_change)(struct s_gui *gui));
void				update_inline_drag(struct s_gui *gui, int mouse_x);
void				end_inline_drag(struct s_gui *gui);

/* srcs/gui/editor/crud.c */
void				editor_add_sphere(struct s_gui *gui);
void				editor_add_plane(struct s_gui *gui);
void				editor_add_cylinder(struct s_gui *gui);
void				editor_add_cone(struct s_gui *gui);
void				editor_add_light(struct s_gui *gui);
void				editor_add_tri(struct s_gui *gui);
void				editor_add_rect(struct s_gui *gui);
void				editor_add_pyramid(struct s_gui *gui);
void				editor_add_box(struct s_gui *gui);
void				editor_add_capsule(struct s_gui *gui);
void				editor_add_obj(struct s_gui *gui, const char *path);
void				editor_add_glb(struct s_gui *gui, const char *path);
void				editor_delete_selected(struct s_gui *gui);
void				delete_sel_sp_pl(t_scene *sc, t_selection *sel);
void				delete_sel_cy_co(t_scene *sc, t_selection *sel);
t_vec3				cam_fwd_pos(struct s_gui *gui, double dist);

/* srcs/gui/editor/crud_ui.c */
void				draw_crud_buttons(struct s_gui *gui);
bool				crud_handle_click(struct s_gui *gui, t_vec2i mouse);

/* srcs/gui/editor/popup.c */
void				draw_popup(struct s_gui *gui);
bool				popup_handle_click(struct s_gui *gui, t_vec2i mouse);
bool				popup_handle_key(struct s_gui *gui, int keycode);
void				popup_load_mesh(struct s_gui *gui);

/* srcs/gui/editor/physics_panel.c */
void				draw_physics_panel(struct s_gui *gui, t_physics_body *phys,
						int x);
bool				physics_panel_handle_click(struct s_gui *gui, t_vec2i mouse,
						t_physics_body *phys);

/* srcs/gui/editor/light_panel.c */
void				draw_light_panel(struct s_gui *gui, int x);
bool				light_panel_handle_click(struct s_gui *gui, t_vec2i mouse);
void				draw_ambient_panel(struct s_gui *gui, int x);
bool				ambient_panel_handle_click(struct s_gui *gui,
						t_vec2i mouse);

/* srcs/gui/editor/mesh_info_panel.c */
void				draw_mesh_info_panel(struct s_gui *gui, int x);

#endif
