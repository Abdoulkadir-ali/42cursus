/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 11:02:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "widget.h"
# include <X11/keysym.h>
# include "objects.h"
# include "raytracing.h"
# include "color.h"

/* --- Internal scene-panel types --- */
typedef struct s_scene_row_res
{
	t_type	type;
	size_t	index;
}	t_scene_row_res;

/* 2. MODULE TYPES */

void				scene_snap_take(t_scene_snap *snap, struct s_gui *gui);
void				scene_snap_free(t_scene_snap *snap);
void				scene_reset(struct s_gui *gui);

/* types/gui/editor.h */
struct s_tab_draw
{
	t_inspect_tab	*tabs;
	const char		**labels;
	int				step;
};

/* snap_utils.c */
void				snap_array(void **dst, void *src, size_t count, size_t sz);
void				snap_meshes(t_scene_snap *snap, t_scene *sc);
void				snap_groups(t_scene_snap *snap, t_scene *sc);
void				snap_primitives(t_scene_snap *snap, t_scene *sc);
void				snap_extra(t_scene_snap *snap, t_scene *sc);

/* reset_utils.c */
void				reset_meshes(t_scene *sc, t_scene_snap *snap);
void				reset_groups(t_scene *sc, t_scene_snap *snap);
void				reset_primitives(t_scene *sc, t_scene_snap *snap);
void				reset_extra(t_scene *sc, t_scene_snap *snap);

/* srcs/gui/editor/panel/transform/sync.c */
void				transform_selection_sync(t_gui *gui);
void				transform_panel_sync(t_gui *gui);

/* srcs/gui/editor/panel/transform/sliders.c */
void				build_tr_sliders(t_gui *gui, int type, t_vec2i *pos);

/* srcs/gui/editor/panel/transform/mesh.c */
void				mesh_transform_sync(t_gui *gui);
void				mesh_transform_commit(t_gui *gui);

/* srcs/gui/editor/panel/transform/sphere.c */
void				sphere_scale_sync(t_gui *gui);

/* srcs/gui/editor/panel/transform/transform.c */
void				transform_panel(t_gui *gui);
void				draw_transform_panel(struct s_gui *gui, t_vec2i pos);
bool				transform_panel_handle_click(struct s_gui *gui,
						t_vec2i mouse);

/* 3. FUNCTION PROTOTYPES */

/* srcs/gui/editor/selection.c */
void				select_object(struct s_gui *gui, t_type type, size_t index);
void				clear_selection(struct s_gui *gui);
t_material			*get_selected_material(struct s_gui *gui);
void				pick_at_mouse(struct s_gui *gui, t_vec2i mouse);
void				rebuild_bvh(struct s_gui *gui);


/* srcs/gui/editor/scene_panel.c */
void				editor_init(struct s_gui *gui);
void				gui_recompute_layout(struct s_gui *gui);
void				draw_scene_panel_bg(struct s_gui *gui);
void				draw_scene_panel_text(struct s_gui *gui);
bool				scene_panel_handle_click(struct s_gui *gui, t_vec2i mouse);
bool				scene_panel_handle_scroll(struct s_gui *gui, int button);

/* srcs/gui/editor/core/inspector.c */
const char			*type_name_str(t_type type);
void				draw_inspector_bg(struct s_gui *gui);
void				draw_inspector_text(struct s_gui *gui);
bool				inspector_handle_click(struct s_gui *gui, t_vec2i mouse);

/* srcs/gui/editor/panel/material.c */
void				draw_material_panel_text(struct s_gui *gui, t_vec2i pos);
bool				material_panel_handle_click(struct s_gui *gui,
						t_vec2i mouse);
void				build_mat_sliders(t_material *mat, t_islider *sl,
						int *count);
void				sync_group_materials(struct s_gui *gui);

/* srcs/gui/editor/widgets/slider.c + slider_draw.c */
void				draw_slider_row(struct s_gui *gui, t_vec2i pos,
						t_islider sl);
bool				try_islider_click(struct s_gui *gui, t_vec2i mouse,
						t_vec2i pos, t_islider sl);
void				update_inline_drag(struct s_gui *gui, t_vec2i mouse);
void				end_inline_drag(struct s_gui *gui);
void				fill_rect_row(struct s_gui *gui, t_vec2i pos, int w,
						unsigned int col);
void				fill_rect(struct s_gui *gui, t_vec2i pos, t_vec2i size,
						unsigned int col);
void				draw_slider_fill(struct s_gui *gui, t_vec2i pos,
						int fill_w, int total_w);

/* srcs/gui/editor/widgets/insp_row.c */
void				draw_insp_header(struct s_gui *gui, t_vec2i pos,
						const char *title);
void				draw_insp_color_swatch(struct s_gui *gui, t_vec2i pos,
						t_vec3 rgb);
void				draw_insp_row(struct s_gui *gui, t_vec2i pos, t_islider sl);
void				draw_insp_toggle_row(struct s_gui *gui, t_vec2i pos,
						const char *label, bool val);
void				draw_panel_insp_rows(struct s_gui *gui, t_islider *sl,
						int count, t_vec2i pos);

