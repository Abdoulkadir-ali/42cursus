/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_render.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:00:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 23:33:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_GUI_RENDER_H
# define TYPES_GUI_RENDER_H

# include <stdatomic.h>
# include <stdint.h>
# include <pthread.h>
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
** t_render — per-tile worker context, allocated on the stack each frame.
*/
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
	TASK_INTERP,
	TASK_TAA,
	TASK_UPSCALE,
	TASK_BLUR
}	t_pool_task;

typedef struct s_render_task
{
	struct s_gui		*gui;
	t_render			*render;
	t_pool_task			type;
	_Atomic size_t		worker_idx;
}	t_render_task;

/*
** t_optimizations — owns ALL state for post-render optimizations.
** Lives in t_gui as `gui->opts`. Never touches t_render_state.
*/
typedef struct s_optimizations
{
	bool		adaptive_scale;
	bool		auto_fullres;
	bool		reprojection;
	bool		temporal_blend;
	float		*depth_buf;
	uint32_t	*prev_color;
	float		*prev_depth;
	uint32_t	*reproj_buf;
	size_t		*reproj_tag;
	size_t		reproj_gen;
	t_transform	cur_cam;
	double		cur_half_w;
	double		cur_half_h;
	t_transform	prev_cam;
	double		prev_half_w;
	double		prev_half_h;
	t_vec2s		prev_render_size;
	bool		prev_valid;
	bool		frame_interp;
	uint32_t	*interp_buf;
	t_transform	interp_cam;
	t_vec2		interp_half;
	float		interp_alpha;
	bool		taa;
	uint32_t	*taa_buf;
	size_t		taa_frame;
	double		taa_jitter_x;
	double		taa_jitter_y;	uint32_t	*bloom_buf;
	uint32_t	*bloom_tmp;
}				t_optimizations;

/*
** t_bake_job — self-contained context for one async background bake.
** Allocated on heap by bake_job_start; freed by bake_job_cancel/poll.
*/
typedef struct s_bake_job
{
	pthread_t				thread;
	volatile bool			running;
	volatile bool			cancel;
	volatile bool			done;
	uint32_t				*accum_r;
	uint32_t				*accum_g;
	uint32_t				*accum_b;
	uint32_t				*pixel_scratch;
	int						width;
	int						height;
	double					fov;
	size_t					frame;
	size_t					target;
	char					out_path[256];
	struct s_gui			*gui;
	t_transform				camera;
	t_raytracer_settings	settings;
	long long				done_ts;
	struct s_scene			*scene_snap;
}	t_bake_job;

/*
** t_render_state — frame loop bookkeeping only.
** All optimization state lives in t_optimizations (gui->opts).
*/
typedef struct s_render_state
{
	size_t				scale;
	bool				dirty;
	bool				force_fullres;
	double				fps;
	long long			last_time;
	double				render_fps;
	long long			render_last_time;
	long long			scale_last_change;
	bool				last_dirty;
	int					bvh_needs_rebuild;
	int					scene_swap_pending;
	struct s_scene		*next_scene;
	struct s_map_entry	*next_entry;
	int					back_idx;
	volatile bool		abort_render;
	t_bake_job			*bake_job;
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
