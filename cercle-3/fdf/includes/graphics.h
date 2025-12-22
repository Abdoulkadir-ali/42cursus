/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 18:00:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

// SYSTEM REQUIREMENTS
# include "libft.h"
# include <immintrin.h>
# include <math.h>

// PROJECT REQUIREMENTS
# include "geometry.h"
# include "render.h"
# include "window.h"

# define NUM_THREADS 8
# define DEFAULT_LOD_LEVEL 1.0
# define FP_SHIFT 16
# define FP_16 65536.0
# define DRAW_LIMIT -1000000.0
# define DEFAULT_TARGET_POINTS 1000000UL
# define MAX_DETAIL_LEVEL 7
# define MIN_DETAIL_LEVEL -5

# define B_USE_Z 1
# define B_COLOR_SHIFT 2

typedef struct s_events		t_events;

typedef enum e_render_mode
{
	RENDER_LINES,
	RENDER_TRIANGLES,
	RENDER_MODE_COUNT
}							t_render_mode;
typedef struct s_clipping_bounds
{
	int						min_x;
	int						max_x;
}							t_clipping_bounds;

typedef struct s_triangle
{
	t_point					p1;
	t_point					p2;
	t_point					p3;
}							t_triangle;

typedef struct s_quad_triangle
{
	t_point					p1;
	t_point					p2;
	t_point					p3;
	t_point					p4;
}							t_quad_triangle;

typedef struct s_triangle_interp
{
	t_triangle				triangle;
	int						y;
}							t_triangle_interp;

typedef struct s_scanline_data
{
	int						x1;
	int						x2;
	int						y;
	float					z1;
	float					z2;
	int						c1;
	int						c2;
}							t_scanline_data;

typedef struct s_scanline_color_ctx
{
	t_vec3					rgb1;
	t_vec3					rgb2;
	t_vec3					drgb;
}							t_scanline_color_ctx;

typedef struct s_scanline_draw_ctx
{
	int						x;
	int						end_x;
	t_scanline_color_ctx	color_ctx;
	float					z;
	float					dz;
	char					*pixel_addr;
	float					*z_ptr;
}							t_scanline_draw_ctx;

/* Helper struct for edge walking */
typedef struct s_edge
{
	double					x;
	double					z;
	double					r;
	double					g;
	double					b;
	double					dx;
	double					dz;
	double					dr;
	double					dg;
	double					db;
}							t_edge;

typedef struct s_rasterize_ctx
{
	t_edge					e1;
	t_edge					e2;
	int						y_start;
	int						y_end;
}							t_rasterize_ctx;

typedef struct s_bresenham
{
	t_vec2					p;
	t_vec2					delta;
	t_vec2					step;
	int						err;
	int						e2;
}							t_bresenham;

typedef struct s_bresenham_ctx
{
	int						err;
	int						e2;
	t_vec2					current;
	int						fp_r;
	int						fp_g;
	int						fp_b;
	int						fp_dr;
	int						fp_dg;
	int						fp_db;
}							t_bresenham_ctx;

typedef struct s_line_draw_state
{
	t_bresenham				b;
	int						color;
	t_vec2d					s_pos;
	t_vec2d					e_pos;
	t_vec2d					delta_total;
	double					total_dist;
	t_vec2d					current_pos;
	t_vec2d					delta_current;
	double					current_dist;
	t_camera				*c;
}							t_line_draw_state;

/* Helper to manage memory pointers for line drawing */
typedef struct s_ptr_ctx
{
	char					*img_ptr;
	float					*z_ptr;
	int						step_x;
	int						step_y;
	int						z_step_x;
	int						z_step_y;
	size_t					bpp;
	size_t					line_len;
	size_t					width;
	size_t					height;
}							t_ptr_ctx;

/* Struct for bresenham loop parameters */
typedef struct s_bresenham_params
{
	t_vec2					start;
	t_vec2					end;
	t_vec2					delta;
	t_vec2					sign;
	t_ptr_ctx				ctx;
	char					*pixel_addr;
	float					*z_addr;
	double					zr;
	double					z_step_val;
	double					r;
	double					green;
	double					b;
	double					dr;
	double					dg;
	double					db;
	size_t					min_x;
	size_t					max_x;
}							t_bresenham_params;

/* Struct for pixel drawing parameters */
typedef struct s_pixel_draw_params
{
	char					*pixel_addr;
	float					*z_addr;
	float					zr;
	unsigned int			color;
}							t_pixel_draw_params;

/* Struct for interpolation data */
typedef struct s_interp_data
{
	double					zr;
	double					z_step_val;
	double					r;
	double					green;
	double					b;
	double					dr;
	double					dg;
	double					db;
}							t_interp_data;

