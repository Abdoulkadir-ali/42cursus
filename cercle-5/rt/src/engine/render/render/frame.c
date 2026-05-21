/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/02 17:11:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"

void	rebuild_emitters(t_app *app);
void	accum_ensure(t_app *app);
void	taa_reproject(t_app *app);

void	render_frame(t_app *app)
{
	double	t0;
	double	t1;

	rebuild_emitters(app);
	if (app->set.render.progressive)
		accum_ensure(app);
	if (app->moving && app->set.render.taa)
	{
		taa_reproject(app);
		app->accum_samples = 1;
	}
	t0 = time_ms_now();
	pool_run(&app->pool);
	t1 = time_ms_now();
	app->time.last_render_ms = t1 - t0;
	if (app->set.render.progressive && app->set.render.downscale <= 1)
		app->accum_samples++;
	app->scene.cam_prev = app->scene.cam;
}
