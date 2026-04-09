/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot_mat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static size_t	get_mat_p1(t_selection *sel, t_scene *sc, int slot)
{
	if (sel->type == TYPE_SPHERE && sel->index.i < sc->sphere_count)
		return (sc->spheres[sel->index.i].mat_slots[slot]);
	if (sel->type == TYPE_PLANE && sel->index.i < sc->plane_count)
		return (sc->planes[sel->index.i].mat_slots[slot]);
	if (sel->type == TYPE_CYLINDER && sel->index.i < sc->cylinder_count)
		return (sc->cylinders[sel->index.i].mat_slots[slot]);
	if (sel->type == TYPE_CONE && sel->index.i < sc->cone_count)
		return (sc->cones[sel->index.i].mat_slots[slot]);
	if (sel->type == TYPE_TRI && sel->index.i < sc->tri_count)
		return (sc->tris[sel->index.i].mat_slots[slot]);
	return (0);
}

size_t	slot_get_mat(t_gui *gui, int slot)
{
	t_selection		*s;
	t_scene			*sc;
	size_t			res;

	s = &gui->selection;
	sc = gui->scene;
	if (!s->active || !sc)
		return (0);
	res = get_mat_p1(s, sc, slot);
	if (res)
		return (res);
	if (s->type == TYPE_RECT && s->index.i < sc->rect_count)
		return (sc->rects[s->index.i].mat_slots[slot]);
	if (s->type == TYPE_PYRAMID && s->index.i < sc->pyramid_count)
		return (sc->pyramids[s->index.i].mat_slots[slot]);
	if (s->type == TYPE_BOX && s->index.i < sc->box_count)
		return (sc->boxes[s->index.i].mat_slots[slot]);
	if (s->type == TYPE_CAPSULE && s->index.i < sc->capsule_count)
		return (sc->capsules[s->index.i].mat_slots[slot]);
	if (s->type == TYPE_MESH && s->index.i < sc->group_count)
		return (sc->meshes[sc->groups[s->index.i].start].mat_slots[slot]);
	return (0);
}

static void	set_mat_p1(t_gui *gui, int slot, size_t mat_id)
{
	t_selection	*sel;
	t_scene		*sc;

	sel = &gui->selection;
	sc = gui->scene;
	if (sel->type == TYPE_SPHERE)
		sc->spheres[sel->index.i].mat_slots[slot] = mat_id;
	else if (sel->type == TYPE_PLANE)
		sc->planes[sel->index.i].mat_slots[slot] = mat_id;
	else if (sel->type == TYPE_CYLINDER)
		sc->cylinders[sel->index.i].mat_slots[slot] = mat_id;
	else if (sel->type == TYPE_CONE)
		sc->cones[sel->index.i].mat_slots[slot] = mat_id;
	else if (sel->type == TYPE_TRI)
		sc->tris[sel->index.i].mat_slots[slot] = mat_id;
	else if (sel->type == TYPE_RECT)
		sc->rects[sel->index.i].mat_slots[slot] = mat_id;
}

void	slot_set_mat(t_gui *gui, int slot, size_t mat_id)
{
	t_selection		*s;
	t_scene			*sc;
	t_mesh_group	*g;
	size_t			i;

	s = &gui->selection;
	sc = gui->scene;
	if (!s->active || !sc)
		return ;
	if (s->type == TYPE_MESH && s->index.i < sc->group_count)
	{
		g = &sc->groups[s->index.i];
		i = 0;
		while (i < g->sub_count)
			sc->meshes[g->start + i++].mat_slots[slot] = mat_id;
		return ;
	}
	set_mat_p1(gui, slot, mat_id);
	if (s->type == TYPE_PYRAMID)
		sc->pyramids[s->index.i].mat_slots[slot] = mat_id;
	else if (s->type == TYPE_BOX)
		sc->boxes[s->index.i].mat_slots[slot] = mat_id;
	else if (s->type == TYPE_CAPSULE)
		sc->capsules[s->index.i].mat_slots[slot] = mat_id;
}
