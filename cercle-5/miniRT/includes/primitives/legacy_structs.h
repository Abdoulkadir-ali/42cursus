/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legacy_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 21:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 21:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEGACY_STRUCTS_H
# define LEGACY_STRUCTS_H

# include "maths.h"

/* 
** Legacy AoS structures kept ONLY for editor snapshots and UI.
** DO NOT USE in runtime rendering or physics loops.
*/

typedef struct s_sphere
{
	t_transform		transform;
	double			radius_sq;
	int				mat_id;
	bool			is_deformed;
	t_physics_body	phys;
	t_mat4			inv_transform;
}	t_sphere;

typedef struct s_plane
{
	t_transform		transform;
	t_vec3			normal;
	int				mat_id;
}	t_plane;

typedef struct s_cylinder
{
	t_transform		transform;
	t_vec3			axis;
	double			radius_sq;
	double			height;
	int				mat_id;
	t_physics_body	phys;
}	t_cylinder;

typedef struct s_cone
{
	t_transform		transform;
	t_vec3			axis;
	double			angle;
	double			height;
	int				mat_id;
}	t_cone;

typedef struct s_box
{
	t_transform		transform;
	t_vec3			extents;
	int				mat_id;
	t_physics_body	phys;
}	t_box;

typedef struct s_capsule
{
	t_transform		transform;
	t_vec3			axis;
	double			radius;
	double			half_height;
	int				mat_id;
	t_physics_body	phys;
}	t_capsule;

typedef struct s_rect
{
	t_transform		transform;
	t_vec3			v[4];
	t_vec3			normal;
	int				mat_id;
}	t_rect;

typedef struct s_pyramid
{
	t_transform		transform;
	t_vec3			up;
	double			base_size;
	double			height;
	int				mat_id;
}	t_pyramid;

typedef struct s_tri_shape
{
	t_vec3			v[3];
	t_vec3			n;
	int				mat_id;
}	t_tri_shape;

#endif
