/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:28:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 11:27:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

void	adjust_move_speed(t_events *events, int increase)
{
	if (increase)
	{
		events->camera->move_speed += 0.2;
		if (events->camera->move_speed > 5.0)
			events->camera->move_speed = 5.0;
	}
	else
	{
		events->camera->move_speed -= 0.2;
		if (events->camera->move_speed < 0.2)
			events->camera->move_speed = 0.2;
	}
}

static void	init_movement_ctx(t_movement_ctx *ctx, t_events *events)
{
	ctx->v = create_vec2d(0, 0);
	ctx->m = 1;
	if (events->camera->invert_movement)
		ctx->m = -1;
	ctx->speed = events->camera->move_speed;
}

static void	calculate_movement_vector(t_movement_ctx *ctx, t_events *events)
{
	t_keys	*keyboard;

	keyboard = &events->keys;
	if (keyboard->up)
		vec2d_add(&ctx->v, create_vec2d(0, -1 * ctx->m));
	if (keyboard->down)
		vec2d_add(&ctx->v, create_vec2d(0, 1 * ctx->m));
	if (keyboard->left)
		vec2d_add(&ctx->v, create_vec2d(-1 * ctx->m, 0));
	if (keyboard->right)
		vec2d_add(&ctx->v, create_vec2d(1 * ctx->m, 0));
}

static void	apply_movement(t_movement_ctx *ctx, t_events *events)
{
	t_vec2d	delta;

	vec2d_multiply_scalar(&ctx->v, ctx->speed);
	delta = ctx->v;
	vec2d_add(&events->camera->offset, delta);
	if (!isfinite(events->camera->offset.x)
		|| !isfinite(events->camera->offset.y))
	{
		events->camera->offset.x = 0.0;
		events->camera->offset.y = 0.0;
	}
}

static void	clamp_offset(t_events *events)
{
	double	max_off;

	if (!events->window)
		return ;
	if (events->window->width > events->window->height)
		max_off = (double)events->window->width * 100.0;
	else
		max_off = (double)events->window->height * 100.0;
	if (max_off > 500000.0)
		max_off = 500000.0;
	if (events->camera->offset.x > max_off)
		events->camera->offset.x = max_off;
	if (events->camera->offset.x < -max_off)
		events->camera->offset.x = -max_off;
	if (events->camera->offset.y > max_off)
		events->camera->offset.y = max_off;
	if (events->camera->offset.y < -max_off)
		events->camera->offset.y = -max_off;
}
