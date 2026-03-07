/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/07 23:11:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "core.h"
# include "maths.h"
# include "surface.h"
# include "physics.h"

/* --- Editor Color Constants --- */
# define COL_SELECTED   0x20D870
# define COL_PANEL_HDR  0x1A1A28
# define COL_ROW_HOVER  0x1E2030
# define COL_ROW_SEL    0x2A3040
# define COL_SLIDER_BG  0x1A1A20
# define COL_SLIDER_FG  0xE0A820

/* --- Editor Layout Constants --- */
# define INSPECTOR_W    280
# define SCENE_PANEL_W  220
# define ROW_H          24
# define CRUD_PANEL_H   98
# define CRUD_BTN_H     22
# define CRUD_BTN_W     52

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

typedef struct s_islider
{
	const char	*label;
	double		min;
	double		max;
	double		*ptr;
}	t_islider;

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
	struct s_widget	*target;
}	t_slider_state;

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

/* srcs/gui/editor/transform_panel.c */
bool		transform_panel_handle_click(struct s_gui *gui, t_vec2i mouse);

/* srcs/gui/editor/slider_inline.c */
void		draw_slider_row(struct s_gui *gui, t_vec2i pos, t_islider sl);
bool		try_islider_click(struct s_gui *gui, t_vec2i mouse,
			t_vec2i pos, t_islider sl);
void		update_inline_drag(struct s_gui *gui, int mouse_x);
void		end_inline_drag(struct s_gui *gui);

/* srcs/gui/editor/crud.c */
void		editor_add_sphere(struct s_gui *gui);
void		editor_add_plane(struct s_gui *gui);
void		editor_add_cylinder(struct s_gui *gui);
void		editor_add_cone(struct s_gui *gui);
void		editor_add_light(struct s_gui *gui);
void		editor_delete_selected(struct s_gui *gui);

/* srcs/gui/editor/crud_ui.c */
void		draw_crud_buttons(struct s_gui *gui);
bool		crud_handle_click(struct s_gui *gui, t_vec2i mouse);

/* srcs/gui/editor/physics_panel.c */
void		draw_physics_panel(struct s_gui *gui, t_physics_body *phys, int x);
bool		physics_panel_handle_click(struct s_gui *gui, t_vec2i mouse,
			t_physics_body *phys);

/* srcs/gui/editor/light_panel.c */
void		draw_light_panel(struct s_gui *gui, int x);
bool		light_panel_handle_click(struct s_gui *gui, t_vec2i mouse);
void		draw_ambient_panel(struct s_gui *gui, int x);
bool		ambient_panel_handle_click(struct s_gui *gui, t_vec2i mouse);

/* srcs/gui/editor/mesh_info_panel.c */
void		draw_mesh_info_panel(struct s_gui *gui, int x);

#endif
