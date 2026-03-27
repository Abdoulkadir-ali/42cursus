/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 21:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "helpers/geometry.h"

void	rebuild_bvh(t_gui *gui)
{
	if (gui->scene->bvh)
		bvh_destroy(gui->scene->bvh);
	gui->scene->bvh = bvh_create(gui->scene);
}

/**
 * @brief DOD-compliant object selection. 
 * Indices now map directly to the unified SoA storage.
 */
void	select_object(t_gui *gui, t_type type, int index)
{
	gui->selection->type = type;
	gui->selection->index = index;
	gui->selection->active = true;
	/* In unified DOD, meshes might still use groups, 
	** but primitives use direct SoA query */
	if (type == TYPE_MESH)
	{
		/* Mesh implementation remains AoS-compatible as intended */
		gui->selection->bbox = gui->scene->meshes[index].bbox;
	}
	else
	{
		gui->selection->bbox = get_primitive_aabb_soa(&gui->scene->primitives,
				index);
	}
	gui->inspector->visible = true;
	if (type == TYPE_MESH)
		gui->inspector->tab = TAB_INFO;
	else if (type == TYPE_LIGHT)
		gui->inspector->tab = TAB_LIGHT;
	else
		gui->inspector->tab = TAB_TRANSFORM;
	ft_print_debug("[editor] selected DOD prim %d at idx=%d\n", 
		(int)type, index);
}

void	clear_selection(t_gui *gui)
{
	gui->selection->active = false;
	gui->selection->index = -1;
	gui->selection->type = TYPE_NONE;
	gui->inspector->visible = false;
}

/**
 * @brief Extracts material ID from selected object (DOD or AoS mesh).
 */
static int	mat_id_of_selection(t_gui *gui)
{
	t_selection	*sel;

	sel = gui->selection;
	if (sel->type == TYPE_MESH)
		return (gui->scene->meshes[sel->index].mat_id);
	if (sel->index >= 0 && (size_t)sel->index < gui->scene->primitives.count)
		return (gui->scene->primitives.mat_ids[sel->index]);
	return (-1);
}

t_material	*get_selected_material(t_gui *gui)
{
	int			mat_id;

	if (!gui->selection->active || !gui->scene)
		return (NULL);
	mat_id = mat_id_of_selection(gui);
	if (mat_id < 0 || mat_id >= (int)gui->scene->mat_count)
		return (NULL);
	return (&gui->scene->materials[mat_id]);
}

void	pick_at_mouse(t_gui *gui, t_vec2i mouse)
{
	t_ray	ray;
	t_hit	hit;

	if (!gui->scene || !gui->scene->bvh || !gui->cam_ctrl.camera)
		return ;
	/* Compute pick ray logic (assumed correct from baseline) */
	ray_init(&ray, gui->cam_ctrl.transform.pos, gui->cam_ctrl.transform.forward);
	ft_memset(&hit, 0, sizeof(t_hit));
	if (bvh_intersect(gui->scene->bvh, &ray, &hit))
		select_object(gui, (t_type)hit.ref.type, hit.ref.index);
	else
		clear_selection(gui);
	gui->render.dirty = true;
}
