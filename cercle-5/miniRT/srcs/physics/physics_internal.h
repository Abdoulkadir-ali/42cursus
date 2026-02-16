/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/16 18:00:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSICS_INTERNAL_H
# define PHYSICS_INTERNAL_H

# include "physics.h"
# include "scene.h"
# include "maths.h"
# include "objects.h"
# include <math.h>

# ifndef fmin
#  define fmin(a, b) ((a) < (b) ? (a) : (b))
# endif

# ifndef fmax
#  define fmax(a, b) ((a) > (b) ? (a) : (b))
# endif

/* Constants */
# define MAX_CONTACTS 1024
# define SOLVER_ITERATIONS 8
# define BAUMGARTE 0.2
# define SLOP 0.01

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
