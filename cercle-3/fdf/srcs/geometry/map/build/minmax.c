/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minmax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:23:38 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:36:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

/**
 * @brief Scan one row while updating min and max height state.
 * @param ctx Running min/max accumulator.
 * @param map Map being scanned.
 * @param y Row index to process.
 */
static void	process_min_max_row(t_find_min_max_ctx *ctx, t_map *map, int y)
{
	ctx->pos.y = y;
	ctx->pos.x = 0;
	while (ctx->pos.x < (int)map->width)
	{
		ctx->idx = (size_t)ctx->pos.y * map->width + ctx->pos.x;
		ctx->val = map->points.raw[ctx->idx].z;
		if (ctx->first)
		{
			ctx->min_val = ctx->val;
			ctx->max_val = ctx->val;
			ctx->first = 0;
		}
		else
		{
			if (ctx->val < ctx->min_val)
				ctx->min_val = ctx->val;
			if (ctx->val > ctx->max_val)
				ctx->max_val = ctx->val;
		}
		ctx->pos.x++;
	}
}

/**
 * @brief Find the minimum and maximum raw z values in a map.
 * @param map Map to scan.
 * @param min Output minimum z value.
 * @param max Output maximum z value.
 */
void	find_min_max_z(t_map *map, float *min, float *max)
{
	t_find_min_max_ctx	ctx;
	size_t				y;

	ctx.first = 1;
	y = 0;
	while (y < map->height)
	{
		process_min_max_row(&ctx, map, y);
		y++;
	}
	*min = ctx.min_val;
	*max = ctx.max_val;
}

/**
 * @brief Store the map's raw z range inside `min_max_z`.
 * @param map Map to update.
 */
void	calculate_min_max_z(t_map *map)
{
	float	min_z;
	float	max_z;

	find_min_max_z(map, &min_z, &max_z);
	map->min_max_z.x = min_z;
	map->min_max_z.y = max_z;
}
