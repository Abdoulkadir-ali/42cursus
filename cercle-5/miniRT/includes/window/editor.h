/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:02:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

/* PROJECT DEPENCIES */
# include "gui.h"
# include "old_structs.h"

struct				s_selection
{
	t_type			type;
	int				index;
	bool			active;
	t_aabb			bbox;
};

typedef enum e_inspect_tab
{
	TAB_TRANSFORM,
	TAB_MATERIAL,
	TAB_OBJECT,
	TAB_LIGHT,
	TAB_PHYSICS,
	TAB_INFO
}					t_inspect_tab;

struct				s_inspector
{
	bool			visible;
	t_inspect_tab	tab;
	int				x;
	int				width;
};

struct				s_scene_panel
{
	bool			visible;
	int				width;
	int				scroll;
	int				hovered_row;
};

struct				s_btn_rect
{
	int				x;
	int				y;
	int				w;
	int				h;
};

struct				s_islider
{
	const char		*label;
	double			min;
	double			max;
	double			*ptr;
};

struct				s_slider_arg
{
	t_vec2i			pos;
	t_islider		sl;
	void			(*on_change)(struct s_gui *gui);
};

struct				s_vec3_label_arg
{
	int				x;
	int				y;
	const char		*label;
	t_vec3			v;
};

struct				s_bool_label_arg
{
	int				x;
	int				y;
	const char		*label;
	bool			val;
};

struct				s_slider_state
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
};

struct				s_mesh_snap
{
	t_transform		transform;
	int				mat_id;
	t_physics_body	phys;
	int				current_anim;
	double			anim_time;
};

struct				s_group_snap
{
	t_transform		transform;
	t_vec3			pivot;
	t_physics_body	phys;
};

struct				s_scene_snap
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
};

struct				s_crud_ui
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
};

struct				s_hover_cache
{
	int				x;
	int				y;
	bool			active;
	bool			hit;
	long			last_frame;
};

/* --- Function Prototypes --- */

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

/* material panel helpers */
void				build_mat_sliders(t_material *mat, t_islider *sl,
						int *count);

/* srcs/gui/editor/transform_panel.c */
bool				transform_panel_handle_click(struct s_gui *gui,
						t_vec2i mouse);

/* transform panel helpers and callbacks */
void				mesh_transform_sync(struct s_gui *gui);
void				sphere_scale_sync(struct s_gui *gui);
void				box_scale_sync(struct s_gui *gui);
void				capsule_dims_sync(struct s_gui *gui);
void				build_tr_sliders(t_transform *tr, t_type type,
						t_islider *sl, int *count);

/* srcs/gui/editor/slider_inline.c */
void				draw_slider_row(struct s_gui *gui, t_slider_arg arg);
bool				try_islider_click(struct s_gui *gui, t_vec2i mouse,
						t_slider_arg arg);

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

/* delete helpers (crud/delete/) */
bool				handle_delete_light(t_scene *sc, t_selection *sel, int i);
void				delete_sel_prims(t_scene *sc, t_selection *sel);
void				delete_sel_solids(t_scene *sc, t_selection *sel);
void				delete_sel_extras(t_scene *sc, t_selection *sel);

/* crud helpers */
t_transform			make_obj_transform(t_vec3 pos, t_vec3 fwd, t_vec3 scl);
t_vec3				cam_fwd_pos(struct s_gui *gui, double dist);

/* srcs/gui/editor/crud_ui.c */
void				draw_crud_buttons(struct s_gui *gui);
bool				crud_handle_click(struct s_gui *gui, t_vec2i mouse);

/* srcs/gui/editor/popup.c */
void				draw_popup(struct s_gui *gui);
bool				popup_handle_click(struct s_gui *gui, t_vec2i mouse);
bool				popup_handle_key(struct s_gui *gui, int keycode);
void				update_popup_rect(struct s_gui *gui);
void				popup_load_mesh(struct s_gui *gui);

/* Internal Popup Helpers */
bool				phit(t_vec2i m, t_vec2i pos, t_vec2i size);
void				draw_modal_bg(struct s_gui *gui);
void				draw_popup_btn(struct s_gui *gui, t_vec2i pos, t_vec2i size,
						const char *lbl, int bg);
void				draw_popup_shape(struct s_gui *gui);
bool				click_popup_shape(struct s_gui *gui, t_vec2i mouse);
void				draw_popup_mesh_fmt(struct s_gui *gui);
bool				click_popup_mesh_fmt(struct s_gui *gui, t_vec2i mouse);
void				draw_popup_mesh_path(struct s_gui *gui);
bool				click_popup_mesh_path(struct s_gui *gui, t_vec2i mouse);
char				popup_shift_char(int keycode);
void				draw_physics_panel(struct s_gui *gui, t_physics_body *phys,
						int x);
bool				physics_panel_handle_click(struct s_gui *gui, t_vec2i mouse,
						t_physics_body *phys);

/* physics panel helpers */
void				build_phys_sliders(t_physics_body *phys, t_islider out[3]);

/* srcs/gui/editor/light_panel.c */
void				draw_light_panel(struct s_gui *gui, int x);
bool				light_panel_handle_click(struct s_gui *gui, t_vec2i mouse);
void				draw_ambient_panel(struct s_gui *gui, int x);
bool				ambient_panel_handle_click(struct s_gui *gui,
						t_vec2i mouse);

/* shared helpers for light panel */
void				build_light_sliders(t_light *lt, t_islider *sl, int *count);

/* srcs/gui/editor/mesh_info_panel.c */
void				draw_mesh_info_panel(struct s_gui *gui, int x);
t_physics_body		*get_selected_physics(t_gui *gui);
int					get_tabs(t_type type, t_inspect_tab tabs[4],
						const char *labels[4]);

void				scene_snapshot(t_scene_snap *snap, struct s_gui *gui);
void				scene_snap_free(t_scene_snap *snap);
void				scene_reset(struct s_gui *gui);
void				draw_vec3_label(struct s_gui *gui,
						const t_vec3_label_arg *a);
void				draw_bool_label(struct s_gui *gui,
						const t_bool_label_arg *a);

#endif
