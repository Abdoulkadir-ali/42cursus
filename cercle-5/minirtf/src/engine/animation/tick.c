/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 04:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/02 17:11:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "skeletal.h"

static void	advance_skinning(t_app *app, t_animator *a)
{
	skel_reskin_all(a, &app->scene);
	bvh_refit(&app->bvh, app->scene.bvh_objs);
	bvh_prepare_simd(&app->bvh, app->scene.bvh_objs);
	app->dirty = 1;
}

void	skel_animator_tick(t_app *app, float dt)
{
	t_animator	*a;

	a = (t_animator *)app->scene.animator;
	if (!a)
		return ;
	if (a->playing && a->active >= 0 && a->active < a->n_clips)
	{
		float	dur;

		a->time += dt * a->speed;
		dur = skel_animator_clip_duration(a, a->active);
		if (dur > 0.0f)
		{
			if (a->loop)
			{
				while (a->time >= dur)
					a->time -= dur;
				while (a->time < 0.0f)
					a->time += dur;
			}
			else
			{
				if (a->time >= dur)
				{
					a->time = dur;
					a->playing = 0;
				}
				if (a->time < 0.0f)
					a->time = 0.0f;
			}
		}
	}
	skel_reset_to_bind(a);
	if (a->active >= 0)
		skel_apply_clip(a);
	skel_compute_world(a);
	if (app->set.anim.anim_skinning)
		advance_skinning(app, a);
}
