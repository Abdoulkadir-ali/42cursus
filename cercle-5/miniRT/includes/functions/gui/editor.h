/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 17:46:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "widget.h"
# include "objects.h"
# include "raytracing.h"

/* --- Internal scene-panel types --- */
typedef struct s_scene_row_res
{
	t_type	type;
	int		index;
}	t_scene_row_res;

/* 2. MODULE TYPES */

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

/* srcs/gui/editor/panel/scene/utils.c */
int					count_mesh_entries(t_scene *sc);
int					mesh_row_to_idx(t_scene *sc, int r);
int					count_scene_rows(t_scene *sc);
int					row_strip(int *r, int count, t_type t, t_scene_row_res *res);
void				row_to_object(t_gui *gui, int r, t_type *ty, int *idx);

/* srcs/gui/editor/panel/scene/row.c */
void				draw_scene_rows(t_gui *gui);

/* srcs/gui/editor/panel/transform/sliders.c */
void				build_tr_sliders(struct s_gui *gui, int type, int *y);

/* srcs/gui/editor/panel/light/utils.c */
void				build_light_sliders(t_light *lt, t_islider *sl, int *count);
void				get_ambient_sliders(t_scene *scene, t_islider sl[4]);
void				draw_panel_sliders(struct s_gui *gui, t_islider *sl, int count, t_vec2i pos);

/* srcs/gui/editor/panel/mesh_info/utils.c */
void				draw_info_row(struct s_gui *gui, t_vec2 pos, const char *label, const char *val);

/* srcs/gui/editor/panel/physics/utils.c */
void				draw_vec3_label(struct s_gui *gui, t_vec2i pos, const char *label, t_vec3 v);
void				draw_bool_label(struct s_gui *gui, t_vec2i pos, const char *label, bool val);
void				get_phys_sliders(t_physics_body *phys, t_islider sl[3]);

#endif
