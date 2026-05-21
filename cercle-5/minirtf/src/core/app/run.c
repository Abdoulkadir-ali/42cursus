/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:27:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 01:29:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static void	setup_app_scene(t_app *app)
{
	layout_load();
	camera_setup(&app->scene.cam, app->img.w, app->img.h);
	app->scene.cam_prev = app->scene.cam;
	camera_init_yaw_pitch(&app->scene);
	bvh_build(&app->bvh, app->scene.bvh_objs, (int)app->scene.n_bvh);
	bvh_prepare_simd(&app->bvh, app->scene.bvh_objs);
	phys_ensure_all_bodies(app);
}

int	mini_rt(int argc, char **argv, int bench)
{
	t_app	app;

	memset(&app, 0, sizeof(app));
	settings_defaults(&app);
	if (app_init_subsystems(&app, argv[argc - 1]) != 0)
		return (1);
	setup_app_scene(&app);
	fprintf(stderr, "scene: %zu objects, %zu planes, BVH nodes=%zu\n",
		app.scene.n_bvh, app.scene.n_planes, app.bvh.n_nodes);
	if (pool_init(&app.pool, &app) < 0)
	{
		app_cleanup(&app);
		return (die("pool_init"));
	}
	if (bench > 0)
		run_bench(&app, bench);
	else
		window_loop(&app);
	layout_save();
	app_cleanup(&app);
	return (0);
}
