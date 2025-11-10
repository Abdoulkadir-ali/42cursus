/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spline.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 20:13:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLINE_H
# define SPLINE_H

# include "vectors.h"
# include "render.h"

// Forward declarations
typedef struct s_data	t_data;

/* ========== SPLINE RENDERING ========== */
// Draw a smooth Catmull-Rom spline between two points
// p0: previous point (for curve continuity)
// p1: start point
// p2: end point
// p3: next point (for curve continuity)
// segments: number of line segments to subdivide the curve into
void	draw_spline_segment(t_data *data, t_point p0, t_point p1,
			t_point p2, t_point p3, int segments);

/* ========== SPLINE UTILITIES ========== */
// Catmull-Rom spline interpolation for a single coordinate
// Returns the interpolated value at parameter t (0.0 to 1.0)
// p0, p1, p2, p3: four control points
double	catmull_rom_interpolate(double p0, double p1, double p2,
			double p3, double t);

// Linear interpolation between two points
t_point	lerp_point(t_point p1, t_point p2, double t);

#endif
