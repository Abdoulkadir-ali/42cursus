/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:54:53 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 19:58:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"
#include "skeletal.h"

typedef enum e_xfm_kind { XFM_T, XFM_R, XFM_S } t_xfm_kind;

static t_vec3	tri_centroid(const t_triangle *t)
{
	t_vec3	s;

	s = v3_add(v3_add(t->a, t->b), t->c);
	return (v3_mul(s, 1.0f / 3.0f));
}

static t_vec3	selection_pivot(t_scene *s, int sel)
{
	t_vec3	c;
	t_object	*o;
	size_t	i;
	size_t	n;
	int	gid;

	c = v3(0, 0, 0);
	if (sel == 0x7fffffff)
		return (c);
	if (sel < 0)
	{
		i = (size_t)(-sel - 1);
		if (i < (size_t)s->n_planes)
			return (s->planes[i].u.pln.point);
		return (c);
	}
	if (sel >= (int)s->n_bvh)
		return (c);
	o = &s->bvh_objs[sel];
	if (o->group_id > 0)
	{
		gid = o->group_id;
		n = 0;
		i = 0;
		while (i < s->n_bvh)
		{
			if (s->bvh_objs[i].group_id == gid
				&& s->bvh_objs[i].type == OBJ_TRIANGLE)
			{
				c = v3_add(c, tri_centroid(&s->bvh_objs[i].u.tri));
				n++;
			}
			i++;
		}
		if (n > 0)
			c = v3_mul(c, 1.0f / n);
		return (c);
	}
	if (o->type == OBJ_SPHERE)
		return (o->u.sph.center);
	if (o->type == OBJ_PLANE)
		return (o->u.pln.point);
	if (o->type == OBJ_CYLINDER)
		return (o->u.cyl.base);
	if (o->type == OBJ_TRIANGLE)
		return (tri_centroid(&o->u.tri));
	return (c);
}

static t_vec3	rot_pos(t_vec3 p, t_vec3 piv, const float m[9])
{
	t_vec3	r;
	t_vec3	o;

	r = v3_sub(p, piv);
	o.x = m[0] * r.x + m[1] * r.y + m[2] * r.z;
	o.y = m[3] * r.x + m[4] * r.y + m[5] * r.z;
	o.z = m[6] * r.x + m[7] * r.y + m[8] * r.z;
	return (v3_add(piv, o));
}

static t_vec3	rot_dir(t_vec3 v, const float m[9])
{
	t_vec3	o;

	o.x = m[0] * v.x + m[1] * v.y + m[2] * v.z;
	o.y = m[3] * v.x + m[4] * v.y + m[5] * v.z;
	o.z = m[6] * v.x + m[7] * v.y + m[8] * v.z;
	return (o);
}

static void	rot_axis_angle(int axis, float deg, float m[9])
{
	float	r;
	float	c;
	float	s;

	r = deg * 0.017453292519943295f;
	c = cosf(r);
	s = sinf(r);
	if (axis == 0)
	{
		m[0] = 1; m[1] = 0; m[2] = 0;
		m[3] = 0; m[4] = c; m[5] = -s;
		m[6] = 0; m[7] = s; m[8] = c;
	}
	else if (axis == 1)
	{
		m[0] = c; m[1] = 0; m[2] = s;
		m[3] = 0; m[4] = 1; m[5] = 0;
		m[6] = -s; m[7] = 0; m[8] = c;
	}
	else
	{
		m[0] = c; m[1] = -s; m[2] = 0;
		m[3] = s; m[4] = c; m[5] = 0;
		m[6] = 0; m[7] = 0; m[8] = 1;
	}
}

static void	obj_translate(t_object *o, t_vec3 d)
{
	if (o->type == OBJ_SPHERE)
		o->u.sph.center = v3_add(o->u.sph.center, d);
	else if (o->type == OBJ_PLANE)
		o->u.pln.point = v3_add(o->u.pln.point, d);
	else if (o->type == OBJ_CYLINDER)
		o->u.cyl.base = v3_add(o->u.cyl.base, d);
	else if (o->type == OBJ_TRIANGLE)
	{
		o->u.tri.a = v3_add(o->u.tri.a, d);
		o->u.tri.b = v3_add(o->u.tri.b, d);
		o->u.tri.c = v3_add(o->u.tri.c, d);
	}
}

static void	tri_recompute_normal(t_triangle *t)
{
	t_vec3	e1;
	t_vec3	e2;

	e1 = v3_sub(t->b, t->a);
	e2 = v3_sub(t->c, t->a);
	t->n = v3_norm(v3_cross(e1, e2));
}

