/* Physics minimal types shared with primitives */
#ifndef ENGINES_PHYSICS_TYPES_H
#define ENGINES_PHYSICS_TYPES_H

# include "helpers.h"

typedef struct s_sub_shape
{
	void			*shape;
	t_aabb			local_aabb;
	t_vec3			offset;
	t_mat4			transform;
	double			radius;
	t_phys_type		type;
} t_sub_shape;

typedef struct s_physics_body
{
	t_vec3			velocity;
	t_vec3			angular_velocity;
	t_vec3			torque;
	double			mass;
	t_mat3			inv_inertia;
	double			elasticity;
	double			friction;
	bool			is_static;
	bool			is_compound;
	t_vec3			center;
	void			*owner;
	t_transform		*transform;
	/* Note: sub_shapes count is implementation detail; keep small fixed array */
	/* Keep size small to avoid heavy header dependencies */
	/* Full physics implementation defines a richer body */
} t_physics_body;

#endif
