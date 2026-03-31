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

# include "scene.h"

/* ── GJK / EPA ──────────────────────────────────────────────────────────── */
typedef t_vec3 (*t_support_fn)(const void *shape, t_vec3 dir);

typedef struct s_gjk_shape
{
	const void		*data;
	t_support_fn	support;
	t_vec3			center;
}	t_gjk_shape;

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
}						t_contact;

typedef struct s_simplex
{
	t_vec3	pts[4];
	t_vec3	a_pts[4];
	t_vec3	b_pts[4];
	int		n;
}	t_simplex;

/* Global State Access */
t_physics_state *get_physics_state(void);

/* Integration */
void    integrate_bodies(t_scene *scene, double dt);
int     generate_contacts(t_scene *scene, t_contact *contacts, int max_c);

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
