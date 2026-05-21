/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 02:29:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 02:29:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "core.h"

static void	setup_lights(t_scene *s)
{
	t_light	*l;

	l = scene_push_light(s);
	if (l)
	{
		l->pos = v3(8, 12, -6);
		l->ratio = 0.9f;
		l->color = v3(1.00f, 0.95f, 0.85f);
	}
	l = scene_push_light(s);
	if (l)
	{
		l->pos = v3(-10, 6, -2);
		l->ratio = 0.5f;
		l->color = v3(0.55f, 0.70f, 1.00f);
	}
	l = scene_push_light(s);
	if (l)
	{
		l->pos = v3(0, 8, 12);
		l->ratio = 0.6f;
		l->color = v3(1.00f, 0.85f, 0.70f);
	}
}

int	setup_default_scene(t_app *app)
{
	t_scene		*s;
	t_object	*pl;

	s = &app->scene;
	s->amb.ratio = 0.2f;
	s->amb.color = v3(1, 1, 1);
	s->amb.set = 1;
	s->cam.pos = v3(0, 5, -15);
	s->cam.dir = v3(0, 0, 1);
	s->cam.fov = 70.0f;
	s->cam_set = 1;
	setup_lights(s);
	pl = scene_push_plane(s);
	if (pl)
	{
		pl->type = OBJ_PLANE;
		pl->u.pln.point = v3(0, -1.0f, 0);
		pl->u.pln.normal = v3(0, 1, 0);
		pl->color = v3(0.55f, 0.55f, 0.6f);
		mat_init_default(&pl->mat, pl->color);
		pl->mat.roughness = 0.85f;
	}
	return (1);
}
