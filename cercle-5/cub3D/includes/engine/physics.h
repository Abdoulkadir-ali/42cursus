/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 23:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/07 02:08:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSICS_H
# define PHYSICS_H

# include "engine.h"

# define EPSILON 0.000001f
# define MIN 0.000000001f
# define NEG_INF -1000000000000000000000000000000.0f
# define FDELTA 0.0001f
# define MAX_RAY_BOUNCES 4
# define BOUNCE_EPS 0.001f

/* dda_run.c */
void		run_dda(t_dda *d, t_map *map);
bool		peek_current_cell(t_dda *d, t_map *map);
bool		check_cell_content(t_dda *d, t_map *map);

bool		is_door_tile(char c);
bool		is_door_open_tile(char c);
float		door_open_at(t_map *map, int mx, int my);

/* dda_utils.c */
void		set_tex_idx(t_dda *d, t_map *map);
void		dda_step(t_dda *d);
void		finalize_axis_hit(t_dda *d, t_map *map);

/* dda_extra.c */
bool		push_aabb_hit(t_dda *d, t_map *map, float *t, int *side);
bool		try_portal(t_dda *d, t_map *map);
bool		try_mirror(t_dda *d, t_map *map);

/* collision_axis.c */
bool		calc_axis(float ray, float origin, t_vec2 bounds, t_vec2 *t);
bool		calc_aabb_t(t_dda *d, t_vec2 min, t_vec2 *t);

/* collision_pw.c */
t_push_wall	*get_push_wall(t_dda *d, t_map *map);
t_vec2		get_pw_min(t_push_wall *pw);

void		init_dda(t_dda *d, t_vec3 pos, t_vec2 ray);
bool		is_wall(t_world *world, t_vec3 pos);

#endif
