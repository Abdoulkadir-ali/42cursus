/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 16:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 03:22:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static void	set_player_spawn(t_map *map, t_vec2s pos, char dir)
{
	map->player_spawn.pos.x = (float)pos.x + 0.5f;
	map->player_spawn.pos.y = (float)pos.y + 0.5f;
	map->player_spawn.dir = dir;
}

/*
** set_grid_cell:
** Validates a single character against our strict whitelist.
** - If it's a player spawn (N,S,E,W),
**		it registers the pos and replaces with '0'.
** - If it's in our strict whitelist (0,1, doors, enemies, items),
	it's accepted.
** - If it's an unrecognized non-space character (e.g., /, -, etc.), parsing
**   halts immediately and an error is thrown. No silent fallbacks.
** - If it's whitespace, it triggers padding logic.
*/
static int	set_grid_cell(t_map *map, t_vec2s pos, char c, size_t *player_found)
{
	if (ft_strchr("NSEW", c) != NULL || (c == 'E' && *player_found == 0))
	{
		if (*player_found != 0)
			return (0);
		*player_found = 1;
		set_player_spawn(map, pos, c);
		map->grid[pos.y][pos.x] = '0';
	}
	else if (ft_strchr("012DOdeEGMmPpsA ", c) != NULL)
		map->grid[pos.y][pos.x] = c;
	else if (ft_isspace((unsigned char)c) != 0)
		map->grid[pos.y][pos.x] = ' ';
	else
	{
		print_error("Invalid map character at (%zu, %zu): '%c'", pos.x, pos.y,
			c);
		return (2);
	}
	return (1);
}

static size_t	get_max_raw_width(char **raw, size_t count)
{
	size_t	w;
	size_t	i;
	size_t	len;

	w = 0;
	i = 0;
	while (i < count)
	{
		len = 0;
		while (raw[i][len] != '\0' && raw[i][len] != '\n'
			&& raw[i][len] != '\r')
			len++;
		if (len > w)
			w = len;
		i++;
	}
	return (w);
}

/*
** fill_grid_row:
** Maps a single ragged line from the .cub file into a normalized grid row.
** Since map lines can be of varying lengths, this function pads the remainder
** of the row with solid walls ('1') up to map->width, ensuring a perfectly
** rectangular 2D array that is completely safe for the DDA raycaster.
*/
static int	fill_grid_row(t_map *map, size_t row, const char *raw,
		size_t *player_found)
{
	size_t	j;
	size_t	len;
	char	c;

	len = 0;
	while (raw[len] != '\0' && raw[len] != '\n' && raw[len] != '\r')
		len++;
	j = 0;
	while (j < map->width)
	{
		c = ' ';
		if (j < len)
			c = raw[j];
		if (set_grid_cell(map, (t_vec2s){j, row}, c, player_found) != 1)
			return (0);
		j++;
	}
	map->grid[row][map->width] = '\0';
	return (1);
}

/*
** build_grid:
** Converts raw string array into a sanitized rectangular grid.
** 1. Calculates the maximum width of all lines.
** 2. Allocates a rectangular [count x width] char matrix.
** 3. Fills and normalizes every row, ensuring exactly one player spawn exists.
*/
int	build_grid(t_map *map, char **raw, size_t count)
{
	size_t	w;
	size_t	i;
	size_t	player_found;

	w = get_max_raw_width(raw, count);
	map->width = w;
	map->height = count;
	map->size.x = w;
	map->size.y = count;
	map->grid = (char **)ft_calloc(count + 1, sizeof(char *));
	if (map->grid == NULL)
		return (0);
	player_found = 0;
	i = 0;
	while (i < count)
	{
		map->grid[i] = (char *)malloc(w + 1);
		if (map->grid[i] == NULL || fill_grid_row(map, i, raw[i],
				&player_found) == 0)
			return (0);
		i++;
	}
	return (player_found == 1);
}