/* Struct for draw_line local variables */
typedef struct s_draw_line_ctx
{
	t_vec2					start_pos;
	t_vec2					end_pos;
	t_vec2					delta;
	t_vec2					sign;
	t_ptr_ctx				ctx;
	char					*pixel_addr;
	float					*z_addr;
	int						steps;
	t_interp_data			interp;
	t_bresenham_params		p;
}							t_draw_line_ctx;

typedef struct s_line_state
{
	t_vec2					start_pos;
	t_vec2					end_pos;
	t_vec2					delta;
	t_vec2					sign;
	int						err;
	int						steps;
	int						i;
	double					zr;
	double					zr_step;
	t_vec3d					start_color;
	t_vec3d					end_color;
	t_vec3d					color_delta;
	t_vec3d					current_color;
	t_vec2					current_pos;
}							t_line_state;

typedef struct s_render_config
{
	t_render_mode			render_mode;
	int						use_depth_culling;
	int						filled;
	float					lod_value;
	int						use_tesselation;
	int						tesselation_level;
	size_t					target_tesselation_points;
	int						max_tesselation_level;
	int						use_horizon_culling;
	int						use_adaptive_logic;
	int						detail_level;
	t_vec2					last_tess_min;
	t_vec2					last_tess_max;
	int						last_tess_level;
}							t_render_config;

typedef struct s_frame_data
{
	long					last_frame_time;
	int						frame_in_progress;
	int						fps;
	int						frame_count;
	long					last_check;
}							t_frame_data;

/* Camera state for cache invalidation */
typedef struct s_camera_state
{
	t_vec3d					position;
	t_vec3d					rotation;
	double					scale;
	double					z_scale_val;
	double					alpha;
}							t_camera_state;

/* Projection cache */
typedef struct s_cache
{
	t_point					*points;
	size_t					width;
	size_t					height;
	t_map					*map;
	int						cache_valid;
	t_camera_state			cam_state;
}							t_cache;

typedef struct s_fill_cache_ctx
{
	size_t					x;
	size_t					y;
	size_t					idx;
	t_point					projected;
}							t_fill_cache_ctx;

typedef struct s_clear_z_ctx
{
	size_t					i;
	size_t					total;
	float					*z_buffer;
	__m256					max_depth;
}							t_clear_z_ctx;

typedef struct s_clear_img_ctx
{
	size_t					i;
	size_t					total_bytes;
	char					*buffer;
	__m256i					zeros;
}							t_clear_img_ctx;

typedef struct s_graphics
{
	t_window				*window;
	t_camera				*camera;
	t_map					*map;
	t_map					*base_map;
	t_map					*tesselated_map;
	t_map					*lod_maps[8];
	t_render_config			render_config;
	t_frame_data			frame_data;
	t_cache					cache;
	int						*horizon_buffer;
	int						dirty;
}							t_graphics;

typedef struct s_thread_data
{
	t_graphics				*g;
	size_t					start_y;
	size_t					end_y;
	float					lod_value;
	size_t					min_visible_x;
	size_t					max_visible_x;
}							t_thread_data;

typedef struct s_graphics_args
{
	t_window				*window;
	t_camera				*camera;
	t_map					*map;
}							t_graphics_args;

typedef struct s_draw_line_params
{
	int						x;
	int						y;
	t_point					p1;
	int						step;
}							t_draw_line_params;

/* Perspective Helper */
/* Moved to renderer module */

t_point						lerp_point(t_point p1, t_point p2, double t);

static inline void	draw_pixel_fast_no_z(t_pixel_draw_params p)
{
	*(unsigned int *)p.pixel_addr = p.color;
}

static inline void	draw_pixel_fast(t_graphics *g, t_pixel_draw_params p)
{
	if (!g->render_config.use_depth_culling || !p.z_addr || p.zr < *p.z_addr)
	{
		if (g->render_config.use_depth_culling && p.z_addr)
			*p.z_addr = p.zr;
		*(unsigned int *)p.pixel_addr = p.color;
	}
}
void						fill_bresenham_params(t_draw_line_ctx *dlc);
void						setup_pointers(t_graphics *g, t_ptr_ctx *ctx,
								int sx, int sy);
void						init_interpolation(t_point start, t_point end,
								int steps, t_interp_data *data);
int							init_draw_line_ctx(t_graphics *g, t_point start,
								t_point end, t_draw_line_ctx *dlc);
void						draw_pixel(t_graphics *graphics, t_point point);
void						draw_line(t_graphics *graphics, t_point start,
								t_point end);
void						draw_line_clipped(t_graphics *g, t_point start,
								t_point end, t_clipping_bounds bounds);
void						draw_triangle(t_graphics *g, t_point p1, t_point p2,
								t_point p3);
void						swap_points(t_point *a, t_point *b);
void						calculate_color(t_line_draw_state *state,
								t_point start, t_point end);
