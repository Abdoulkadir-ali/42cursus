/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_panel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/08 01:28:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "editor.h"

static void	mesh_transform_sync(t_gui *gui)
{
	t_mesh	*mesh;
	t_mat4	s;
	t_mat4	r;
	t_mat4	sr;
	t_vec3	local;
	t_vec3	piv;
	int		i;

	if (!gui->selection.active || gui->selection.type != TYPE_MESH)
		return ;
	mesh = &gui->scene->meshes[gui->selection.index];
	if (!mesh->edit_snap_verts)
		return ;
	s = mat4_scaling(mesh->transform.scale);
	r = mat4_rotation(mesh->transform.rotation);
	sr = mat4_mul(r, s);
	piv = mesh->edit_snap_pivot;
	i = 0;
	while (i < mesh->vertex_count)
	{
		local = vec3_sub(mesh->edit_snap_verts[i], piv);
		local = mat4_mul_pos(sr, local);
		mesh->vertices[i] = vec3_add(vec3_add(local, piv), mesh->transform.pos);
		if (mesh->normals && mesh->edit_snap_norms)
			mesh->normals[i] = vec3_norm(mat4_mul_vec3(r,
						mesh->edit_snap_norms[i]));
		i++;
	}
	mesh->bbox = aabb_create_empty();
	i = 0;
	while (i < mesh->vertex_count)
		aabb_expand_point(&mesh->bbox, mesh->vertices[i++]);
	mesh_build_bvh(mesh);
}

static void	sphere_scale_sync(t_gui *gui)
{
	t_selection	*sel;
	t_sphere	*sp;
	t_transform	scale_only;

	sel = &gui->selection;
	if (!sel->active || sel->type != TYPE_SPHERE)
		return ;
	sp = &gui->scene->spheres[sel->index];
	sp->transform.scale.y = sp->transform.scale.x;
	sp->transform.scale.z = sp->transform.scale.x;
	sp->radius_sq = sp->transform.scale.x * sp->transform.scale.x;
	scale_only.pos = sp->transform.pos;
	scale_only.scale = sp->transform.scale;
	scale_only.rotation = (t_rotator){0, 0, 0};
	sp->inv_transform = mat4_inverse_transform(scale_only);
}

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

static void	build_tr_sliders(t_transform *tr, t_type type,
	t_islider *sl, int *count)
{
	int	i;

	i = 0;
	sl[i++] = (t_islider){"Pos X", SL_POS_MIN, SL_POS_MAX, &tr->pos.x};
	sl[i++] = (t_islider){"Pos Y", SL_POS_MIN, SL_POS_MAX, &tr->pos.y};
	sl[i++] = (t_islider){"Pos Z", SL_POS_MIN, SL_POS_MAX, &tr->pos.z};
	sl[i++] = (t_islider){"Pitch", SL_ROT_MIN, SL_ROT_MAX, &tr->rotation.pitch};
	sl[i++] = (t_islider){"Yaw", SL_ROT_MIN, SL_ROT_MAX, &tr->rotation.yaw};
	sl[i++] = (t_islider){"Roll", SL_ROT_MIN, SL_ROT_MAX, &tr->rotation.roll};
	if (type == TYPE_SPHERE)
		sl[i++] = (t_islider){"Scale", SL_SCALE_MIN, SL_SCALE_MAX, &tr->scale.x};
	else if (type == TYPE_CYLINDER || type == TYPE_CONE)
	{
		sl[i++] = (t_islider){"Radius", SL_SCALE_MIN, SL_SCALE_MAX, &tr->scale.x};
		sl[i++] = (t_islider){"Height", SL_SCALE_MIN, SL_SCALE_MAX, &tr->scale.y};
	}
	else if (type == TYPE_MESH)
	{
		sl[i++] = (t_islider){"Scale X", SL_SCALE_MIN, SL_SCALE_MAX, &tr->scale.x};
		sl[i++] = (t_islider){"Scale Y", SL_SCALE_MIN, SL_SCALE_MAX, &tr->scale.y};
		sl[i++] = (t_islider){"Scale Z", SL_SCALE_MIN, SL_SCALE_MAX, &tr->scale.z};
	}
	else if (type == TYPE_PLANE)
		sl[i++] = (t_islider){"UV Scale", SL_SCALE_MIN, SL_SCALE_MAX, &tr->scale.x};
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
	if (gui->selection.type == TYPE_SPHERE)
		tr->scale.y = tr->scale.z = tr->scale.x;
	mlx_string_put(gui->win.mlx, gui->win.win,
		x + 8, 88, COL_HOVER, "TRANSFORM");
	build_tr_sliders(tr, gui->selection.type, sl, &count);
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
	build_tr_sliders(tr, gui->selection.type, sl, &count);
	y = 104;
	i = 0;
	while (i < count)
	{
		void	(*cb)(t_gui *);

		cb = NULL;
		if (gui->selection.type == TYPE_SPHERE && i == 6)
			cb = sphere_scale_sync;
		else if (gui->selection.type == TYPE_MESH)
			cb = mesh_transform_sync;
		if (try_islider_click(gui, mouse, vec2i(x + 8, y), sl[i], cb))
			return (true);
		y += 30;
		i++;
	}
	return (false);
}