static void	obj_rotate(t_object *o, t_vec3 piv, const float m[9])
{
	if (o->type == OBJ_SPHERE)
		o->u.sph.center = rot_pos(o->u.sph.center, piv, m);
	else if (o->type == OBJ_PLANE)
	{
		o->u.pln.point = rot_pos(o->u.pln.point, piv, m);
		o->u.pln.normal = v3_norm(rot_dir(o->u.pln.normal, m));
	}
	else if (o->type == OBJ_CYLINDER)
	{
		o->u.cyl.base = rot_pos(o->u.cyl.base, piv, m);
		o->u.cyl.axis = v3_norm(rot_dir(o->u.cyl.axis, m));
	}
	else if (o->type == OBJ_TRIANGLE)
	{
		o->u.tri.a = rot_pos(o->u.tri.a, piv, m);
		o->u.tri.b = rot_pos(o->u.tri.b, piv, m);
		o->u.tri.c = rot_pos(o->u.tri.c, piv, m);
		tri_recompute_normal(&o->u.tri);
	}
}

static void	obj_scale(t_object *o, t_vec3 piv, float k)
{
	if (o->type == OBJ_SPHERE)
	{
		o->u.sph.center = v3_add(piv,
			v3_mul(v3_sub(o->u.sph.center, piv), k));
		o->u.sph.radius *= k;
		o->u.sph.radius2 = o->u.sph.radius * o->u.sph.radius;
	}
	else if (o->type == OBJ_PLANE)
		o->u.pln.point = v3_add(piv,
			v3_mul(v3_sub(o->u.pln.point, piv), k));
	else if (o->type == OBJ_CYLINDER)
	{
		o->u.cyl.base = v3_add(piv,
			v3_mul(v3_sub(o->u.cyl.base, piv), k));
		o->u.cyl.radius *= k;
		o->u.cyl.radius2 = o->u.cyl.radius * o->u.cyl.radius;
		o->u.cyl.height *= k;
	}
	else if (o->type == OBJ_TRIANGLE)
	{
		o->u.tri.a = v3_add(piv, v3_mul(v3_sub(o->u.tri.a, piv), k));
		o->u.tri.b = v3_add(piv, v3_mul(v3_sub(o->u.tri.b, piv), k));
		o->u.tri.c = v3_add(piv, v3_mul(v3_sub(o->u.tri.c, piv), k));
		tri_recompute_normal(&o->u.tri);
	}
}

static void	selection_apply(t_scene *s, int sel, t_xfm_kind kind,
						 t_vec3 piv, const void *data)
{
	t_object	*o;
	size_t		i;
	int		gid;

	if (sel == 0x7fffffff)
		return ;
	if (sel < 0)
	{
		i = (size_t)(-sel - 1);
		if (i >= (size_t)s->n_planes)
			return ;
		o = &s->planes[i];
	}
	else if (sel < (int)s->n_bvh)
		o = &s->bvh_objs[sel];
	else
		return ;
	if (sel >= 0 && o->group_id > 0)
	{
		gid = o->group_id;
		i = 0;
		while (i < s->n_bvh)
		{
			if (s->bvh_objs[i].group_id == gid)
			{
				if (kind == XFM_T)
					obj_translate(&s->bvh_objs[i], *(const t_vec3 *)data);
				else if (kind == XFM_R)
					obj_rotate(&s->bvh_objs[i], piv, (const float *)data);
				else
					obj_scale(&s->bvh_objs[i], piv, *(const float *)data);
			}
			i++;
		}
		if (s->animator
			&& ((t_animator *)s->animator)->group_id == gid)
			skel_animator_extra_apply((t_animator *)s->animator,
				(int)kind, piv, data);
		return ;
	}
	if (kind == XFM_T)
		obj_translate(o, *(const t_vec3 *)data);
	else if (kind == XFM_R)
		obj_rotate(o, piv, (const float *)data);
	else
		obj_scale(o, piv, *(const float *)data);
}

