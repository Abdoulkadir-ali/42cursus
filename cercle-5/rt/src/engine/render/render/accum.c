/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accum.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:28:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"
#include <stdlib.h>
#include <string.h>

void	accum_ensure(t_app *app)
{
	size_t	n;

	if (app->accum_w == app->img.w && app->accum_h == app->img.h && app->accum)
		return ;
	free(app->accum);
	free(app->depth_buffer);
	free(app->taa_scratch);
	app->accum_w = app->img.w;
	app->accum_h = app->img.h;
	n = (size_t)app->accum_w * app->accum_h;
	app->accum = (float *)malloc(sizeof(float) * n * 3);
	app->depth_buffer = (float *)malloc(sizeof(float) * n);
	app->taa_scratch = (float *)malloc(sizeof(float) * n * 3);
	if (app->accum)
		memset(app->accum, 0, sizeof(float) * n * 3);
	if (app->taa_scratch)
		memset(app->taa_scratch, 0, sizeof(float) * n * 3);
	if (app->depth_buffer)
	{
		for (size_t i = 0; i < n; i++)
			app->depth_buffer[i] = 1e30f;
	}
	app->accum_samples = 0;
}
