/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integrate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/16 18:00:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics_internal.h"

static void integrate_sphere(t_sphere *sp, double dt, t_physics_state *state)
{
    if (sp->phys.is_static)
        return ;

    /* Ensure valid physical properties */
    if (sp->phys.mass < 1e-6) sp->phys.mass = 1.0;
    if (sp->phys.elasticity < 1e-6) sp->phys.elasticity = 0.5;
    if (sp->phys.friction < 1e-6) sp->phys.friction = 0.5;

	/* Semi-implicit Euler Integration */
	
	/* 1. Velocity Update (Gravity + Damping) */
	sp->phys.velocity = vec3_add(sp->phys.velocity,
			vec3_scale(state->gravity, dt));

	/* Exponential Damping for stability and smoothness */
	/* pow(decay, dt) for frame-rate independence */
	double linear_decay = pow(1.0 - clamp_d(state->global_damping, 0, 1), dt);
	double angular_decay = pow(1.0 - clamp_d(state->global_damping * 0.5, 0, 1), dt);

	sp->phys.velocity = vec3_scale(sp->phys.velocity, linear_decay);
	sp->phys.angular_velocity = vec3_scale(sp->phys.angular_velocity, angular_decay);
	
	/* 2. Position Update */
	sp->transform.pos = vec3_add(sp->transform.pos,
			vec3_scale(sp->phys.velocity, dt));

	/* 3. Rotation Update (Approximate Euler Integration) */
	/* Convert angular velocity (rad/s) to degrees for transform */
	t_vec3 rot_deg = vec3_scale(sp->phys.angular_velocity, dt * 180.0 / M_PI);
	sp->transform.rotation.pitch += rot_deg.x;
	sp->transform.rotation.yaw += rot_deg.y;
	sp->transform.rotation.roll += rot_deg.z;
    
    /* 4. Speed Deformation (Squash & Stretch) & Caching */
    double speed = vec3_mag(sp->phys.velocity);
    double deform = speed * 0.05;
    if (deform > 0.3) deform = 0.3; /* Cap deformation */
    
    /* Simple Uniform "Energy" Expansion */
    if (speed > 0.1)
    {
        /* Stretch slightly */
        sp->transform.scale = vec3(1.0 + deform, 1.0 + deform, 1.0 + deform);
        sp->is_deformed = true;
        sp->inv_transform = mat4_inverse_transform(sp->transform);
    }
    else
    {
        /* Return to normal */
        sp->transform.scale = vec3(1, 1, 1);
        sp->is_deformed = false;
    }
}

void integrate_bodies(t_scene *scene, double dt)
{
    t_physics_state *state;
    int             i;

    if (!scene)
        return ;
    state = get_physics_state();
    i = 0;
    while (i < scene->sphere_count)
    {
        integrate_sphere(&scene->spheres[i], dt, state);
        i++;
    }
}
