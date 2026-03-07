/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/07 20:51:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "core.h"
# include "maths.h"
# include "surface.h"

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
	TAB_OBJECT
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

typedef struct s_slider_state
{
	bool			dragging;
	int				drag_start_x;
	double			drag_start_val;
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

#endif