static void	inspector_geom(t_app *app, t_object *o)
{
	int	rebuild;

	rebuild = 0;
	if (o->type == OBJ_SPHERE)
	{
		rebuild |= ui_slider_f(app, "x", &o->u.sph.center.x, -50, 50);
		rebuild |= ui_slider_f(app, "y", &o->u.sph.center.y, -50, 50);
		rebuild |= ui_slider_f(app, "z", &o->u.sph.center.z, -50, 50);
		if (ui_slider_f(app, "radius", &o->u.sph.radius, 0.05f, 20.0f))
		{
			o->u.sph.radius2 = o->u.sph.radius * o->u.sph.radius;
			rebuild = 1;
		}
	}
	else if (o->type == OBJ_PLANE)
	{
		ui_slider_f(app, "px", &o->u.pln.point.x, -50, 50);
		ui_slider_f(app, "py", &o->u.pln.point.y, -50, 50);
		ui_slider_f(app, "pz", &o->u.pln.point.z, -50, 50);
		app->dirty = 1;
	}
	else
	{
		rebuild |= ui_slider_f(app, "bx", &o->u.cyl.base.x, -50, 50);
		rebuild |= ui_slider_f(app, "by", &o->u.cyl.base.y, -50, 50);
		rebuild |= ui_slider_f(app, "bz", &o->u.cyl.base.z, -50, 50);
		if (ui_slider_f(app, "radius", &o->u.cyl.radius, 0.05f, 20.0f))
		{
			o->u.cyl.radius2 = o->u.cyl.radius * o->u.cyl.radius;
			rebuild = 1;
		}
		rebuild |= ui_slider_f(app, "height", &o->u.cyl.height, 0.1f, 50.0f);
	}
	if (rebuild)
	{
		bvh_rebuild(app);
		app->dirty = 1;
	}
}

static void	inspector_transform(t_app *app, t_object *o)
{
	t_vec3	piv;
	t_vec3	pos;
	static t_vec3 rot = {0, 0, 0};
	static t_vec3 scale = {1, 1, 1};
	float	mat[9];
	int	dirty;
	static int last_selected = -1;

	(void)o;

	piv = selection_pivot(&app->scene, app->selected);
	pos = piv;

	if (app->selected != last_selected)
	{
		rot = v3(0, 0, 0);
		scale = v3(1, 1, 1);
		last_selected = app->selected;
	}

	ui_section(app, "-- Transform --");
	if (ui_vec3_edit(app, "Position", &pos))
	{
		t_vec3 d = v3_sub(pos, piv);
		selection_apply(&app->scene, app->selected, XFM_T, piv, &d);
		dirty = 1;
	}

	t_vec3 old_rot = rot;
	if (ui_vec3_edit(app, "Rotation", &rot))
	{
		if (rot.x != old_rot.x)
		{
			rot_axis_angle(0, rot.x - old_rot.x, mat);
			selection_apply(&app->scene, app->selected, XFM_R, piv, mat);
		}
		if (rot.y != old_rot.y)
		{
			rot_axis_angle(1, rot.y - old_rot.y, mat);
			selection_apply(&app->scene, app->selected, XFM_R, piv, mat);
		}
		if (rot.z != old_rot.z)
		{
			rot_axis_angle(2, rot.z - old_rot.z, mat);
			selection_apply(&app->scene, app->selected, XFM_R, piv, mat);
		}
		dirty = 1;
	}

	t_vec3 old_scale = scale;
	if (ui_vec3_edit(app, "Scale", &scale))
	{
		float k = 1.0f;
		if (scale.x != old_scale.x)
			k = scale.x / old_scale.x;
		else if (scale.y != old_scale.y)
			k = scale.y / old_scale.y;
		else if (scale.z != old_scale.z)
			k = scale.z / old_scale.z;

		if (k > 0.001f && k < 1000.0f)
		{
			selection_apply(&app->scene, app->selected, XFM_S, piv, &k);
			dirty = 1;
		}
		else
			scale = old_scale;
	}

	if (dirty)
	{
		if (app->ui.active_id != 0)
		{
			bvh_refit(&app->bvh, app->scene.bvh_objs);
			bvh_prepare_simd(&app->bvh, app->scene.bvh_objs);
		}
		else
			bvh_rebuild(app);
		app->dirty = 1;
	}
}

static void	subpanel_transform(t_app *app, t_object *o)
{
	inspector_transform(app, o);
}

