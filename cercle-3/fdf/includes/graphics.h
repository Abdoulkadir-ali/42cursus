/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 21:32:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "camera.h"
# include "controls.h"
# include "libft.h"
# include "map.h"
# include "vectors.h"
# include <math.h>
# include <mlx.h>

typedef struct s_data	t_data;
typedef struct s_camera	t_camera;
typedef struct s_window	t_window;
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

typedef struct s_spline_points
{
	t_point				p1;
	t_point				p2;
	t_point				p3;
	t_point				p4;
}						t_spline_points;

typedef struct s_bresenham
{
	t_vec2				p;
	t_vec2				delta;
	t_vec2				step;
	int					err;
	int					e2;
}						t_bresenham;

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
}						t_frame_data;

typedef struct s_graphics
{
	t_window			*window;
	t_camera			*camera;
	t_mouse				mouse;
	t_keys				keys;

	t_map_manager		map_manager;
	t_map				*map;

	t_map_style_config	map_config;
	t_render_config		render_config;
	t_frame_data		frame_data;

}						t_graphics;

typedef struct s_thread_data
{
	t_graphics			*g;
	int					start_y;
	int					end_y;
	int					step;
}						t_thread_data;

int						should_draw_line(t_point p1, t_point p2, t_graphics *g);
int						is_point_visible(t_point p, t_graphics *g);
void					draw_spline_segment(t_graphics *g, t_point p0,
							t_point p1, t_point p2, t_point p3, int segments);
void					draw_line(t_graphics *g, t_point p1, t_point p2);
void					draw_filled_triangle(t_graphics *g, t_point p1,
							t_point p2, t_point p3);
void					draw_wireframe_triangle(t_graphics *g, t_point p1,
							t_point p2, t_point p3);
void					draw_quad_triangles(t_graphics *g, t_point p1,
							t_point p2, t_point p3, t_point p4);
void					clear_image(t_graphics *g);
void					clear_z_buffer(t_graphics *g);
int						z_buffer_test(t_graphics *g, int x, int y, float z);
void					img_pixel_put_with_z(t_graphics *g, int x, int y,
							float z, int color);
int						is_visible(int x, int y, t_graphics *g);
void					redraw(t_events *events);
void					draw_grid(t_graphics *g);

t_window				init_window(void *mlx_ptr);
t_graphics				init_graphics(t_window *window, t_camera *camera);

#endif