/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collide.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/16 18:00:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics_internal.h"
#include "objects.h" /* For detect_... prototypes if needed */

/* 
 * detect_sphere_sphere_collision is from physics.c/h (the old one), 
 * here we wrap it or reimplement it to fill t_contact.
 * We'll reimplement cleanly to avoid dependency on old file.
 */

bool collide_sphere_sphere(t_sphere *a, t_sphere *b, t_contact *c)
{
    t_vec3  delta;
    double  dist_sq;
    double  r_sum;
    double  dist;
    double  sa;
    double  sb;

    delta = vec3_sub(b->transform.pos, a->transform.pos);
    dist_sq = vec3_mag_sq(delta);
    
    sa = fabs(a->transform.scale.x); if (sa < 1e-4) sa = 1.0;
    sb = fabs(b->transform.scale.x); if (sb < 1e-4) sb = 1.0;
    
    r_sum = (sqrt(a->radius_sq) * sa) + (sqrt(b->radius_sq) * sb);
    if (dist_sq > r_sum * r_sum || dist_sq < 1e-8)
        return (false);
    dist = sqrt(dist_sq);
    c->normal = vec3_scale(delta, 1.0 / dist);
    c->penetration = r_sum - dist;
    c->a = &a->phys;
    c->b = &b->phys;
    c->ta = &a->transform;
    c->tb = &b->transform;
    /* Contact point aprox */
    c->contact_point = vec3_add(a->transform.pos,
            vec3_scale(c->normal, sqrt(a->radius_sq) * sa));
    c->restitution = fmin(a->phys.elasticity, b->phys.elasticity);
    c->friction = sqrt(a->phys.friction * b->phys.friction);
    return (true);
}

bool collide_sphere_plane(t_sphere *s, t_plane *pl, t_contact *c)
{
    t_vec3  normal;
    t_vec3  to_center;
    double  dist;
    double  radius;
    double  scale;

    normal = pl->transform.up;
    if (vec3_mag_sq(normal) < 1e-6)
        normal = (t_vec3){0, 1, 0, 0};
    else
        normal = vec3_norm(normal);
    to_center = vec3_sub(s->transform.pos, pl->transform.pos);
    dist = vec3_dot(to_center, normal);
    
    scale = fabs(s->transform.scale.x); if (scale < 1e-4) scale = 1.0;
    radius = sqrt(s->radius_sq) * scale;
    
    if (dist >= radius)
        return (false);
    c->normal = vec3_scale(normal, -1.0); /* Normal points A -> B (Sphere -> Plane) */
    c->penetration = radius - dist;
    c->a = &s->phys;
    c->b = NULL; /* Plane has no physics body (static infinite mass) */
    c->ta = &s->transform;
    c->tb = &pl->transform;
    c->contact_point = vec3_sub(s->transform.pos,
            vec3_scale(normal, radius));
    c->restitution = fmin(s->phys.elasticity, 0.2); /* Plane low elasticity (dampening) */
    c->friction = sqrt(s->phys.friction * 0.5); /* Plane default friction 0.5 */
    return (true);
}

bool collide_sphere_mesh(t_sphere *s, t_mesh *m, t_contact *c)
{
    t_vec3  n;
    double  pen;

    if (!detect_sphere_mesh_collision(s, m, &n, &pen))
        return (false);
    c->normal = n;
    c->penetration = pen;
    c->a = &s->phys;
    c->b = NULL; /* Mesh is static force */
    c->ta = &s->transform;
    c->tb = &m->transform;
    c->contact_point = vec3_sub(s->transform.pos,
            vec3_scale(n, sqrt(s->radius_sq))); /* Approx */
    c->restitution = s->phys.elasticity;
    c->friction = sqrt(s->phys.friction * m->phys.friction);
    return (true);
}
