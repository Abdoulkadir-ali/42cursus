/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@gemini.google.com> +#    +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 00:00:00 by antigravity       #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	make_camera_ray(t_render_ctx *ctx, double x, double y, t_ray *ray)
{
	double	px;
	double	py;
	t_vec3	dir;

	px = (2.0 * (x + 0.5) / ctx->gui->win.width - 1.0) * ctx->half_width
		* ctx->aspect_ratio;
	py = (1.0 - 2.0 * (y + 0.5) / ctx->gui->win.height) * ctx->half_height
		* ctx->aspect_ratio;
	dir = vec3_norm(vec3_add(ctx->transform.forward,
				vec3_add(vec3_scale(ctx->transform.right, px),
					vec3_scale(ctx->transform.up, py))));
	ray_init(ray, ctx->transform.pos, dir);
}
