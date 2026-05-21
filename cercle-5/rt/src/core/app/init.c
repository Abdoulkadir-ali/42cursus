/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:29:28 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 01:32:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	app_init_subsystems(t_app *app, char *path)
{
	if (scene_init(&app->scene) < 0)
		return (die("scene_init"));
	phys_init(&app->phys);
	if (!parse_file(path, app))
	{
		scene_free(&app->scene);
		phys_free(&app->phys);
		return (1);
	}
	if (ensure_default_texture(&app->scene) < 0)
	{
		scene_free(&app->scene);
		return (die("texture"));
	}
	if (window_init(app) < 0)
	{
		app_cleanup(app);
		return (die("window_init"));
	}
	return (0);
}
