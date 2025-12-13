/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 15:00:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

// SYSTEM REQUIREMENTS
# include "libft.h"
# include <math.h>
# include <immintrin.h>

# define FP_16 65536.0

// PROJECT REQUIREMENTS
# include "camera.h"
# include "map.h"
# include "vectors.h"
# include "window.h"

# define NUM_THREADS 4
# define DEFAULT_LOD_LEVEL 1
# define FP_SHIFT 16

typedef struct s_events	t_events;

typedef enum e_render_mode
{
	RENDER_LINES,
	RENDER_SPLINES,
	RENDER_TRIANGLES,
	RENDER_MODE_COUNT
}						t_render_mode;

typedef struct s_triangle
{
	t_point				p1;
	t_point				p2;
	t_point				p3;
}						t_triangle;

typedef struct s_quad_triangle
{
	t_point				p1;
	t_point				p2;
	t_point				p3;
	t_point				p4;
}						t_quad_triangle;

typedef struct s_spline
{
	t_point				p0;
	t_point				p1;
	t_point				p2;
	t_point				p3;
}						t_spline;

typedef struct s_triangle_interp
{
	t_triangle			triangle;
	int					y;
}						t_triangle_interp;

typedef struct s_scanline_data
{
	int					x1;
	int					x2;
	int					y;
	float				z1;
	float				z2;
	int					c1;
	int					c2;
}						t_scanline_data;

typedef struct s_scanline_color_ctx
{
	t_vec3				rgb1;
	t_vec3				rgb2;
	t_vec3				drgb;
}						t_scanline_color_ctx;

typedef struct s_scanline_draw_ctx
{
	int					x;
	int					end_x;
	t_scanline_color_ctx	color_ctx;
	float				z;
	float				dz;
	char				*pixel_addr;
	float				*z_ptr;
}						t_scanline_draw_ctx;

/* Helper struct for edge walking */
typedef struct s_edge
{
	double				x;
	double				z;
	double				r;
	double				g;
	double				b;
	double				dx;
	double				dz;
	double				dr;
	double				dg;
	double				db;
}						t_edge;

typedef struct s_rasterize_ctx
{
	t_edge				e1;
	t_edge				e2;
	int					y_start;
	int					y_end;
}						t_rasterize_ctx;

typedef struct s_bresenham
{
	t_vec2				p;
	t_vec2				delta;
	t_vec2				step;
	int					err;
	int					e2;
}						t_bresenham;

typedef struct s_bresenham_ctx
{
	int					err;
	int					e2;
	t_vec2				current;
	int					fp_r;
	int					fp_g;
	int					fp_b;
	int					fp_dr;
	int					fp_dg;
	int					fp_db;
}						t_bresenham_ctx;

typedef struct s_line_draw_state
{
	t_bresenham			b;
	int					color;
	t_vec2d				s_pos;
	t_vec2d				e_pos;
	t_vec2d				delta_total;
	double				total_dist;
	t_vec2d				current_pos;
	t_vec2d				delta_current;
	double				current_dist;
	t_camera			*c;
}						t_line_draw_state;

/* Helper to manage memory pointers for line drawing */
typedef struct s_ptr_ctx
{
	char				*img_ptr;
	float				*z_ptr;
	int					step_x;
	int					step_y;
	int					z_step_x;
	int					z_step_y;
	int					bpp;
	int					line_len;
	int					width;
	int					height;
}						t_ptr_ctx;

/* Struct for bresenham loop parameters */
typedef struct s_bresenham_params
{
	t_vec2				start;
	t_vec2				end;
	t_vec2				delta;
	t_vec2				sign;
	t_ptr_ctx			ctx;
	char				*pixel_addr;
	float				*z_addr;
	double				zr;
	double				z_step_val;
	double				r;
	double				green;
	double				b;
	double				dr;
	double				dg;
	double				db;
}						t_bresenham_params;

/* Struct for pixel drawing parameters */
typedef struct s_pixel_draw_params
{
	char				*pixel_addr;
	float				*z_addr;
	float				zr;
	int					color;
}						t_pixel_draw_params;

