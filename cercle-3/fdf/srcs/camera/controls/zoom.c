/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:21:26 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/21 19:52:05 by abdoali          ###   ########.fr       */
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
	ctx->camera->scale = ctx->camera->target_scale;
}
