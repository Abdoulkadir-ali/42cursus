/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:16:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	find_group_by_mesh(t_scene *sc, size_t mesh_idx)
{
	size_t	gi;

	gi = 0;
	while (gi < sc->group_count)
	{
		if (mesh_idx >= sc->groups[gi].start
			&& mesh_idx < sc->groups[gi].start + sc->groups[gi].sub_count)
			return (gi);
		gi++;
	}
	return (-1);
}

static void	compute_pick_ray(t_gui *gui, t_vec2i mouse, t_ray *ray)
{
	double	sc;
	double	asp;
	t_vec2	p;
	t_vec3	dir;

	p.x = (double)mouse.x * gui->win.size.x / gui->win.disp_size.x;
	p.y = (double)mouse.y * gui->win.size.y / gui->win.disp_size.y;
	sc = tan(gui->cam_ctrl.camera->fov * M_PI / 360.0);
	asp = (double)gui->win.size.x / (double)gui->win.size.y;
	p.x = (2.0 * (p.x + 0.5) / gui->win.size.x - 1.0) * sc * asp;
	p.y = (1.0 - 2.0 * (p.y + 0.5) / gui->win.size.y) * sc;
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
	int		grp;

	if (!gui->scene || !gui->scene->bvh || !gui->cam_ctrl.camera)
		return ;
	compute_pick_ray(gui, mouse, &ray);
	ft_memset(&hit, 0, sizeof(t_hit));
	hit.t = 1e30;
	if (bvh_intersect(gui->scene->bvh, &ray, &hit))
	{
		if ((t_type)hit.ref.type == TYPE_MESH)
		{
			grp = find_group_by_mesh(gui->scene, hit.ref.index);
			if (grp < 0)
				grp = hit.ref.index;
			select_object(gui, TYPE_MESH, grp);
		}
		else
			select_object(gui, (t_type)hit.ref.type, hit.ref.index);
	}
	else
		clear_selection(gui);
	gui->render.dirty = true;
}