/* srcs/gui/editor/widgets/insp_input.c */
bool				insp_row_click(struct s_gui *gui, t_vec2i mouse,
						t_vec2i pos, t_islider sl);
bool				insp_toggle_click(struct s_gui *gui, t_vec2i mouse,
						t_vec2i pos);
void				insp_input_key(struct s_gui *gui, int keycode);
void				insp_input_commit(struct s_gui *gui);
bool				insp_input_nav(t_insp_edit *e, int keycode);
void				set_insp_drag(struct s_gui *gui, t_islider sl, t_vec3i p);
void				set_insp_edit(struct s_gui *gui, t_islider sl);

/* srcs/gui/editor/crud/add/ */
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
t_vec3				cam_fwd_pos(struct s_gui *gui, double dist);

/* srcs/gui/editor/crud/delete/ */
void				editor_delete_selected(struct s_gui *gui);
void				delete_sel_sp_pl(t_scene *sc, t_selection *sel);
void				delete_sel_cy_co(t_scene *sc, t_selection *sel);
void				delete_sel_rect_tri(t_scene *sc, t_selection *sel);
void				delete_sel_py_bx(t_scene *sc, t_selection *sel);

/* srcs/gui/editor/crud/ui.c */
void				draw_crud_buttons(struct s_gui *gui);
bool				crud_handle_click(struct s_gui *gui, t_vec2i mouse);
void				draw_crud_btn(struct s_gui *gui, t_panel btn);
bool				crud_handle_click(struct s_gui *gui, t_vec2i mouse);
void				draw_crud_btn(struct s_gui *gui, t_panel btn);

/* srcs/gui/editor/crud/popup/utils.c */
void				draw_modal_bg(struct s_gui *gui, size_t h, t_vec2i *p);
void				draw_popup_btn(struct s_gui *gui, t_panel p);

/* srcs/gui/editor/crud/popup/draw.c */
void				draw_popup(struct s_gui *gui);
void				draw_popup_shape(struct s_gui *gui);
void				draw_popup_mesh_fmt(struct s_gui *gui);
void				draw_popup_mesh_path(struct s_gui *gui);
void				draw_path_field(struct s_gui *gui, t_vec2i o,
					size_t modal_h);

/* srcs/gui/editor/crud/popup.c */

/* srcs/gui/editor/panel/physics/physics.c */
void				draw_physics_panel(struct s_gui *gui, t_physics_body *phys,
						t_vec2i pos);
bool				physics_panel_handle_click(struct s_gui *gui, t_vec2i mouse,
						t_physics_body *phys);

/* srcs/gui/editor/panel/light/light.c */
void				draw_light_panel(struct s_gui *gui, t_vec2i pos);
bool				light_panel_handle_click(struct s_gui *gui, t_vec2i mouse);
void				draw_ambient_panel(struct s_gui *gui, t_vec2i pos);
bool				ambient_panel_handle_click(struct s_gui *gui,
						t_vec2i mouse);

/* srcs/gui/editor/panel/info/ */
void				draw_mesh_info_panel(struct s_gui *gui, t_vec2i pos);
bool				info_panel_handle_click(struct s_gui *gui, t_vec2i mouse);

/* srcs/gui/editor/panel/scene/utils.c */
size_t				mesh_row_to_idx(size_t r);
size_t				count_scene_rows(t_scene *sc);
int					row_strip(size_t *r, size_t count, t_type t,
						t_scene_row_res *res);
void				row_to_object(struct s_gui *gui, size_t r, t_type *ty,
						size_t *idx);
/* srcs/gui/editor/panel/scene/header.c */
void				draw_scene_header(struct s_gui *gui);

/* srcs/gui/editor/panel/scene/row.c */
void				draw_scene_rows(t_gui *gui);

/* srcs/gui/editor/panel/light/utils.c */
void				build_light_sliders(t_light *lt, t_islider *sl, int *count);
void				get_ambient_sliders(t_scene *scene, t_islider sl[4]);
void				draw_panel_sliders(struct s_gui *gui, t_islider *sl,
						int count, t_vec2i pos);

/* srcs/gui/editor/panel/mesh_info/utils.c */
void				draw_info_row(struct s_gui *gui, t_vec2i pos,
						const char *label, const char *val);

/* srcs/gui/editor/panel/physics/utils.c */
void				draw_vec3_label(struct s_gui *gui, t_vec2i pos,
						const char *label, t_vec3 v);
void				draw_bool_label(struct s_gui *gui, t_vec2i pos,
						const char *label, bool val);
void				get_phys_sliders(t_physics_body *phys, t_islider sl[3]);

/* srcs/gui/editor/crud/popup/click/ */
bool				click_popup_mesh_fmt(struct s_gui *gui, t_vec2i mouse);
bool				popup_handle_click(struct s_gui *gui, t_vec2i mouse);
bool				popup_handle_key(struct s_gui *gui, int keycode);

/* srcs/gui/editor/core/inspector/tabs.c */
int					get_tabs(t_type type, t_inspect_tab tabs[4],
						const char *labels[4]);
void				draw_inspector_tabs(struct s_gui *gui, t_vec2i pos);

/* srcs/gui/editor/core/inspector/utils.c */
t_physics_body		*get_selected_physics(struct s_gui *gui);

#endif
