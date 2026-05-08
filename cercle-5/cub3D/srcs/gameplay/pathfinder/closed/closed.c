/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 23:23:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 03:54:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

static bool	push_tile(size_t *stack, size_t *top, size_t x, size_t y)
{
	stack[*top] = y;
	stack[*top + 1] = x;
	*top += 2;
	return (true);
}

static bool	visit_tile(t_map *map, bool *seen, size_t *stack, size_t *top)
{
	size_t	idx;
	size_t	x;
	size_t	y;

	x = stack[--(*top)];
	y = stack[--(*top)];
	idx = y * map->width + x;
	if (seen[idx] || !pf_closed_is_player_walkable(map->grid[y][x]))
		return (true);
	seen[idx] = true;
	if (!pf_closed_check_tile(map, x, y))
		return (false);
	push_tile(stack, top, x - 1, y);
	push_tile(stack, top, x + 1, y);
	push_tile(stack, top, x, y - 1);
	push_tile(stack, top, x, y + 1);
	return (true);
}

static bool	check_reachable(t_map *map, bool *seen, size_t x, size_t y)
{
	size_t	*stack;
	size_t	top;
	bool	closed;

	stack = malloc(sizeof(size_t) * map->width * map->height * 2);
	if (stack == NULL)
		return (false);
	top = 0;
	closed = true;
	push_tile(stack, &top, x, y);
	while (top > 0 && closed)
		closed = visit_tile(map, seen, stack, &top);
	free(stack);
	return (closed);
}

static bool	is_closed(t_map *map, bool *seen, size_t x, size_t y)
{
	bool	b1;
	bool	b2;
	bool	b3;

	b1 = check_reachable(map, seen, x, y);
	b2 = pf_closed_check_sprite_cells(map);
	b3 = pf_closed_check_hborders(map);
	return (b1 && b2 && b3);
}

bool	pf_check_closed(t_map *map)
{
	bool	*seen;
	bool	closed;
	size_t	x;
	size_t	y;

	x = (size_t)map->player_spawn.pos.x;
	y = (size_t)map->player_spawn.pos.y;
	seen = ft_calloc(map->width * map->height, sizeof(bool));
	if (seen == NULL)
		return (false);
	closed = is_closed(map, seen, x, y);
	free(seen);
	return (closed);
}
