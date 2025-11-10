/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:56 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 22:37:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "map.h"
# include "controls.h"

typedef struct s_data	t_data;
t_vec3d					apply_rotation(t_vec3d v, t_rotation rot);
t_vec3d					apply_rotation_centered(t_vec3d v, t_rotation rot,
							t_vec3d c);

static inline t_vec3d	rotate_x(t_vec3d v, double angle)
{
	t_vec3d	rotated;

	rotated.x = v.x;
	rotated.y = v.y * cos(angle) - v.z * sin(angle);
	rotated.z = v.y * sin(angle) + v.z * cos(angle);
	return (rotated);
}

static inline t_vec3d	rotate_y(t_vec3d v, double angle)
{
	t_vec3d	rotated;

	rotated.x = v.x * cos(angle) + v.z * sin(angle);
	rotated.y = v.y;
	rotated.z = -v.x * sin(angle) + v.z * cos(angle);
	return (rotated);
}

static inline t_vec3d	rotate_z(t_vec3d v, double angle)
{
	t_vec3d	rotated;

	rotated.x = v.x * cos(angle) - v.y * sin(angle);
	rotated.y = v.x * sin(angle) + v.y * cos(angle);
	rotated.z = v.z;
	return (rotated);
}

t_point	project_isometric(t_point p3d, t_camera cam);

typedef struct s_bresenham
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
	int	x;
	int	y;
}	t_bresenham;


// Visibility and screening helpers
int		is_point_visible(t_point p3d, t_data *data);
int		is_on_screen(int x, int y, t_data *data);
int		should_draw_line(t_point p1, t_point p2, t_data *data);

// Image manipulation
void	clear_image(t_data *data);
void	clear_z_buffer(t_data *data);
int		z_buffer_test(t_data *data, int x, int y, float z);

// Line drawing with color interpolation
void	draw_line(t_data *data, t_point start, t_point end);

// Draw entire grid
void	draw_grid(t_data *data);

// Redraw entire scene
void	redraw(t_data *data);

/* ========== VISUAL STYLE FUNCTIONS ========== */
extern const char	*g_style_names[];
int		get_styled_color(int base_z, int min_z, int max_z, int style);
int		get_background_color(int style);
void	cycle_visual_style(t_data *data);
void	apply_style_to_map(t_data *data);

#endif
