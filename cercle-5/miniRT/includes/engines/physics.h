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
# include "physics.h"
# include "maths.h"



/* Constants */
# define MAX_CONTACTS 16384
# define SOLVER_ITERATIONS 8
# define BAUMGARTE 0.2
# define SLOP 0.01
/* Minimum approach speed for restitution to fire (kills spawn-jolt) */
# define RESTITUTION_SLOP 0.2


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
	t_vec3  inv_inertia; /* per-axis m/I (body space diagonal) — set by integrate */
	t_vec3  center;      /* world-space center of mass — updated each frame     */
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

/* Physics debug */
void	phys_debug_spheres(t_scene *scene);

/* Ray refraction */
t_vec3	refract_ray(t_vec3 incident, t_vec3 normal, float n1, float n2);

/* Sphere-mesh collision (mesh/collision.c) */
bool    detect_sphere_mesh_collision(const struct s_sphere *s, struct s_mesh *m,
				t_vec3 *out_normal, double *out_penetration);

/* Generic collider — kept for mesh capsule-simplification path */
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
		double      radius;
		t_vec3      half_extents;
		t_vec3      normal;
		struct {
			t_vec3 a;
			t_vec3 b;
			double radius;
		} capsule;
	} data;
}               t_collider;

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

/* ── GJK / EPA ──────────────────────────────────────────────────────────── */

/*
** Unified convex shape interface for GJK.
** 'support' returns the world-space point furthest along dir.
** 'center'  is the world-space center of mass.
*/
typedef t_vec3 (*t_support_fn)(const void *shape, t_vec3 dir);

typedef struct s_gjk_shape
{
	const void		*data;
	t_support_fn	support;
	t_vec3			center;
}	t_gjk_shape;

/*
** GJK simplex — up to 4 points in Minkowski-difference space.
** a_pts / b_pts track the original support points on each shape
** (needed by EPA for barycentric contact interpolation).
*/
typedef struct s_simplex
{
	t_vec3	pts[4];
	t_vec3	a_pts[4];
	t_vec3	b_pts[4];
	int		n;
}	t_simplex;

/* Support functions (one per shape type) */
t_vec3	gjk_support_sphere(const void *data, t_vec3 dir);
t_vec3	gjk_support_box(const void *data, t_vec3 dir);
t_vec3	gjk_support_capsule(const void *data, t_vec3 dir);
t_vec3	gjk_support_cylinder(const void *data, t_vec3 dir);
t_vec3	gjk_support_rect(const void *data, t_vec3 dir);
t_vec3	gjk_support_tri(const void *data, t_vec3 dir);
t_vec3	gjk_support_pyramid(const void *data, t_vec3 dir);
t_vec3	gjk_support_mesh(const void *data, t_vec3 dir);

/* GJK intersection test — fills 'out' simplex for EPA */
bool	gjk_intersect(t_gjk_shape *a, t_gjk_shape *b, t_simplex *out);

/* EPA — extracts MTD from GJK simplex */
bool	gjk_epa(t_gjk_shape *a, t_gjk_shape *b, t_simplex *s,
			t_vec3 *normal, double *depth,
			t_vec3 *contact_a, t_vec3 *contact_b);

/* Contact generation */
int		gjk_make_contact(t_gjk_shape *sa, t_gjk_shape *sb,
			t_physics_body *ba, t_physics_body *bb,
			t_transform *ta, t_transform *tb,
			t_contact *c);

int		gjk_vs_plane(t_gjk_shape *sa, t_physics_body *ba, t_transform *ta,
			t_plane *pl, t_contact *c);

/* Solver */
void    solve_velocities(t_contact *contacts, int count);
void    solve_positions(t_contact *contacts, int count);

/* Utils */
double  clamp_d(double v, double lo, double hi);


#endif
