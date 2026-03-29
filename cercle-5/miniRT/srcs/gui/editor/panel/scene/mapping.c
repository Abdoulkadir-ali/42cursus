/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 13:57:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
int	count_scene_rows(t_scene *sc)
{
	return (sc->light_count + sc->primitives.count);
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
	*idx = 0;
	if (row_strip(&r, sc->light_count, TYPE_LIGHT, ty, idx))
		return ;
	if (r >= 0 && r < (int)sc->primitives.count)
	{
		*ty = sc->primitives.types[r];
		*idx = r;
	}
}

const char	*row_type_prefix(t_type type)
{
	const char *lbl[] = {"???", "Light", "Sphere", "Plane", "Cylinder", "Cone",
		"Triangle", "Rect", "Pyramid", "Box", "Capsule", "Mesh"};
	t_type			ty_map[] = { TYPE_NONE, TYPE_LIGHT, TYPE_SPHERE, TYPE_PLANE,
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
	return ("???");
}

/**
 * @brief Draws a single hierarchy row with its appropriate color and label.
 */
void	draw_one_row(t_gui *gui, int y_px, t_type ty, int idx)
{
	char	buf[64];
	int		col;

	col = COL_TEXT_DIM;
	if (gui->selection->active && gui->selection->type == ty
		&& gui->selection->index == idx)
		col = COL_ACCENT;
	snprintf(buf, sizeof(buf), "%s #%d", row_type_prefix(ty), idx);
	gui_draw_string(gui, buf, SCENE_PANEL_PAD_X, y_px, col);
}
