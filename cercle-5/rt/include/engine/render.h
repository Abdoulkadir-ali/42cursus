/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 18:49:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <pthread.h>
# include "threads.h"
# include "maths.h"
# include "physics.h"
# include "raytracing.h"
# include "scene.h"
# include "shapes.h"
# include "simd.h"

# define TILE_SIZE 32
# define MAX_BOUNCES 4

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}			t_image;

typedef struct s_tile
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
}		t_tile;

struct s_app;

typedef struct s_render_settings
{
	int		downscale;
	int		accum_cap;
	float	exposure;
	float	brightness;
	float	contrast;
	float	saturation;
	float	gamma;
	float	vignette;
	bool	progressive;
	bool	pick_buffer;
	bool	selection_outline;
	bool	downscale_on_move;
	bool	taa;
}			t_render_settings;

/*
** Per-tile job passed to the generic thread pool.
** Must stay alive until tpool_wait() returns (pool_run() guarantees this).
*/
typedef struct s_tile_job
{
	struct s_app	*app;
	t_tile			tile;
}				t_tile_job;

typedef struct s_taa_job
{
	struct s_app	*app;
	int				y0;
	int				y1;
}				t_taa_job;

typedef struct s_thread_pool
{
	t_tpool			tpool;
	int				n_threads;
	t_tile			*tiles;
	t_tile_job		*jobs;
	int				cap_tiles;
	int				n_tiles;
	struct s_app	*app;
	t_taa_job		taa_jobs[MAX_THREADS];
}					t_thread_pool;

typedef struct s_pickbuf
{
	int	*ids;
	int	w;
	int	h;
}		t_pickbuf;

/* Rendering */
void	render_frame(struct s_app *app);
int		render_screenshot(struct s_app *app, const char *path);
t_vec3	shade(const struct s_app *app, const t_ray *r, const t_hit *h,
			int depth);
const t_object	*shade_resolve_obj(const t_scene *s, int idx);
int	scene_occluded(const struct s_app *app, const t_ray *r, float max_t);
t_vec3	phong_light(const struct s_app *app, const t_hit *h, t_vec3 albedo,
			const t_light *l, const t_vec3 view);
t_vec3	emitter_lights(const struct s_app *app, const t_hit *h,
			t_vec3 albedo, t_vec3 view, int depth);
float	fresnel(float cos_t, float ior);
t_vec3	trace_ray(const struct s_app *app, const t_ray *r, int depth);
t_vec3	sky_color(t_vec3 d);
int	hit_planes(const t_object *planes, size_t n, const t_ray *r, t_hit *h);
int	planes_occluded(const t_object *planes, size_t n, const t_ray *r,
			float max_t);
t_ray	primary_ray(const t_camera *c, float x, float y, int w, int h,
			float rx, float ry);

/* Thread pool */
int		pool_init(t_thread_pool *p, struct s_app *app);
void	pool_run(t_thread_pool *p);
void	pool_destroy(t_thread_pool *p);
void	pool_rebuild_tiles(t_thread_pool *p, int w, int h);

/* Picking */
int		pick_alloc(t_pickbuf *pb, int w, int h);
void	pick_free(t_pickbuf *pb);
int		pick_at(struct s_app *app, int sx, int sy);

/* Camera update */
void	update_camera(struct s_app *app);
void	render_tile(struct s_app *app, t_tile t);

#endif
