/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 22:45:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

# include "vectors.h"
# include "render.h"

// Forward declarations
typedef struct s_data	t_data;

void	draw_filled_triangle(t_data *data, t_point p1, t_point p2, t_point p3);
void	draw_wireframe_triangle(t_data *data, t_point p1, t_point p2, t_point p3);
void	draw_quad_triangles(t_data *data, t_point p1, t_point p2,
			t_point p3, t_point p4);

#endif
