/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:22:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/31 09:50:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_ENGINE_PHYSICS_H
# define TYPES_ENGINE_PHYSICS_H

# include "maths.h"

typedef struct s_physics_body
{
	t_vec3				pos;
	t_vec3				center;
	t_vec3				velocity;
	t_vec3				angular_velocity;
	t_vec3				accel;
	t_vec3				inv_inertia;
	double				mass;
	double				inv_mass;
	double				restitution;
	double				elasticity;
	double				friction;
	bool				is_static;
	bool				use_gravity;
}						t_physics_body;

typedef struct s_physics_state
{
	t_vec3				gravity;
	double				global_damping;
	double				time_scale;
	int					mesh_simplify_collision;
}						t_physics_state;

typedef enum e_collider_type
{
	COLLIDER_SPHERE,
	COLLIDER_BOX,
	COLLIDER_PLANE,
	COLLIDER_CAPSULE
}						t_collider_type;

typedef struct s_collider
{
	t_collider_type		type;
	union
	{
		double			radius;
		t_vec3			half_extents;
		t_vec3			normal;
		struct
		{
			t_vec3		a;
			t_vec3		b;
			double		radius;
		}				capsule;
	}					data;
}						t_collider;


#endif
