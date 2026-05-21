/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/02 16:41:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"
#include <stdlib.h>

#define EMIT_CAP 256

void	rebuild_emitters(t_app *app)
{
	int			i;
	int			n;
	float		p;
	const t_object	*o;

	n = 0;
	if (!app->set.rt.emitters_as_lights)
	{
		app->scene.n_emit = 0;
		return ;
	}
	if (app->scene.cap_emit < EMIT_CAP)
	{
		free(app->scene.emit_idx);
		app->scene.emit_idx = (size_t *)malloc(sizeof(size_t) * EMIT_CAP);
		app->scene.cap_emit = app->scene.emit_idx ? EMIT_CAP : 0;
	}
	if (!app->scene.emit_idx)
	{
		app->scene.n_emit = 0;
		return ;
	}
	i = 0;
	while (i < (int)app->scene.n_bvh && n < EMIT_CAP)
	{
		o = &app->scene.bvh_objs[i];
		p = o->mat.emission;
		if (o->mat.emit_power > 0.0f)
			p += o->mat.emit_power;
		if (p > 0.01f)
			app->scene.emit_idx[n++] = i;
		i++;
	}
	app->scene.n_emit = n;
}
