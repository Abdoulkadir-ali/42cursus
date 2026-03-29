/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 13:38:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "unpacker.h"
#include "debug.h"

/**
 * @brief Unified DOD object selection.
 */
void	select_object(t_gui *gui, t_type type, int index)
{
	gui->selection->type = type;
	gui->selection->index = index;
	gui->selection->active = true;
	if (type == TYPE_MESH)
		ft_memset(&gui->selection->bbox, 0, sizeof(t_aabb));
	else if (type == TYPE_LIGHT)
	{
		t_vec3 pos = gui->scene->lights[index].transform.pos;
		gui->selection->bbox.min = vec3_sub(pos, vec3(0.5, 0.5, 0.5));
		gui->selection->bbox.max = vec3_add(pos, vec3(0.5, 0.5, 0.5));
	}
	else if (type == TYPE_TRI)
		gui->selection->bbox = get_tri_aabb_soa(&gui->scene->tri_soa, index);
	else
		gui->selection->bbox = get_primitive_aabb_soa(&gui->scene->primitives,
				index);
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

static int	mat_id_of_selection(t_gui *gui)
{
	t_selection	*sel;

	sel = gui->selection;
	if (!gui->scene || sel->index < 0)
		return (-1);
	if (sel->type == TYPE_MESH)
		return (-1); /* To be implemented when mesh groups are restored */
	if ((size_t)sel->index < gui->scene->primitives.count)
		return (gui->scene->primitives.mat_ids[sel->index]);
	return (-1);
}

t_material	*get_selected_material(t_gui *gui)
{
	int			mat_id;

	if (!gui->selection->active || !gui->scene)
		return (NULL);
	mat_id = mat_id_of_selection(gui);
	if (mat_id < 0 || (size_t)mat_id >= gui->scene->mat_count)
		return (NULL);
	return (&gui->scene->materials[mat_id]);
}

void	pick_at_mouse(t_gui *gui, t_vec2i mouse)
{
	t_ray		ray;
	t_hit		hit;
	t_render	*ctx;

	if (!gui->scene || !gui->rt.bvh || !gui->cam_ctrl.camera)
		return ;
	DBG_TRACE_MSG(DBG_CH_EDITOR,
		"pick_at_mouse: (%d,%d) bvh=%p\n",
		mouse.x, mouse.y, (void *)gui->rt.bvh);
	ctx = gui->pool.ctx[0];
	if (!ctx)
		return ;
	make_camera_ray(ctx, (double)mouse.x, (double)mouse.y, &ray);
	ft_memset(&hit, 0, sizeof(t_hit));
	if (bvh_intersect(gui->rt.bvh, &ray, &hit))
	{
		DBG_INFO_MSG(DBG_CH_EDITOR,
			"pick_at_mouse: hit type=%d idx=%d\n",
			(int)hit.ref.type, hit.ref.index);
		select_object(gui, (t_type)hit.ref.type, hit.ref.index);
	}
	else
	{
		DBG_TRACE_MSG(DBG_CH_EDITOR, "pick_at_mouse: no hit\n");
		clear_selection(gui);
	}
	gui->render.dirty = true;
}

t_physics_body	*get_selected_physics(t_gui *gui)
{
	(void)gui;
	// TODO: Implement properly
	return (NULL);
}
