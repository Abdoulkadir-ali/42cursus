/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:31:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "gui.h"

void  make_camera_ray(t_render *ctx, double x, double y, t_ray *ray)
{
	double	px;
	double	py;
	t_vec3	dir;

	px = (x + 0.5) * ctx->px_step_x - ctx->px_off_x;
	py = ctx->px_off_y - (y + 0.5) * ctx->px_step_y;
	dir = vec3_norm(vec3_add(ctx->transform.forward,
				vec3_add(vec3_scale(ctx->transform.right, px),
					vec3_scale(ctx->transform.up, py))));
	ray_init(ray, ctx->transform.pos, dir);
}
