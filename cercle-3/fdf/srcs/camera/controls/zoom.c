/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:21:26 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 17:18:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

void	zoom_in(t_camera_manager *ctx)
{
	double	factor;

	factor = 1.0 + (0.1 * ctx->camera->zoom_speed);
	ctx->camera->target_scale *= factor;
	if (ctx->camera->target_scale > 100)
		ctx->camera->target_scale = 100;
}

void	zoom_out(t_camera_manager *ctx)
{
	double	factor;

	factor = 1.0 - (0.1 * ctx->camera->zoom_speed);
	ctx->camera->target_scale *= factor;
}

void	update_zoom(t_camera_manager *ctx)
{
	double	diff;

	if (!ctx || !ctx->camera)
		return ;
	diff = ctx->camera->target_scale - ctx->camera->scale;
	if (fabs(diff) < 0.001)
		ctx->camera->scale = ctx->camera->target_scale;
	else
		ctx->camera->scale += diff * 0.15;
}
