/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/07 23:11:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "raytracing.h"

void	rebuild_bvh(t_gui *gui)
{
	if (gui->scene->bvh)
		bvh_destroy(gui->scene->bvh);
	gui->scene->bvh = bvh_create(gui->scene);
}

void	select_object(t_gui *gui, t_type type, int index)
{
	t_bvh_ref	ref;

	ref.type = (uint8_t)type;
	ref.index = index;
	gui->selection.type = type;
	gui->selection.index = index;
	gui->selection.active = true;
	gui->selection.bbox = aabb_from_ref(gui->scene, ref);
	gui->inspector.visible = true;
	if (type == TYPE_MESH)
		gui->inspector.tab = TAB_INFO;
	else if (type == TYPE_LIGHT)
		gui->inspector.tab = TAB_LIGHT;
	else
		gui->inspector.tab = TAB_TRANSFORM;
	ft_print_debug("[editor] selected %d idx=%d\n", (int)type, index);
}

void	clear_selection(t_gui *gui)
{
	gui->selection.active = false;
	gui->selection.index = -1;
	gui->selection.type = TYPE_NONE;
	gui->inspector.visible = false;
}

static int	mat_id_of_selection(t_gui *gui)
{
	t_selection	*sel;
	t_scene		*sc;

	sel = &gui->selection;
	sc = gui->scene;
	if (sel->type == TYPE_SPHERE)
		return (sc->spheres[sel->index].mat_id);
	if (sel->type == TYPE_PLANE)
		return (sc->planes[sel->index].mat_id);
	if (sel->type == TYPE_CYLINDER)
		return (sc->cylinders[sel->index].mat_id);
	if (sel->type == TYPE_CONE)
		return (sc->cones[sel->index].mat_id);
	if (sel->type == TYPE_MESH)
		return (sc->meshes[sel->index].mat_id);
	return (-1);
}

t_material	*get_selected_material(t_gui *gui)
{
	t_selection	*sel;
	int			mat_id;

	sel = &gui->selection;
	if (!sel->active || !gui->scene)
		return (NULL);
	mat_id = mat_id_of_selection(gui);
	if (mat_id < 0 || mat_id >= gui->scene->mat_count)
		return (NULL);
	return (&gui->scene->materials[mat_id]);
}

static void	compute_pick_ray(t_gui *gui, t_vec2i mouse, t_ray *ray)
{
	double	scale;
	double	aspect;
	double	rx;
	double	ry;
	t_vec2	p;
	t_vec3	dir;

	rx = (double)mouse.x * gui->win.width / gui->win.disp_w;
	ry = (double)mouse.y * gui->win.height / gui->win.disp_h;
	scale = tan(gui->cam_ctrl.camera->fov * M_PI / 360.0);
	aspect = (double)gui->win.width / (double)gui->win.height;
	p.x = (2.0 * (rx + 0.5) / gui->win.width - 1.0) * scale * aspect;
	p.y = (1.0 - 2.0 * (ry + 0.5) / gui->win.height) * scale;
	dir = vec3_add(gui->cam_ctrl.transform.forward,
			vec3_add(vec3_scale(gui->cam_ctrl.transform.right, p.x),
				vec3_scale(gui->cam_ctrl.transform.up, p.y)));
	dir = vec3_norm(dir);
	ray_init(ray, gui->cam_ctrl.transform.pos, dir);
}

void	pick_at_mouse(t_gui *gui, t_vec2i mouse)
{
	t_ray	ray;
	t_hit	hit;

	if (!gui->scene || !gui->scene->bvh || !gui->cam_ctrl.camera)
		return ;
	compute_pick_ray(gui, mouse, &ray);
	ft_memset(&hit, 0, sizeof(t_hit));
	if (bvh_intersect(gui->scene->bvh, &ray, &hit))
		select_object(gui, (t_type)hit.ref.type, hit.ref.index);
	else
		clear_selection(gui);
	gui->render.dirty = true;
}
