/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:32:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 01:32:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	app_cleanup(t_app *app)
{
	if (!app)
		return ;
	pool_destroy(&app->pool);
	bvh_free(&app->bvh);
	pick_free(&app->pick);
	phys_free(&app->phys);
	scene_free(&app->scene);
	free(app->accum);
	if (app->img.img && app->mlx)
		mlx_destroy_image(app->mlx, app->img.img);
	if (app->win && app->mlx)
		mlx_destroy_window(app->mlx, app->win);
	if (app->mlx)
	{
		mlx_destroy_display(app->mlx);
		free(app->mlx);
	}
}
