/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_editor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 18:12:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_EDITOR_H
# define T_EDITOR_H

# include "t_physics.h"

struct			s_gui;
struct			s_widget;

typedef enum e_popup
{
	POPUP_NONE,
	POPUP_SHAPE,
	POPUP_MESH_FMT,
	POPUP_MESH_PATH
}	t_popup;

typedef enum e_mesh_fmt
{
	MESH_FMT_OBJ,
	MESH_FMT_GLB
}	t_mesh_fmt;

typedef struct s_crud_ui
{
	t_popup		popup;
	t_mesh_fmt	mesh_fmt;
	char		path_buf[1024];
	size_t		path_len;
	bool		path_error;
	bool		shift_held;
}	t_crud_ui;

/* --- Editor Color Constants --- */
# define COL_SELECTED 0x20D870
# define COL_PANEL_HDR 0x1A1A28
# define COL_ROW_HOVER 0x1E2030
# define COL_ROW_SEL 0x2A3040
# define COL_SLIDER_BG 0x1A1A20
# define COL_SLIDER_FG 0xE0A820

/* --- Inspector Combo-Row Layout --- */
# define INSP_LBL_W	80
# define INSP_SL_OFF	84
# define INSP_SL_W	106
# define INSP_IN_OFF	194
# define INSP_IN_W	62
# define INSP_ROW_H	18
# define INSP_ROW_STEP	24
# define INSP_HDR_STEP	20

/* --- Editor Layout Constants --- */
# define INSPECTOR_W 280
# define SCENE_PANEL_W 220
# define ROW_H 24
# define CRUD_PANEL_H 120
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
	t_index			index;
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
	size_t			width;
	int				scroll;
	t_index			hovered_row;
}					t_scene_panel;

typedef struct s_islider
{
	const char		*label;
	double			min;
	double			max;
	double			*ptr;
	void			(*on_change)(struct s_gui *);
}					t_islider;

typedef struct s_insp_edit
{
	bool			active;
	double			*value_ptr;
	char			buf[32];
	size_t			i;
	double			dmin;
	double			dmax;
	void			(*on_change)(struct s_gui *gui);
}					t_insp_edit;

typedef struct s_slider_state
{
	bool			dragging;
	t_vec2i			drag_start;
	double			drag_start_val;
	double			*value_ptr;
	double			dmin;
	double			dmax;
	int				track_x;
	int				track_w;
	void			(*on_change)(struct s_gui *gui);
	struct s_widget	*target;
	t_insp_edit		insp_edit;
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
	size_t			mat_id;
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
	size_t			sphere_count;
	t_plane			*planes;
	size_t			plane_count;
	t_cylinder		*cylinders;
	size_t			cylinder_count;
	t_cone			*cones;
	size_t			cone_count;
	t_light			*lights;
	size_t			light_count;
	t_material		*materials;
	size_t			mat_count;
	t_mesh_snap		*meshes;
	size_t			mesh_count;
	size_t			mesh_group_count;
	t_group_snap	*groups;
	size_t			group_count;
	t_box			*boxes;
	size_t			box_count;
	t_capsule		*capsules;
	size_t			capsule_count;
	t_rect			*rects;
	size_t			rect_count;
	t_pyramid		*pyramids;
	size_t			pyramid_count;
	t_tri_shape		*tris;
	size_t			tri_count;
	t_ambient		ambient;
	t_camera		camera;
	int				ambient_color;
	double			ambient_intensity;
}					t_scene_snap;

#endif