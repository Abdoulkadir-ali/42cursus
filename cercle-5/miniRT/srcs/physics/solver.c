/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/16 18:00:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics_internal.h"

/* Solve position constraints (prevent sinking)
 * Moves objects apart based on penetration depth and inverse mass.
 */
void solve_positions(t_contact *c, int count)
{
    int     i;
    double  inv_a, inv_b, inv_sum;
    t_vec3  correction;
    double  percent;

    percent = BAUMGARTE; /* Usually 0.2 to 0.8 */
    i = 0;
    while (i < count)
    {
        inv_a = (c[i].a && c[i].a->mass > 1e-6 && !c[i].a->is_static) ? 1.0 / c[i].a->mass : 0.0;
        inv_b = (c[i].b && c[i].b->mass > 1e-6 && !c[i].b->is_static) ? 1.0 / c[i].b->mass : 0.0;
        inv_sum = inv_a + inv_b;
        if (inv_sum > 1e-8)
        {
            double depth = fmax(c[i].penetration - SLOP, 0.0);
            double scalar = depth / inv_sum * percent;
            correction = vec3_scale(c[i].normal, scalar);
            if (c[i].a && inv_a > 0.0)
                c[i].ta->pos = vec3_sub(c[i].ta->pos, vec3_scale(correction, inv_a));
            if (c[i].b && inv_b > 0.0)
                c[i].tb->pos = vec3_add(c[i].tb->pos, vec3_scale(correction, inv_b));
        }
        i++;
    }
}

/* Solve velocity constraints (bounce + friction) */
void solve_velocities(t_contact *c, int count)
{
    int     i;
    double  inv_a, inv_b, inv_sum;
    t_vec3  rel_v, impulse, tangent;
    double  vn, j, vt;

    i = 0;
    while (i < count)
    {
        inv_a = (c[i].a && c[i].a->mass > 1e-6 && !c[i].a->is_static) ? 1.0 / c[i].a->mass : 0.0;
        inv_b = (c[i].b && c[i].b->mass > 1e-6 && !c[i].b->is_static) ? 1.0 / c[i].b->mass : 0.0;
        inv_sum = inv_a + inv_b;
        if (inv_sum <= 1e-8) { i++; continue; }

        t_vec3 va = (c[i].a) ? c[i].a->velocity : (t_vec3){0};
        t_vec3 vb = (c[i].b) ? c[i].b->velocity : (t_vec3){0};
        rel_v = vec3_sub(vb, va);
        vn = vec3_dot(rel_v, c[i].normal);

        /* 1. Normal Impulse (Bounce) */
        if (vn < 0.0)
        {
            j = -(1.0 + c[i].restitution) * vn / inv_sum;
            impulse = vec3_scale(c[i].normal, j);
            if (c[i].a && inv_a > 0.0) c[i].a->velocity = vec3_sub(c[i].a->velocity, vec3_scale(impulse, inv_a));
            if (c[i].b && inv_b > 0.0) c[i].b->velocity = vec3_add(c[i].b->velocity, vec3_scale(impulse, inv_b));
        }

        /* 2. Tangent Impulse (Friction) */
        /* Re-calculate relative velocity including angular velocity */
        va = (c[i].a) ? c[i].a->velocity : (t_vec3){0};
        vb = (c[i].b) ? c[i].b->velocity : (t_vec3){0};
		t_vec3 wa = (c[i].a) ? c[i].a->angular_velocity : (t_vec3){0};
		t_vec3 wb = (c[i].b) ? c[i].b->angular_velocity : (t_vec3){0};
		
		t_vec3 va_pt = vec3_add(va, vec3_cross(wa, c[i].ra));
		t_vec3 vb_pt = vec3_add(vb, vec3_cross(wb, c[i].rb));
        rel_v = vec3_sub(vb_pt, va_pt);
        
        t_vec3 vn_vec = vec3_scale(c[i].normal, vec3_dot(rel_v, c[i].normal));
        t_vec3 vt_vec = vec3_sub(rel_v, vn_vec);
        double vt_mag_sq = vec3_mag_sq(vt_vec);
        
        if (vt_mag_sq > 1e-6) // Only apply if significant tangential movement
        {
            tangent = vec3_norm(vt_vec);
            vt = vec3_dot(rel_v, tangent);
            double kt = inv_sum; // Simplified tangent mass
            double jt = -vt / kt;
            
            /* Coulomb friction limit */
            /* Using accumulated normal impulse would be better, but simplified: */
            // double max_j = c[i].friction * ...;
            
            if (jt > 0.0) jt = 0.0;
            
            t_vec3 friction_impulse = vec3_scale(tangent, jt * c[i].friction); // Scaling by friction directly as simplified model
            
             if (c[i].a && inv_a > 0.0) {
                 c[i].a->velocity = vec3_sub(c[i].a->velocity, vec3_scale(friction_impulse, inv_a));
				 /* Apply Torque: ra x (-J) */
				 t_vec3 torque = vec3_cross(c[i].ra, vec3_scale(friction_impulse, -1.0));
				 double r2 = vec3_mag_sq(c[i].ra);
				 double inv_inertia = (r2 > 1e-6) ? (2.5 / r2) : 0.0;
				 c[i].a->angular_velocity = vec3_add(c[i].a->angular_velocity, vec3_scale(torque, inv_a * inv_inertia));
			 }
             if (c[i].b && inv_b > 0.0) {
                 c[i].b->velocity = vec3_add(c[i].b->velocity, vec3_scale(friction_impulse, inv_b));
				 /* Apply Torque: rb x J */
				 t_vec3 torque = vec3_cross(c[i].rb, friction_impulse);
				 double r2 = vec3_mag_sq(c[i].rb);
				 double inv_inertia = (r2 > 1e-6) ? (2.5 / r2) : 0.0;
				 c[i].b->angular_velocity = vec3_add(c[i].b->angular_velocity, vec3_scale(torque, inv_b * inv_inertia));
			 }
        }
        i++;
    }
}
