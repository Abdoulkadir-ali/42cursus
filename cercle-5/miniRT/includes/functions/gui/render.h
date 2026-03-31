/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:00:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/31 09:50:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_RENDER_H
# define GUI_RENDER_H


# include "core.h"
# include "physics.h"
# include "maths.h"

typedef struct s_render				t_render;

# define RENDER_POOL_MAX 128
# define RENDER_W 2560
# define RENDER_H 1440

# ifndef GUI_AUTOREFRESH_PHYSICS
#  define GUI_AUTOREFRESH_PHYSICS 1
# endif

# ifndef GUI_AUTOREFRESH_SCALE
#  define GUI_AUTOREFRESH_SCALE 2
# endif

typedef struct s_render
{
	struct s_gui	*gui;
	int				next_tile_id;
	int				total_tiles;
	int				tiles_x;
	t_transform		transform;
	double			half_width;
	double			half_height;
	double			aspect_ratio;
	int				step;
	t_vec2i			pos;
	int				color;
	char			*pixel_addr;
}	t_render;

typedef struct s_worker
{
	struct s_render_pool	*pool;
	int						idx;
}	t_worker;

typedef struct s_render_pool
{
	pthread_t		threads[RENDER_POOL_MAX];
	sem_t			start[RENDER_POOL_MAX];
	sem_t			done[RENDER_POOL_MAX];
	t_render		*render[RENDER_POOL_MAX];
	int				n;
	bool			shutdown;
	bool			ready;
}	t_render_pool;

typedef struct s_render_state
{
	int				scale;
	bool			dirty;
	bool			force_fullres;
	double			fps;
	long long		last_time;
	bool			last_dirty;
	int				num_cores;
	t_render_pool	pool;
}	t_render_state;

typedef struct s_tile_vars
{
	int				id;
	int				tx;
	int				ty;
	t_vec2i			pos;
	t_vec2i			p_pos;
	int				bpp_step;
	int				row_step;
	char			*row_ptr;
	char			*pixel_ptr;
}	t_tile_vars;

/* Prototypes */
void			gui_render(struct s_gui *gui);
unsigned int	color_blend(unsigned int dst, int src, float alpha);
void			render_tiles(t_render *render);
bool			update_hover(struct s_gui *gui, t_render *render);
void			process_pixel(t_render *render, t_vec2i pos, char *pixel_addr);
void			make_camera_ray(t_render *render, double x, double y, t_ray *ray);
void			upscale_image(struct s_gui *gui);
void			fullres_toggle(struct s_gui *gui);

#endif
