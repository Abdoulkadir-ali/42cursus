/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:03:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "render.h"

static t_matrix4	build_view_matrix(t_camera *cam, t_matrix4 rot)
{
	float		cam_dist;
	float		tan_half;
	t_matrix4	translate;

	cam_dist = 500.0f;
	if (cam->projection == PROJ_CONIC)
	{
		tan_half = tanf((cam->alpha * (M_PI / 180.0f)) / 2.0f);
		if (tan_half < 0.001f)
			tan_half = 0.001f;
		cam_dist = 500.0f / tan_half;
	}
	cam->view_dist = cam_dist;
	translate = matrix_translation(0, 0, -cam_dist);
	return (matrix_multiply(translate, rot));
}

static void	set_rotation_matrix(t_matrix4 *rot, t_vec3d *rm)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		rot->m[i][0] = (float)rm[i].x;
		rot->m[i][1] = (float)rm[i].y;
		rot->m[i][2] = (float)rm[i].z;
		i++;
	}
}

void	calculate_transform_matrix(t_camera *cam)
{
	t_transform_ctx	ctx;

	ctx.rot = matrix_identity();
	set_rotation_matrix(&ctx.rot, cam->rotation_matrix);
	ctx.rot.m[3][3] = 1.0f;
	ctx.view = build_view_matrix(cam, ctx.rot);
	ctx.proj = get_projection_matrix(cam, 1.0f);
	ctx.mvp = matrix_multiply(ctx.proj, ctx.view);
	ctx.scale_factor = 50.0f;
	if (cam->projection == PROJ_CONIC)
		ctx.scale_factor *= 30.0f;
	ctx.scale_factor *= cam->scale;
	ctx.screen_scale = matrix_scale(ctx.scale_factor, ctx.scale_factor, 1.0f);
	ctx.mvp = matrix_multiply(ctx.screen_scale, ctx.mvp);
	cam->transform_matrix = ctx.mvp;
}
