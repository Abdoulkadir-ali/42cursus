/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:12 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 17:33:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct s_vec2
{
	int	x;
	int	y;
}	t_vec2;

typedef struct s_vec2d
{
	double	x;
	double	y;
}	t_vec2d;

typedef struct s_vec3
{
	int	x;
	int	y;
	int	z;
}	t_vec3;

typedef struct s_vec3d
{
	double	x;
	double	y;
	double	z;
}	t_vec3d;

typedef struct s_point
{
	t_vec3				pos;
	int					color;
}						t_point;

# define create_vec3(x, y, z) ((t_vec3){x, y, z})
# define create_vec3d(x, y, z) ((t_vec3d){x, y, z})

# define create_vec2(x, y) ((t_vec3d){x, y, z})
# define create_vec2d(x, y) ((t_vec3d){x, y, z})
#endif
