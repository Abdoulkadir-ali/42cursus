/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sidebar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:55:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"

static int	_scene_grow_bvh(t_scene *s)
{
	t_object	*tmp;
	size_t	cap;

	if (s->n_bvh + 1 <= s->cap_bvh)
		return (0);
	if (s->cap_bvh == 0)
		cap = 16;
	else
		cap = s->cap_bvh * 2;
	tmp = realloc(s->bvh_objs, sizeof(t_object) * cap);
	if (!tmp)
		return (-1);
	s->bvh_objs = tmp;
	s->cap_bvh = cap;
	return (0);
}

static void	_add_default_sphere(t_app *app)
{
	t_object	o;

	memset(&o, 0, sizeof(o));
	if (_scene_grow_bvh(&app->scene) < 0)
		return ;
	o.type = OBJ_SPHERE;
	o.u.sph.center = v3_add(app->scene.cam.pos, v3_mul(app->scene.cam.dir, 4.0f));
	o.u.sph.radius = 1.0f;
	o.u.sph.radius2 = 1.0f;
	o.color = v3(0.8f, 0.5f, 0.3f);
	mat_init_default(&o.mat, o.color);
	app->scene.bvh_objs[app->scene.n_bvh++] = o;
	phys_ensure_all_bodies(app);
	bvh_rebuild(app);
	app->dirty = 1;
}

static void	_add_default_cyl(t_app *app)
{
	t_object	o;

	memset(&o, 0, sizeof(o));
	if (_scene_grow_bvh(&app->scene) < 0)
		return ;
	o.type = OBJ_CYLINDER;
	o.u.cyl.base = v3_add(app->scene.cam.pos, v3_mul(app->scene.cam.dir, 4.0f));
	o.u.cyl.axis = v3(0, 1, 0);
	o.u.cyl.radius = 0.7f;
	o.u.cyl.radius2 = 0.49f;
	o.u.cyl.height = 2.0f;
	o.color = v3(0.4f, 0.7f, 0.9f);
	mat_init_default(&o.mat, o.color);
	app->scene.bvh_objs[app->scene.n_bvh++] = o;
	phys_ensure_all_bodies(app);
	bvh_rebuild(app);
	app->dirty = 1;
}

static void	subpanel_scene(t_app *app)
{
	char	buf[128];
	size_t	i;
	static int	group_counts[64];
	static int	last_n = -1;

	int		mx = app->input.mouse_x;
	int		in_left_panel = (mx < UI_SIDEBAR_W + UI_PAD * 2);

	if (last_n != (int)app->scene.n_bvh)
	{
		memset(group_counts, 0, sizeof(group_counts));
		for (size_t k = 0; k < app->scene.n_bvh; k++)
		{
			int g = app->scene.bvh_objs[k].group_id;
			if (g > 0 && g < 64)
				group_counts[g]++;
		}
		last_n = (int)app->scene.n_bvh;
	}
	i = 0;
	int seen[64] = {0};
	while (i < app->scene.n_bvh)
	{
		const t_object	*o = &app->scene.bvh_objs[i];
		int		gid = o->group_id;
		if (gid > 0 && gid < 64)
		{
			if (seen[gid])
			{
				i++;
				continue ;
			}
			seen[gid] = 1;
			const char *nm = (app->scene.group_names[gid][0]) ? app->scene.group_names[gid] : "mesh";
			snprintf(buf, sizeof(buf), "[M] %s (%d)", nm, group_counts[gid]);
			int sel_gid = (app->selected >= 0 && app->selected < (int)app->scene.n_bvh && app->scene.bvh_objs[app->selected].group_id == gid);
			if (ui_select_row(app, buf, sel_gid) && in_left_panel)
				app->selected = (int)i;
		}
		else if (gid <= 0)
		{
			const char *kind = "obj";
			if (o->type == OBJ_SPHERE)
				kind = "sphere";
			else if (o->type == OBJ_CYLINDER)
				kind = "cyl";
			else if (o->type == OBJ_TRIANGLE)
				kind = "tri";
			snprintf(buf, sizeof(buf), "[%zu] %s", i, kind);
			if (ui_select_row(app, buf, app->selected == (int)i) && in_left_panel)
				app->selected = (int)i;
		}
		i++;
	}
	i = 0;
	while (i < app->scene.n_planes)
	{
		snprintf(buf, sizeof(buf), "[plane %zu]", i);
		if (ui_select_row(app, buf, app->selected == -(int)(i + 1)))
			app->selected = -(int)(i + 1);
		i++;
	}
}

void	panel_sidebar(t_app *app)
{
	int	top_margin = UI_PAD * 5;

	ui_panel_begin(app, 0, top_margin, app->img.h - top_margin, UI_SIDEBAR_W, "MiniRT Inspector");
	ui_section(app, "Scene Content");
	if (ui_button(app, "+ Sphere"))
		_add_default_sphere(app);
	if (ui_button(app, "+ Cylinder"))
		_add_default_cyl(app);
	if (ui_button(app, "Save scene.rt"))
		scene_save(&app->scene, "scene_out.rt");
	ui_scroll_begin(app, app->img.h / 2 - 40, &g_layout.scene_scroll);
	subpanel_scene(app);
	ui_scroll_end(app, &g_layout.scene_scroll);
	ui_panel_end(app, NULL);
}
