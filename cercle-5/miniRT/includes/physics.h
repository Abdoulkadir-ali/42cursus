/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:26:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:26:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSICS_H
# define PHYSICS_H

# include "core.h"
# include "maths.h"



/* Constants */
# define MAX_CONTACTS 1024
# define SOLVER_ITERATIONS 8
# define BAUMGARTE 0.2
# define SLOP 0.01


/* Forward declarations to avoid circular includes. Concrete types
 * are included in implementation files when needed. */

/* Physics types - separation of concerns: per-object body and global state */
typedef struct s_physics_body
{
	t_vec3  velocity;
	t_vec3	angular_velocity;
	t_vec3	torque;
	bool    is_static;
	double  mass;
	double  elasticity; /* 0..1 bounce factor */
	double  friction;   /* 0..1 friction coefficient */
}               t_physics_body;

typedef struct s_physics_state
{
	t_vec3          gravity;
	double          global_damping; /* velocity damping */
	double          time_scale;
	int				mesh_simplify_collision; /* 0: precise, 1: capsule approx */
}               t_physics_state;

/* Physics update loop */
void	update_physics(t_scene *scene, double dt);
void	resolve_collisions(t_scene *scene, struct s_sphere *sp);

/* Physics debug */
void	phys_debug_spheres(t_scene *scene);

/* Gravity simulation */
void	apply_gravity(t_scene *scene, float delta_time);

/* Ray refraction */
t_vec3	refract_ray(t_vec3 incident, t_vec3 normal, float n1, float n2);

/* Collision detection helpers */
bool    detect_sphere_plane_collision(const struct s_sphere *s,
				const t_plane *pl, t_vec3 *out_normal, double *out_penetration);
bool    detect_sphere_sphere_collision(const struct s_sphere *a,
				const struct s_sphere *b, t_vec3 *out_normal, double *out_penetration);

bool    detect_sphere_mesh_collision(const struct s_sphere *s, struct s_mesh *m,
				t_vec3 *out_normal, double *out_penetration);

/* Generic collider API */
typedef enum e_collider_type
{
	COLLIDER_SPHERE,
	COLLIDER_BOX,
	COLLIDER_PLANE,
	COLLIDER_CAPSULE
}               t_collider_type;

typedef struct s_collider
{
	t_collider_type    type;
	union {
		double      radius;     /* for sphere */
		t_vec3      half_extents;/* for box */
		t_vec3      normal;     /* for plane (local) */
		struct {
			t_vec3 a;       /* start point (local) */
			t_vec3 b;       /* end point (local) */
			double radius;
		} capsule;
	} data;
}               t_collider;

/* Dispatch between collider types; transforms are the world transforms of the bodies. */
bool    detect_collider_collision(const t_collider *a, const t_transform *ta,
				const t_collider *b, const t_transform *tb,
				t_vec3 *out_normal, double *out_penetration);

/* Interaction */
void	physics_shoot_ray(t_scene *scene, t_ray ray, double impulse);



/* Internal Contact Structure */
typedef struct s_contact
{
    t_physics_body  *a;
    t_transform     *ta;
    t_physics_body  *b;
    t_transform     *tb;
    t_vec3          normal;     /* From A to B */
    double          penetration;
    double          restitution;
    double          friction;
    t_vec3          contact_point; /* World space */
    t_vec3          ra; /* Vector from Center A to Contact Point */
    t_vec3          rb; /* Vector from Center B to Contact Point */
}               t_contact;

/* Global State Access */
t_physics_state *get_physics_state(void);

/* Integration */
void    integrate_bodies(t_scene *scene, double dt);

/* Collision Detection */
int     generate_contacts(t_scene *scene, t_contact *contacts, int max_c);
bool    collide_sphere_sphere(t_sphere *a, t_sphere *b, t_contact *c);
bool    collide_sphere_plane(t_sphere *s, t_plane *p, t_contact *c);
bool    collide_sphere_mesh(t_sphere *s, t_mesh *m, t_contact *c);

/* Solver */
void    solve_velocities(t_contact *contacts, int count);
void    solve_positions(t_contact *contacts, int count);

/* Utils */
double  clamp_d(double v, double lo, double hi);


#endif
