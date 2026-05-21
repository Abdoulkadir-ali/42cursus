/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 02:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 16:59:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "core.h"

static void	rotate_tri(t_object *o, int axis_ez)
{
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;
	t_vec3	na;
	t_vec3	nb;
	t_vec3	nc;

	a = o->u.tri.a;
	b = o->u.tri.b;
	c = o->u.tri.c;
	if (axis_ez)
	{
		na = v3(a.x, -a.z, a.y);
		nb = v3(b.x, -b.z, b.y);
		nc = v3(c.x, -c.z, c.y);
	}
	else
	{
		na = v3(-a.y, a.x, a.z);
		nb = v3(-b.y, b.x, b.z);
		nc = v3(-c.y, c.x, c.z);
	}
	o->u.tri.a = na;
	o->u.tri.b = nb;
	o->u.tri.c = nc;
	o->u.tri.n = v3_norm(v3_cross(v3_sub(nb, na), v3_sub(nc, na)));
}

static void	get_mesh_bounds(t_scene *s, t_vec3 *mn, t_vec3 *mx)
{
	size_t	i;
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;

	*mn = (t_vec3){1e30f, 1e30f, 1e30f};
	*mx = (t_vec3){-1e30f, -1e30f, -1e30f};
	i = 0;
	while (i < s->n_bvh)
	{
		if (s->bvh_objs[i].type == OBJ_TRIANGLE)
		{
			a = s->bvh_objs[i].u.tri.a;
			b = s->bvh_objs[i].u.tri.b;
			c = s->bvh_objs[i].u.tri.c;
			mn->x = fminf(mn->x, fminf(a.x, fminf(b.x, c.x)));
			mn->y = fminf(mn->y, fminf(a.y, fminf(b.y, c.y)));
			mn->z = fminf(mn->z, fminf(a.z, fminf(b.z, c.z)));
			mx->x = fmaxf(mx->x, fmaxf(a.x, fmaxf(b.x, c.x)));
			mx->y = fmaxf(mx->y, fmaxf(a.y, fmaxf(b.y, c.y)));
			mx->z = fmaxf(mx->z, fmaxf(a.z, fmaxf(b.z, c.z)));
		}
		i++;
	}
}

void	autoorient_mesh(t_app *app)
{
	t_scene	*s;
	t_vec3	mn;
	t_vec3	mx;
	t_vec3	e;
	size_t	i;

	s = &app->scene;
	get_mesh_bounds(s, &mn, &mx);
	if (mn.x > mx.x)
		return ;
	e.x = mx.x - mn.x;
	e.y = mx.y - mn.y;
	e.z = mx.z - mn.z;
	if (e.y >= e.x && e.y >= e.z)
		return ;
	i = 0;
	while (i < s->n_bvh)
	{
		if (s->bvh_objs[i].type == OBJ_TRIANGLE)
			rotate_tri(&s->bvh_objs[i], e.z >= e.x);
		i++;
	}
}

static void	frame_lights_ground(t_scene *s, t_vec3 c, float r, t_vec3 mn)
{
	if (s->n_lights >= 1)
	{
		s->lights[0].pos = v3(c.x + 1.5f * r, c.y + 2.0f * r, c.z + 1.5f * r);
		s->lights[0].ratio = 1.0f;
	}
	if (s->n_lights >= 2)
		s->lights[1].pos = v3(c.x - 2.0f * r, c.y + 0.5f * r, c.z + 0.5f * r);
	if (s->n_lights >= 3)
		s->lights[2].pos = v3(c.x, c.y + 1.0f * r, c.z - 2.0f * r);
	if (s->n_planes > 0)
		s->planes[0].u.pln.point = v3(c.x, mn.y - 0.02f * r, c.z);
}

void	autoframe_camera(t_app *app)
{
	t_scene	*s;
	t_vec3	mn;
	t_vec3	mx;
	t_vec3	c;
	float	r;
	float	d;

	s = &app->scene;
	if (s->n_bvh <= 0)
		return ;
	get_mesh_bounds(s, &mn, &mx);
	if (mn.x > mx.x)
		return ;
	c = v3(0.5f * (mn.x + mx.x), 0.5f * (mn.y + mx.y), 0.5f * (mn.z + mx.z));
	r = 0.5f * fmaxf(mx.x - mn.x, fmaxf(mx.y - mn.y, mx.z - mn.z));
	if (r < 1e-4f)
		r = 1.0f;
	d = r / tanf(0.5f * s->cam.fov * (float)M_PI / 180.0f) * 1.6f;
	s->cam.pos = v3(c.x, c.y + 0.2f * r, c.z + d);
	s->cam.dir = v3_norm(v3_sub(c, s->cam.pos));
	frame_lights_ground(s, c, r, mn);
}
