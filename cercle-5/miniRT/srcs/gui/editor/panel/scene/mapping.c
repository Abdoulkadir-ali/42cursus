/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 05:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "gui.h"

int	count_scene_rows(t_scene *sc)
{
	return (sc->light_count + sc->sphere_count + sc->plane_count
		+ sc->cylinder_count + sc->cone_count + sc->tri_count + sc->rect_count
		+ sc->pyramid_count + sc->box_count + sc->capsule_count
		+ sc->group_count);
}

static int	row_strip(int *r, int count, t_type t, t_type *ty, int *idx)
{
	if (*r < count)
	{
		*ty = t;
		*idx = *r;
		return (1);
	}
	*r -= count;
	return (0);
}

/**
 * @brief Resolves a hierarchy row index to a scene object reference.
 */
void	row_to_object(t_gui *gui, int r, t_type *ty, int *idx)
{
	t_scene	*sc;

	sc = gui->scene;
	*ty = TYPE_NONE;
	if (row_strip(&r, sc->light_count, TYPE_LIGHT, ty, idx)
		|| row_strip(&r, sc->sphere_count, TYPE_SPHERE, ty, idx)
		|| row_strip(&r, sc->plane_count, TYPE_PLANE, ty, idx)
		|| row_strip(&r, sc->cylinder_count, TYPE_CYLINDER, ty, idx)
		|| row_strip(&r, sc->cone_count, TYPE_CONE, ty, idx)
		|| row_strip(&r, sc->tri_count, TYPE_TRI, ty, idx)
		|| row_strip(&r, sc->rect_count, TYPE_RECT, ty, idx)
		|| row_strip(&r, sc->pyramid_count, TYPE_PYRAMID, ty, idx)
		|| row_strip(&r, sc->box_count, TYPE_BOX, ty, idx)
		|| row_strip(&r, sc->capsule_count, TYPE_CAPSULE, ty, idx))
		return ;
	if (r < sc->group_count)
	{
		*ty = TYPE_MESH;
		*idx = r;
	}
}

const char	*row_type_prefix(t_type type)
{
	const char *lbl[] = { "[??]", "[LT]", "[SP]", "[PL]", "[CY]", "[CO]",
		"[TR]", "[RC]", "[PY]", "[BX]", "[CA]", "[ME]"};
	int			ty_map[] = { TYPE_NONE, TYPE_LIGHT, TYPE_SPHERE, TYPE_PLANE,
		TYPE_CYLINDER, TYPE_CONE, TYPE_TRI, TYPE_RECT, TYPE_PYRAMID,
		TYPE_BOX, TYPE_CAPSULE, TYPE_MESH};
	int			i;

	i = 0;
	while (i < 12)
	{
		if (type == ty_map[i])
			return (lbl[i]);
		i++;
	}
	return ("[??]");
}

/**
 * @brief Draws a single hierarchy row with its appropriate color and label.
 */
void	draw_one_row(t_gui *gui, int y_px, t_type ty, int idx)
{
	char	buf[64];
	int		col;

	col = COL_TEXT;
	if (gui->selection.active && gui->selection.type == ty
		&& gui->selection.index == idx)
		col = COL_SELECTED;
	if (ty == TYPE_MESH && idx >= 0 && idx < gui->scene->group_count
		&& gui->scene->groups[idx].name)
		snprintf(buf, sizeof(buf), "[ME] %.55s", gui->scene->groups[idx].name);
	else
		snprintf(buf, sizeof(buf), "%s %d", row_type_prefix(ty), idx);
	mlx_string_put(gui->win.mlx, gui->win.win, SCENE_PANEL_PAD_X, y_px, col, buf);
}