static void	subpanel_material(t_app *app, t_object *o)
{
	if (o->group_id > 0)
	{
		int gid = o->group_id;
		int n = 0;
		size_t i = 0;
		char buf[64];

		while (i < app->scene.n_bvh)
		{
			if (app->scene.bvh_objs[i++].group_id == gid)
				n++;
		}
		snprintf(buf, sizeof(buf), "Mesh group (%d tris)", n);
		ui_label(app, buf);
	}
	else
	{
		const char *names[] = {"Sphere", "Plane", "Cylinder", "Triangle"};
		ui_label(app, (o->type >= 0 && o->type <= 3) ? names[o->type] : "Object");
	}
	inspector_geom(app, o);
	if (ui_color_swatch(app, "color", &o->mat.albedo))
	{
		o->color = o->mat.albedo;
		scene_group_propagate(&app->scene, app->selected);
		app->dirty = 1;
	}
	ui_slider_f(app, "spec ks", &o->mat.ks, 0.0f, 1.0f);
	ui_slider_f(app, "shine", &o->mat.shininess, 1.0f, 256.0f);
	ui_slider_f(app, "reflect", &o->mat.reflectivity, 0.0f, 1.0f);
	ui_slider_f(app, "opacity", &o->mat.opacity, 0.0f, 1.0f);
	ui_slider_f(app, "ior", &o->mat.ior, 1.0f, 2.5f);
	ui_slider_i(app, "tex id", &o->mat.tex_id, -1, app->scene.n_textures - 1);
	ui_log_f(app, "temp K", &o->mat.temperature, 100.0f, 4.0e4f);
	ui_log_f(app, "emission", &o->mat.emission, 0.001f, 1.0e6f);
	if (ui_button(app, o->group_id > 0 ? "Delete group" : "Delete object") && app->selected >= 0)
	{
		scene_group_delete(&app->scene, app->selected);
		app->selected = 0x7fffffff;
		bvh_rebuild(app);
		phys_rebuild_body_table(app);
		app->dirty = 1;
	}
}

static void	subpanel_physics(t_app *app, t_object *o)
{
	(void)o;
	int bi = phys_body_for_sphere(&app->phys, app->selected);
	if (bi < 0)
	{
		if (ui_button(app, "Make dynamic (m=1)"))
		{
			phys_add_body(&app->phys, app->selected, 1.0f, 0.55f, v3(0, 0, 0));
			app->phys.enabled = 1;
		}
	}
	else
	{
		t_body	*b = &app->phys.bodies[bi];
		char pbuf[96];
		if (ui_log_f(app, "mass", &b->mass, 1.0e-3f, 1.0e9f))
			b->inv_mass = (b->mass > 0.0f) ? 1.0f / b->mass : 0.0f;
		ui_slider_f(app, "restitution", &b->restitution, 0.0f, 1.0f);
		ui_log_f(app, "temp K", &b->temperature, 100.0f, 4.0e4f);
		ui_log_f(app, "ambient K", &b->temp_ambient, 50.0f, 1000.0f);
		snprintf(pbuf, sizeof(pbuf), "%.2f m/s", sqrtf(v3_dot(b->vel, b->vel)));
		ui_label_value(app, "speed", pbuf);
		if (ui_button(app, "Reset velocity"))
			b->vel = v3(0, 0, 0);
	}
}

void	panel_object_right(t_app *app)
{
	int	panel_w = UI_SIDEBAR_W;
	int	top_margin = UI_PAD * 5;
	int	px = app->img.w - panel_w - UI_PAD;
	int	py = top_margin;
	t_object	*o;

	app->ui.cursor_x = px + UI_PAD;
	app->ui.panel_x = px;
	app->ui.panel_y = py;
	app->ui.panel_w = panel_w;
	ui_panel_begin(app, px, py, app->img.h - top_margin, panel_w, "Object Inspector");
	o = scene_obj_at(&app->scene, app->selected);
	if (!o)
	{
		ui_panel_end(app, NULL);
		return ;
	}
	ui_section(app, "Object Properties");
	int tw = (panel_w - UI_PAD * 2 - 8) / 3;
	if (ui_tab(app, "Xform", app->ui.obj_tab == 0, tw))
		app->ui.obj_tab = 0;
	if (ui_tab(app, "Mat", app->ui.obj_tab == 1, tw))
		app->ui.obj_tab = 1;
	if (ui_tab(app, "Phys", app->ui.obj_tab == 2, tw))
		app->ui.obj_tab = 2;
	app->ui.cursor_y += UI_PAD;
	app->ui.cursor_x = px + UI_PAD;
	app->ui.cursor_y += 2;
	ui_scroll_begin(app, app->img.h / 2 - 120, &g_layout.obj_scroll);
	if (app->ui.obj_tab == 0)
		subpanel_transform(app, o);
	else if (app->ui.obj_tab == 1)
		subpanel_material(app, o);
	else if (app->ui.obj_tab == 2)
		subpanel_physics(app, o);
	ui_scroll_end(app, &g_layout.obj_scroll);
	ui_panel_end(app, NULL);
}