/* Struct for interpolation data */
typedef struct s_interp_data
{
	double				zr;
	double				z_step_val;
	double				r;
	double				green;
	double				b;
	double				dr;
	double				dg;
	double				db;
}						t_interp_data;

/* Struct for draw_line local variables */
typedef struct s_draw_line_ctx
{
	t_vec2				start_pos;
	t_vec2				end_pos;
	t_vec2				delta;
	t_vec2				sign;
	t_ptr_ctx			ctx;
	char				*pixel_addr;
	float				*z_addr;
	int					steps;
	t_interp_data		interp;
	t_bresenham_params	p;
}						t_draw_line_ctx;

typedef struct s_line_state
{
	t_vec2				start_pos;
	t_vec2				end_pos;
	t_vec2				delta;
	t_vec2				sign;
	int					err;
	int					steps;
	int					i;
	double				zr;
	double				zr_step;
	t_vec3d				start_color;
	t_vec3d				end_color;
	t_vec3d				color_delta;
	t_vec3d				current_color;
	t_vec2				current_pos;
}						t_line_state;

typedef struct s_render_config
{
	t_render_mode		render_mode;
	int					use_depth_culling;
	int					fill_triangles;
	int					lod_level;
}						t_render_config;

typedef struct s_frame_data
{
	long				last_frame_time;
	int					frame_in_progress;
	int					fps;
	int					frame_count;
	long				last_check;
}						t_frame_data;

/* Projection cache */
typedef struct s_cache
{
	t_point				*points;
	int					width;
	int					height;
	t_map				*map;
}						t_cache;

typedef struct s_fill_cache_ctx
{
	int					x;
	int					y;
	size_t				idx;
	t_point				projected;
}						t_fill_cache_ctx;

typedef struct s_clear_z_ctx
{
	int					i;
	int					total;
	float				*z_buffer;
	__m256				max_depth;
}						t_clear_z_ctx;

typedef struct s_clear_img_ctx
{
	int					i;
	int					total_bytes;
	char				*buffer;
	__m256i				zeros;
}						t_clear_img_ctx;

typedef struct s_graphics
{
	t_window			*window;
	t_camera			*camera;
	t_map				*map;
	t_render_config		render_config;
	t_frame_data		frame_data;
	t_cache				cache;

}						t_graphics;

typedef struct s_thread_data
{
	t_graphics			*g;
	int					start_y;
	int					end_y;
	int					step;
}						t_thread_data;

typedef struct s_graphics_args
{
	t_window			*window;
	t_camera			*camera;
	t_map				*map;
}						t_graphics_args;

typedef struct s_draw_line_params
{
	int					x;
	int					y;
	t_point				p1;
	int					step;
}						t_draw_line_params;

int						should_draw_line(t_point p1, t_point p2, t_graphics *g);
int						is_point_visible(t_vec3d p, t_graphics *g);
void					draw_spline_segment(t_graphics *g, t_spline spline,
							int segments);
t_point					catmull_rom_point(t_spline spline, double t);
t_point					lerp_point(t_point p1, t_point p2, double t);
void					draw_grid_section(t_graphics *g, int start_y, int end_y,
							int step);
void					draw_pixel_fast(t_graphics *g, t_pixel_draw_params p);
void					draw_pixel_fast_no_z(t_pixel_draw_params p);
void					fill_bresenham_params(t_draw_line_ctx *dlc);
void					setup_pointers(t_graphics *g, t_ptr_ctx *ctx, int sx, int sy);
void					init_interpolation(t_point start, t_point end, int steps,
							t_interp_data *data);
int						init_draw_line_ctx(t_graphics *g, t_point start,
							t_point end, t_draw_line_ctx *dlc);
void					draw_line(t_graphics *g, t_point p1, t_point p2);
void					swap_points(t_point *a, t_point *b);
void					calculate_color(t_line_draw_state *state, t_point start,
							t_point end);
void					draw_filled_triangle(t_graphics *g,
							t_triangle triangle);
void					draw_wireframe_triangle(t_graphics *g,
							t_triangle triangle);
void					setup_edge(t_edge *e, t_point top, t_point bot);
void					step_edge(t_edge *e);
void					draw_quad_triangles(t_graphics *g,
							t_quad_triangle quad);
