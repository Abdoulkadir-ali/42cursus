/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_physics.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:22:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 20:48:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_ENGINE_PHYSICS_H
# define TYPES_ENGINE_PHYSICS_H

# include "maths.h"
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>

# define MAX_CONTACTS 32768
# define PHYS_NUM_TYPES 7

struct s_scene;

typedef t_vec3 (*t_support_fn)(const void *shape, t_vec3 dir);

typedef struct s_collision
{
	t_vec3	normal;
	double	pen;
	double	min_dist_sq;
	bool	hit;
	t_vec3	best_normal;
	double	best_pen;
}	t_collision;

typedef struct s_gjk_shape
{
	const void		*data;
	t_support_fn	support;
	t_vec3			center;
}	t_gjk_shape;

typedef struct s_physics_body
{
	t_vec3				pos;
	t_vec3				center;
	t_vec3				velocity;
	t_vec3				angular_velocity;
	t_vec3				accel;
	t_vec3				inv_inertia;
	t_vec3				prev_velocity;
	double				squash;
	double				mass;
	double				inv_mass;
	double				restitution;
	double				elasticity;
	double				friction;
	bool				is_static;
	bool				use_gravity;
}						t_physics_body;

typedef struct s_contact
{
	t_physics_body		*a;
	t_transform			*ta;
	t_physics_body		*b;
	t_transform			*tb;
	t_vec3				normal;
	double				penetration;
	double				restitution;
	double				friction;
	t_vec3				contact_point;
	t_vec3				ra;
	t_vec3				rb;
	double				lambda_pos;
}						t_contact;

typedef struct s_simplex
{
	t_vec3	pts[4];
	t_vec3	a_pts[4];
	t_vec3	b_pts[4];
	size_t	n;
}	t_simplex;

typedef struct s_physics_settings
{
	double				slop;
	double				baumgarte;
	size_t				solver_iterations;
	double				restitution_slop;
	t_vec3				gravity;
	double				global_damping;
	double				time_scale;
	bool				mesh_simplify_collision;
	double				big_g;
}						t_physics_settings;

typedef struct s_gen_job
{
	struct s_physic_engine	*engine;
	struct s_scene			*scene;
	struct s_contact		*out;
	size_t					max_c;
	size_t					count;
	size_t					type;
}	t_gen_job;

typedef struct s_contact_query
{
	struct s_physic_engine	*engine;
	t_contact			*contacts;
	size_t				count;
	size_t				max;
}						t_contact_query;

typedef struct s_col_pair
{
	t_gjk_shape		*sa;
	t_gjk_shape		*sb;
	t_physics_body	*ba;
	t_physics_body	*bb;
	t_transform		*ta;
	t_transform		*tb;
}						t_col_pair;

typedef struct s_worker_info
{
	struct s_physic_engine	*engine;
	size_t					idx;
}						t_worker_info;

typedef struct s_phys_pool
{
	pthread_t			threads[PHYS_NUM_TYPES];
	t_gen_job			jobs[PHYS_NUM_TYPES];
	t_worker_info		worker_info[PHYS_NUM_TYPES];
	size_t				indices[PHYS_NUM_TYPES];
	sem_t				start[PHYS_NUM_TYPES];
	sem_t				done[PHYS_NUM_TYPES];
	bool				shutdown;
	bool				initialized;
}						t_phys_pool;

typedef struct s_physic_engine
{
	struct s_scene		*scene;
	t_physics_settings	settings;
	t_phys_pool			pool;
}						t_physic_engine;

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

typedef struct s_epa_face
{
	size_t	idx[3];
	t_vec3	normal;
	double	dist;
}	t_epa_face;

# define EPA_MAX_ITER   64
# define EPA_MAX_FACES  128
# define EPA_MAX_VERTS  64
# define EPA_TOL        1e-5
/* Collision margin added to zero-thickness shapes (rect/tri) so GJK/EPA
   has a non-degenerate slab to work with. Value matches Bullet's default. */
# define PHYS_SKIN      0.005

typedef struct s_epa_poly
{
	t_vec3		pts[EPA_MAX_VERTS];
	t_vec3		a_pts[EPA_MAX_VERTS];
	t_vec3		b_pts[EPA_MAX_VERTS];
	size_t		n_verts;
	t_epa_face	faces[EPA_MAX_FACES];
	size_t		n_faces;
}	t_epa_poly;

typedef struct s_edge
{
	size_t	a;
	size_t	b;
}	t_edge;

typedef struct s_epa_res
{
	t_vec3	normal;
	double	depth;
	t_vec3	contact_a;
	t_vec3	contact_b;
}	t_epa_res;

typedef struct s_ref_data
{
	t_gjk_shape		shape;
	t_physics_body	*body;
	t_transform		*xform;
}					t_ref_data;

typedef struct s_bvh_phys_ctx
{
	t_contact_query	*qu;
	t_gjk_shape		*sa;
	t_physics_body	*ba;
	t_transform		*ta;
	uint8_t			skip_type;
}					t_bvh_phys_ctx;

typedef struct s_seg_calc
{
	t_vec2	st;
	t_vec3	d1;
	t_vec3	d2;
	t_vec3	r;
	double	a;
	double	e;
	double	f;
}	t_seg_calc;

#endif
