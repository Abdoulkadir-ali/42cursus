/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_panel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/07 23:49:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "editor.h"

t_transform	*get_selected_transform(t_gui *gui)
{
	t_selection	*sel;
	t_scene		*sc;

	sel = &gui->selection;
	sc = gui->scene;
	if (!sel->active || !sc)
		return (NULL);
	if (sel->type == TYPE_SPHERE)
		return (&sc->spheres[sel->index].transform);
	if (sel->type == TYPE_PLANE)
		return (&sc->planes[sel->index].transform);
	if (sel->type == TYPE_CYLINDER)
		return (&sc->cylinders[sel->index].transform);
	if (sel->type == TYPE_CONE)
		return (&sc->cones[sel->index].transform);
	if (sel->type == TYPE_MESH)
		return (&sc->meshes[sel->index].transform);
	return (NULL);
}

static void	build_tr_sliders(t_transform *tr, t_islider *sl, int *count)
{
	int	i;

	i = 0;
	sl[i++] = (t_islider){"Pos X", SL_POS_MIN, SL_POS_MAX, &tr->pos.x};
	sl[i++] = (t_islider){"Pos Y", SL_POS_MIN, SL_POS_MAX, &tr->pos.y};
	sl[i++] = (t_islider){"Pos Z", SL_POS_MIN, SL_POS_MAX, &tr->pos.z};
	sl[i++] = (t_islider){"Pitch", SL_ROT_MIN, SL_ROT_MAX, &tr->rotation.pitch};
	sl[i++] = (t_islider){"Yaw", SL_ROT_MIN, SL_ROT_MAX, &tr->rotation.yaw};
	sl[i++] = (t_islider){"Roll", SL_ROT_MIN, SL_ROT_MAX, &tr->rotation.roll};
	sl[i++] = (t_islider){"Scale X", SL_SCALE_MIN, SL_SCALE_MAX, &tr->scale.x};
	sl[i++] = (t_islider){"Scale Y", SL_SCALE_MIN, SL_SCALE_MAX, &tr->scale.y};
	sl[i++] = (t_islider){"Scale Z", SL_SCALE_MIN, SL_SCALE_MAX, &tr->scale.z};
	*count = i;
}

void	draw_transform_panel(t_gui *gui, int x)
{
	t_transform	*tr;
	t_islider	sl[9];
	int			count;
	int			i;
	int			y;

	tr = get_selected_transform(gui);
	if (!tr)
	{
		mlx_string_put(gui->win.mlx, gui->win.win,
			x + 8, 90, COL_TEXT, "No transform");
		return ;
	}
	mlx_string_put(gui->win.mlx, gui->win.win,
		x + 8, 88, COL_HOVER, "TRANSFORM");
	build_tr_sliders(tr, sl, &count);
	y = 104;
	i = 0;
	while (i < count)
	{
		draw_slider_row(gui, vec2i(x + 8, y), sl[i]);
		y += 30;
		i++;
	}
}

bool	transform_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_transform	*tr;
	t_islider	sl[9];
	int			count;
	int			i;
	int			y;
	int			x;

	tr = get_selected_transform(gui);
	if (!tr)
		return (false);
	x = gui->win.disp_w - gui->inspector.width;
	build_tr_sliders(tr, sl, &count);
	y = 104;
	i = 0;
	while (i < count)
	{
		if (try_islider_click(gui, mouse, vec2i(x + 8, y), sl[i]))
			return (true);
		y += 30;
		i++;
	}
	return (false);
}
