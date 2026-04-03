/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:33:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int	row_strip(int *r, int count, t_type t, t_scene_row_res *res)
{
	if (*r < count)
	{
		res->type = t;
		res->index = *r;
		return (1);
	}
	*r -= count;
	return (0);
}

static bool	strip_primary_objects(t_scene *sc, int *r, t_scene_row_res *res)
{
	if (row_strip(r, sc->light_count, TYPE_LIGHT, res)
		|| row_strip(r, sc->sphere_count, TYPE_SPHERE, res)
		|| row_strip(r, sc->plane_count, TYPE_PLANE, res)
		|| row_strip(r, sc->cylinder_count, TYPE_CYLINDER, res)
		|| row_strip(r, sc->cone_count, TYPE_CONE, res)
		|| row_strip(r, sc->tri_count, TYPE_TRI, res)
		|| row_strip(r, sc->rect_count, TYPE_RECT, res)
		|| row_strip(r, sc->pyramid_count, TYPE_PYRAMID, res)
		|| row_strip(r, sc->box_count, TYPE_BOX, res)
		|| row_strip(r, sc->capsule_count, TYPE_CAPSULE, res))
		return (true);
	return (false);
}

void	row_to_object(t_gui *gui, size_t r, t_type *ty, int *idx)
{
	t_scene_row_res		res;
	int					row_i;

	*ty = TYPE_NONE;
	*idx = -1;
	res.type = TYPE_NONE;
	res.index = -1;
	row_i = (int)r;
	if (strip_primary_objects(gui->scene, &row_i, &res))
	{
		*ty = res.type;
		*idx = res.index;
		return ;
	}
	if ((size_t)row_i < count_mesh_entries(gui->scene))
	{
		*ty = TYPE_MESH;
		*idx = row_i;
	}
}
