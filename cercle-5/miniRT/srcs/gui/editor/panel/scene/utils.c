/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 12:56:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int	count_mesh_entries(t_scene *sc)
{
	return (sc->group_count);
}

int	mesh_row_to_idx(t_scene *sc, int r)
{
	(void)sc;
	return (r);
}

int	count_scene_rows(t_scene *sc)
{
	return (sc->light_count + sc->sphere_count + sc->plane_count
		+ sc->cylinder_count + sc->cone_count + sc->tri_count
		+ sc->rect_count + sc->pyramid_count
		+ sc->box_count + sc->capsule_count
		+ count_mesh_entries(sc));
}

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

void	row_to_object(t_gui *gui, int r, t_type *ty, int *idx)
{
	t_scene				*sc;
	t_scene_row_res		res;

	sc = gui->scene;
	*ty = TYPE_NONE;
	*idx = -1;
	res.type = TYPE_NONE;
	res.index = -1;
	if (row_strip(&r, sc->light_count, TYPE_LIGHT, &res)
		|| row_strip(&r, sc->sphere_count, TYPE_SPHERE, &res)
		|| row_strip(&r, sc->plane_count, TYPE_PLANE, &res)
		|| row_strip(&r, sc->cylinder_count, TYPE_CYLINDER, &res)
		|| row_strip(&r, sc->cone_count, TYPE_CONE, &res)
		|| row_strip(&r, sc->tri_count, TYPE_TRI, &res)
		|| row_strip(&r, sc->rect_count, TYPE_RECT, &res)
		|| row_strip(&r, sc->pyramid_count, TYPE_PYRAMID, &res)
		|| row_strip(&r, sc->box_count, TYPE_BOX, &res)
		|| row_strip(&r, sc->capsule_count, TYPE_CAPSULE, &res))
	{
		*ty = res.type;
		*idx = res.index;
		return ;
	}
	if (r < count_mesh_entries(sc))
	{
		*ty = TYPE_MESH;
		*idx = mesh_row_to_idx(sc, r);
	}
}
