/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_render.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:00:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 21:06:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_GUI_RENDER_H
# define TYPES_GUI_RENDER_H

# include <pthread.h>
# include <semaphore.h>
# include <stdatomic.h>
# include <stdint.h>
# include "t_physics.h"
# include "t_raytracing.h"
# include "t_maths.h"

# define RENDER_POOL_MAX 128
# define RENDER_W 2560
# define RENDER_H 1440

# ifndef GUI_AUTOREFRESH_PHYSICS
#  define GUI_AUTOREFRESH_PHYSICS 1
# endif

# ifndef GUI_AUTOREFRESH_SCALE
#  define GUI_AUTOREFRESH_SCALE 2
# endif
/*
** Runtime optimization settings — flip any field at runtime to
** enable / disable an optimization without recompiling.
** Add new fields here as new techniques are implemented.
*/
typedef struct s_optimization_settings
{
	bool	adaptive_scale;   /* auto-adjust render.scale to hit target FPS  */
	bool	reprojection;     /* camera reprojection (combo A)               */
	bool	temporal_blend;   /* legacy temporal blend (disabled by default) */
	bool	frame_interp;     /* frame interpolation  (combo B — planned)    */
	bool	taa;              /* temporal anti-aliasing (combo D — planned)  */
}	t_optimization_settings;
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

typedef enum e_pool_task
{
	TASK_RENDER,
	TASK_SCATTER,
	TASK_APPLY,
	TASK_UPSCALE
}	t_pool_task;

typedef struct s_render_task
{
	struct s_gui		*gui;
	t_render		*render;
	t_pool_task		type;
	_Atomic size_t	worker_idx;
}	t_render_task;

typedef struct s_render_state
{
	size_t					scale;
	bool					dirty;
	bool					force_fullres;
	double					fps;
	long long				last_time;
	double					render_fps;
	long long				render_last_time;
	long long				scale_last_change;
	bool					last_dirty;
	int						*prev_buf;
	float					*depth_buf;
	float					*prev_depth;
	uint32_t				*reproj_buf;
	size_t					*reproj_tag;
	size_t					reproj_gen;
	t_transform				cur_cam;
	double					cur_half_w;
	double					cur_half_h;
	t_transform				prev_cam;
	double					prev_half_w;
	double					prev_half_h;
	size_t					prev_step;
	bool					prev_valid;
	t_vec2i					prev_render_size;
	t_optimization_settings	opts;
	/* scene swap — render thread drains this at frame start */
	volatile int			scene_swap_pending;
	struct s_scene			*next_scene;
	struct s_map_entry		*next_entry;
	/* deferred display resize (main→render SPSC) */
	volatile int			disp_resize_pending;
	t_vec2i					pending_disp_size;
	void					*pending_disp_imgs[3];
	char					*pending_disp_addrs[3];
	int						pending_disp_line_len;
	int						pending_disp_bpp;
	int						pending_disp_endian;
	/* destroy signal (render→main SPSC) */	/* disp_resize_done: set after buffer swap, cleared after flip+destroy signal */
	volatile int				disp_resize_done;	volatile int			disp_destroy_pending;
	void					*old_disp_imgs[3];
	/* triple buffer — back_idx is render-thread-private */
	int						back_idx;
	/* lock-free blit handle read by main thread */
	_Atomic void			*blit_img;
	/* render thread */
	pthread_t				render_thread;
	pthread_mutex_t			job_mutex;
	pthread_cond_t			job_cond;
	volatile int			job_requested;
	int						job_stop;
	volatile int			abort_render;
	volatile int			bvh_needs_rebuild;
	_Atomic int				front_idx;
	t_transform				snap_transform;
	double					snap_fov;
	size_t					snap_scale;
	double					snap_delta;
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