void						draw_filled_triangle(t_graphics *g,
								t_triangle triangle);
void						draw_wireframe_triangle(t_graphics *g,
								t_triangle triangle);
void						setup_edge(t_edge *e, t_point top, t_point bot);
void						step_edge(t_edge *e);
void						draw_quad_triangles(t_graphics *g,
								t_quad_triangle quad);
void						rasterize_flat_bottom(t_graphics *g, t_point top,
								t_point b1, t_point b2);
void						rasterize_flat_top(t_graphics *g, t_point t1,
								t_point t2, t_point bot);
void						setup_rasterization_context(t_rasterize_ctx *ctx,
								t_point p1, t_point p2, t_point p3);
void						setup_rasterization_context_flat_top(
								t_rasterize_ctx *ctx, t_point p1, t_point p2,
								t_point p3);
void						handle_y_clipping(t_rasterize_ctx *ctx);
t_scanline_data				create_scanline_from_edges(t_rasterize_ctx *ctx,
								int y);
void						rasterize_span(t_graphics *g, t_rasterize_ctx *ctx);
t_scanline_data				interpolate_triangle_scanline(
								t_triangle_interp interp);
int							z_buffer_test(t_graphics *g, int x, int y, float z);
void						draw_horizontal_scanline_z(t_graphics *g,
								t_scanline_data data);
void						swap_scanline_data(t_scanline_data *data);
void						init_scanline_colors(t_scanline_data data, int len,
								t_scanline_color_ctx *ctx);
void						init_scanline_pointers(t_graphics *g,
								t_scanline_data data, char **pixel_addr,
								float **z_ptr);
void						clip_scanline_left(t_scanline_draw_ctx *ctx,
								float dz);
int							clip_scanline_right(int end_x, size_t win_w);
void						draw_scanline_pixel(t_graphics *g,
								t_scanline_draw_ctx *ctx);
void						draw_scanline_loop(t_graphics *g,
								t_scanline_draw_ctx *ctx);
int							is_on_screen(int x, int y, t_graphics *g);
int							is_visible(int x, int y, t_graphics *g);
void						redraw(t_events *events);
void						draw_grid(t_graphics *g);
void						draw_grid_section(t_graphics *g, int start_y,
								int end_y, float lod_value);
void						draw_horizontal_line(t_graphics *g,
								t_draw_line_params params);
void						draw_vertical_line(t_graphics *g,
								t_draw_line_params params);
void						draw_triangle_quad(t_graphics *g, int x, int y,
								int step);
void						draw_segment(t_graphics *g,
								t_draw_line_params params, int is_horizontal);
void						draw_grid_row(t_graphics *g, int y,
								float lod_value);
void						join_threads(pthread_t *threads);
void						*thread_draw_routine(void *data);
void						clear_image(t_graphics *g);
void						clear_z_buffer(t_graphics *g);
void						clear_z_buffer_simd(t_clear_z_ctx *ctx);
void						clear_z_buffer_remainder(t_clear_z_ctx *ctx);
void						clear_image_simd(t_clear_img_ctx *ctx);
void						clear_image_remainder(t_clear_img_ctx *ctx);
void						clear_frame_buffers(t_graphics *g);
void						cache_projections(t_graphics *g);
t_point						get_cached_proj(t_graphics *g, int x, int y);
void						cleanup_cache(t_graphics *g);
void						init_cache(t_graphics *g);
void						fill_cache(t_graphics *g);

/* Inline fast-path cache access - no bounds checking for hot loops */
static inline t_point	get_cached_proj_fast(t_graphics *g, size_t idx)
{
	return (g->cache.points[idx]);
}

static inline t_point	get_cached_proj_unsafe(t_graphics *g, int x, int y)
{
	return (g->cache.points[y * g->cache.width + x]);
}

void						bresenham(t_graphics *g, t_bresenham_params *p,
								int flags);
void						bresenham_raycast(t_graphics *g,
								t_bresenham_params *p, int flags);

void						init_bresenham_ctx(t_bresenham_ctx *ctx,
								t_bresenham_params *p);
void						update_bresenham_colors(t_bresenham_ctx *ctx,
								t_bresenham_params *p);
int							bresenham_iter(t_bresenham_ctx *ctx,
								t_bresenham_params *p);

t_window					*init_window(void *mlx_ptr);
t_graphics					*init_graphics(t_graphics_args args);
void						init_render_config(t_render_config *c);
void						init_frame_data(t_frame_data *f);

typedef struct s_segment_ctx
{
	t_point					p0;
	t_point					p3;
	int						prev_coord;
	size_t					next_coord;
	int						max_coord;
	size_t					next_x;
	size_t					next_y;
	t_vec2					tmp_vec;
}							t_segment_ctx;

#endif