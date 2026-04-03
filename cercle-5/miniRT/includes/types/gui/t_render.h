/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_render.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:00:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 15:43:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_GUI_RENDER_H
# define TYPES_GUI_RENDER_H

# include <pthread.h>
# include <semaphore.h>
# include "t_physics.h"
# include "t_maths.h"

# define RENDER_POOL_MAX 128
# define RENDER_W 1920
# define RENDER_H 1080

# ifndef GUI_AUTOREFRESH_PHYSICS
#  define GUI_AUTOREFRESH_PHYSICS 1
# endif

# ifndef GUI_AUTOREFRESH_SCALE
#  define GUI_AUTOREFRESH_SCALE 2
# endif

typedef struct s_render
{
	struct s_gui	*gui;
	size_t			next_tile_id;
	size_t			total_tiles;
	t_vec2i			tiles_count;
	t_transform		transform;
	double			half_width;
	double			half_height;
	double			aspect_ratio;
	size_t			step;
	t_vec2i			pos;
	int				color;
	char			*pixel_addr;
}	t_render;

typedef struct s_worker
{
	struct s_render_pool	*pool;
	size_t					idx;
}	t_worker;

typedef struct s_render_pool
{
	pthread_t		threads[RENDER_POOL_MAX];
	sem_t			start[RENDER_POOL_MAX];
	sem_t			done[RENDER_POOL_MAX];
	t_render		*render[RENDER_POOL_MAX];
	size_t			n;
	bool			shutdown;
	bool			ready;
}	t_render_pool;

typedef struct s_render_state
{
	size_t			scale;
	bool			dirty;
	bool			force_fullres;
	double			fps;
	long long		last_time;
	bool			last_dirty;
	size_t			num_cores;
	t_render_pool	pool;
}	t_render_state;

typedef struct s_tile
{
	size_t			id;
	t_vec2i			tile;
	t_vec2i			pos;
	t_vec2i			p_pos;
	size_t			bpp_step;
	size_t			row_step;
	char			*row_ptr;
	char			*pixel_ptr;
}	t_tile;

#endif
