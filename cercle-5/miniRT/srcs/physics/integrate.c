/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integrate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:31:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "objects.h"
#include "scene.h"

static void	apply_damping(t_sphere *sp, double dt, t_physics_state *state)
{
	double	linear_decay;
	double	angular_decay;
	double	damp;

	damp = clamp_d(state->global_damping, 0, 1);
	linear_decay = pow(1.0 - damp, dt);
	angular_decay = pow(1.0 - damp * 0.5, dt);
	sp->phys.velocity = vec3_scale(sp->phys.velocity, linear_decay);
	sp->phys.angular_velocity = vec3_scale(sp->phys.angular_velocity,
			angular_decay);
}

static void	update_rotation(t_sphere *sp, double dt)
{
	t_vec3	rot_deg;

	rot_deg = vec3_scale(sp->phys.angular_velocity, dt * 180.0 / M_PI);
	sp->transform.rotation.pitch += rot_deg.x;
	sp->transform.rotation.yaw += rot_deg.y;
	sp->transform.rotation.roll += rot_deg.z;
}

/*
** Build a scale-only inverse for deformation rendering.
** Rotation must NOT be included — it would rotate the normals,
** making shading "stick" to the sphere surface.
*/
static void	apply_deformation(t_sphere *sp)
{
	double		speed;
	double		deform;
	t_transform	scale_only;

	speed = vec3_mag(sp->phys.velocity);
	deform = speed * 0.05;
	if (deform > 0.3)
		deform = 0.3;
	if (speed > 0.1)
	{
		sp->transform.scale = vec3(1.0 + deform, 1.0 + deform,
				1.0 + deform);
		sp->is_deformed = true;
		scale_only.pos = sp->transform.pos;
		scale_only.scale = sp->transform.scale;
		scale_only.rotation = (t_rotator){0, 0, 0};
		sp->inv_transform = mat4_inverse_transform(scale_only);
	}
	else
	{
		sp->transform.scale = vec3(1, 1, 1);
		sp->is_deformed = false;
	}
}

static void	integrate_sphere(t_sphere *sp, double dt, t_physics_state *state)
{
	if (sp->phys.is_static)
		return ;
	if (sp->phys.mass < 1e-6)
		sp->phys.mass = 1.0;
	if (sp->phys.elasticity < 1e-6)
		sp->phys.elasticity = 0.5;
	if (sp->phys.friction < 1e-6)
		sp->phys.friction = 0.5;
	sp->phys.velocity = vec3_add(sp->phys.velocity,
			vec3_scale(state->gravity, dt));
	apply_damping(sp, dt, state);
	sp->transform.pos = vec3_add(sp->transform.pos,
			vec3_scale(sp->phys.velocity, dt));
	update_rotation(sp, dt);
	apply_deformation(sp);
}

void	integrate_bodies(t_scene *scene, double dt)
{
	t_physics_state	*state;
	int				i;

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