void					rasterize_flat_bottom(t_graphics *g, t_point top,
							t_point b1, t_point b2);
void					rasterize_flat_top(t_graphics *g, t_point t1,
							t_point t2, t_point bot);
void					setup_rasterization_context(t_rasterize_ctx *ctx,
							t_point p1, t_point p2, t_point p3);
void					setup_rasterization_context_flat_top(
							t_rasterize_ctx *ctx, t_point p1, t_point p2,
							t_point p3);
void					handle_y_clipping(t_rasterize_ctx *ctx);
t_scanline_data			create_scanline_from_edges(t_rasterize_ctx *ctx,
							int y);
void					rasterize_span(t_graphics *g, t_rasterize_ctx *ctx);
t_scanline_data			interpolate_triangle_scanline(t_triangle_interp interp);
int						z_buffer_test(t_graphics *g, int x, int y, float z);
void					draw_horizontal_scanline_z(t_graphics *g,
							t_scanline_data data);
void					swap_scanline_data(t_scanline_data *data);
void					init_scanline_colors(t_scanline_data data, int len,
							t_scanline_color_ctx *ctx);
void					init_scanline_pointers(t_graphics *g, t_scanline_data data,
							char **pixel_addr, float **z_ptr);
void					clip_scanline_left(t_scanline_draw_ctx *ctx, float dz);
int						clip_scanline_right(int end_x, int win_w);
void					draw_scanline_pixel(t_graphics *g,
							t_scanline_draw_ctx *ctx);
void					draw_scanline_loop(t_graphics *g,
							t_scanline_draw_ctx *ctx);
int						is_visible(int x, int y, t_graphics *g);
void					redraw(t_events *events);
void					draw_grid(t_graphics *g);
void					draw_grid_section(t_graphics *g, int start_y, int end_y,
							int step);
void					draw_horizontal_line(t_graphics *g,
							t_draw_line_params params);
void					draw_vertical_line(t_graphics *g,
							t_draw_line_params params);
void					draw_triangle_quad(t_graphics *g, int x, int y,
							int step);
void					draw_segment(t_graphics *g,
							t_draw_line_params params, int is_horizontal);
void					draw_grid_row(t_graphics *g, int y, int step);
void					join_threads(pthread_t *threads);
void					*thread_draw_routine(void *data);
void					clear_image(t_graphics *g);
void					clear_z_buffer(t_graphics *g);
void					clear_z_buffer_simd(t_clear_z_ctx *ctx);
void					clear_z_buffer_remainder(t_clear_z_ctx *ctx);
void					clear_image_simd(t_clear_img_ctx *ctx);
void					clear_image_remainder(t_clear_img_ctx *ctx);
void					cache_projections(t_graphics *g);
t_point					get_cached_proj(t_graphics *g, int x, int y);
void					cleanup_cache(t_graphics *g);
void					init_cache(t_graphics *g);
void					fill_cache(t_graphics *g);
void					init_bresenham_ctx(t_bresenham_ctx *ctx,
							t_bresenham_params *p);
int						bresenham_step_x(t_bresenham_ctx *ctx,
							t_bresenham_params *p);
int						bresenham_step_y(t_bresenham_ctx *ctx,
							t_bresenham_params *p);
void					update_bresenham_colors(t_bresenham_ctx *ctx,
							t_bresenham_params *p);
int						get_interpolated_color(t_bresenham_ctx *ctx);
void					bresenham_fixed(t_graphics *g, t_bresenham_params p);
void					bresenham_fixed_shifted(t_graphics *g,
							t_bresenham_params p);
void					bresenham_fixed_no_z(t_bresenham_params p);
void					bresenham_fixed_no_z_shifted(t_graphics *g,
							t_bresenham_params p);

t_window				*init_window(void *mlx_ptr);
t_graphics				*init_graphics(t_graphics_args args);
void					init_render_config(t_render_config *c);
void					init_frame_data(t_frame_data *f);

typedef struct s_segment_ctx
{
	t_point             p0;
	t_point             p3;
	int                 prev_coord;
	int                 next_coord;
	int                 max_coord;
	int                 next_x;
	int                 next_y;
	t_vec2               tmp_vec;
}                       t_segment_ctx;

#endif