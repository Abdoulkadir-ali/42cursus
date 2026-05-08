/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 17:06:36 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 19:53:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATHFINDER_H
# define PATHFINDER_H

/* INTERNAL LIBRARIES */
# include "helpers/index.h"
# include "libft.h"
# include "map.h"
# include "maths.h"

typedef struct s_pf_search
{
	size_t		width;
	size_t		height;
	size_t		area;
	int			*prev;
	int			*queue;
	t_vec2i		start;
	t_vec2i		goal;
	size_t		start_idx;
	size_t		goal_idx;
	size_t		qi;
	size_t		qj;
}				t_pf_search;

typedef struct s_pathfinder_params
{
	const t_map	*map;
	t_vec2		start;
	t_vec2		goal;
	bool		doors_are_walls;
	t_vec2		*next_step;
}				t_pathfinder_params;

bool			pf_init_state(t_pf_search *s, const t_map *m, t_vec2i start,
					t_vec2i goal);
void			pf_step_reconstruct(t_pf_search *s, t_vec2 *next_step);
bool			pf_search(const t_map *map, t_pathfinder_params p,
					bool need_step);
bool			pf_is_tile_passable(const t_map *map, t_vec2i p,
					bool doors_are_walls);
bool			pf_has_path(const t_map *map, t_vec2 start, t_vec2 goal,
					bool doors_are_walls);
bool			pf_get_next_step(const t_map *map, t_pathfinder_params p);
bool			pf_check_closed(t_map *map);
bool			pf_validate_map(const t_map *map, t_vec2 player_pos);

#endif
