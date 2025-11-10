/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spline.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 22:37:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLINE_H
# define SPLINE_H

# include "vectors.h"
# include "render.h"

typedef struct s_data	t_data;

void	draw_spline_segment(t_data *data, t_point p0, t_point p1,
			t_point p2, t_point p3, int segments);
double	catmull_rom_interpolate(double p0, double p1, double p2,
			double p3, double t);
t_point	lerp_point(t_point p1, t_point p2, double t);

#endif
