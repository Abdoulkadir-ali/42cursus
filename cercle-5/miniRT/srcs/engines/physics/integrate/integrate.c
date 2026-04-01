/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integrate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
#include "physics.h"
#include <math.h>
/*
** Rodrigues rotation: rotate v by angular_velocity*dt radians.
** Returns v unchanged when |w|*dt < epsilon.
*/
static t_vec3	rot_by_ang(t_vec3 v, t_vec3 w, double dt)
{
	double	theta;
	t_vec3	n;
	double	c;
	double	s;

	theta = vec3_mag(w) * dt;
	if (theta < 1e-9)
		return (v);
	n = vec3_norm(w);
	c = cos(theta);
	s = sin(theta);
	return (vec3_add(vec3_add(vec3_scale(v, c),
				vec3_scale(vec3_cross(n, v), s)),
			vec3_scale(n, vec3_dot(n, v) * (1.0 - c))));
}

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

static void	init_sphere_inertia(t_sphere *sp)
{
	double	inv_i;

	if (vec3_mag_sq(sp->phys.inv_inertia) > 1e-9)
		return ;
	if (sp->radius_sq < 1e-9)
		inv_i = 1.0;
	else
		inv_i = 2.5 / sp->radius_sq;
	sp->phys.inv_inertia = vec3(inv_i, inv_i, inv_i);
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
	init_sphere_inertia(sp);
	sp->phys.velocity = vec3_add(sp->phys.velocity,
			vec3_scale(state->gravity, dt));
	apply_damping(sp, dt, state);
	sp->transform.pos = vec3_add(sp->transform.pos,
			vec3_scale(sp->phys.velocity, dt));
	update_rotation(sp, dt);
	apply_deformation(sp);
	sp->phys.center = sp->transform.pos;
}

static void	init_rect_inertia(t_rect *rc)
{
	t_vec3	e0;
	t_vec3	e1;
	double	w2;
	double	h2;

	if (vec3_mag_sq(rc->phys.inv_inertia) > 1e-9)
		return ;
	e0 = vec3_sub(rc->v[1], rc->v[0]);
	e1 = vec3_sub(rc->v[3], rc->v[0]);
	w2 = vec3_mag_sq(e0) + 1e-9;
	h2 = vec3_mag_sq(e1) + 1e-9;
	rc->phys.inv_inertia.x = 12.0 / h2;
	rc->phys.inv_inertia.y = 12.0 / (w2 + h2);
	rc->phys.inv_inertia.z = 12.0 / w2;
}

static void	integrate_rect(t_rect *rc, double dt, t_physics_state *state)
{
	t_vec3	delta;
	t_vec3	rot_d;
	int		i;

	if (rc->phys.is_static)
		return ;
	if (rc->phys.mass < 1e-6)
		rc->phys.mass = 1.0;
	init_rect_inertia(rc);
	delta = vec3_scale(vec3_add(vec3_add(rc->v[0], rc->v[1]),
				vec3_add(rc->v[2], rc->v[3])), 0.25);
	delta = vec3_sub(rc->transform.pos, delta);
	i = 0;
	while (i < 4)
	{
		rc->v[i] = vec3_add(rc->v[i], delta);
		i++;
	}
	rc->phys.velocity = vec3_add(rc->phys.velocity,
			vec3_scale(state->gravity, dt));
	rc->phys.velocity = vec3_scale(rc->phys.velocity,
			clamp_d(1.0 - state->global_damping * dt, 0, 1));
	rc->phys.angular_velocity = vec3_scale(rc->phys.angular_velocity,
			clamp_d(1.0 - state->global_damping * 0.5 * dt, 0, 1));
	delta = vec3_scale(rc->phys.velocity, dt);
	rot_d = vec3_scale(rc->phys.angular_velocity, dt * (180.0 / M_PI));
	rc->transform.rotation.pitch += rot_d.x;
	rc->transform.rotation.yaw += rot_d.y;
	rc->transform.rotation.roll += rot_d.z;
	rc->normal = rot_by_ang(rc->normal, rc->phys.angular_velocity, dt);
	i = 0;
	while (i < 4)
	{
		rc->v[i] = vec3_add(vec3_add(rc->transform.pos,
				rot_by_ang(vec3_sub(rc->v[i], rc->transform.pos),
					rc->phys.angular_velocity, dt)), delta);
		i++;
	}
	rc->transform.pos = vec3_add(rc->transform.pos, delta);
	rc->phys.center = rc->transform.pos;
}

static void	integrate_pyramid(t_pyramid *py, double dt, t_physics_state *state)
{
	t_vec3	rot_d;

	if (py->phys.is_static)
		return ;
	if (py->phys.mass < 1e-6)
		py->phys.mass = 1.0;
	if (vec3_mag_sq(py->phys.inv_inertia) < 1e-9)
	{
		const double	s2 = py->base_size * py->base_size + 1e-9;
		const double	h2 = py->height * py->height + 1e-9;
		py->phys.inv_inertia.x = 10.0 / (s2 * 0.25 + h2 * 0.4);
		py->phys.inv_inertia.y = 6.0 / s2;
		py->phys.inv_inertia.z = 10.0 / (s2 * 0.25 + h2 * 0.4);
	}
	py->phys.velocity = vec3_add(py->phys.velocity,
			vec3_scale(state->gravity, dt));
	py->phys.velocity = vec3_scale(py->phys.velocity,
			clamp_d(1.0 - state->global_damping * dt, 0, 1));
	py->phys.angular_velocity = vec3_scale(py->phys.angular_velocity,
			clamp_d(1.0 - state->global_damping * 0.5 * dt, 0, 1));
	rot_d = vec3_scale(py->phys.angular_velocity, dt * (180.0 / M_PI));
	py->transform.rotation.pitch += rot_d.x;
	py->transform.rotation.yaw += rot_d.y;
	py->transform.rotation.roll += rot_d.z;
	py->up = vec3_norm(rot_by_ang(py->up, py->phys.angular_velocity, dt));
	py->transform.pos = vec3_add(py->transform.pos,
			vec3_scale(py->phys.velocity, dt));
	py->phys.center = vec3_add(py->transform.pos,
			vec3_scale(py->up, py->height * 0.25));
}

static void	init_box_inertia(t_box *bx)
{
	t_vec3	e;

	if (vec3_mag_sq(bx->phys.inv_inertia) > 1e-9)
		return ;
	e = bx->half_extents;
	bx->phys.inv_inertia.x = 3.0 / (e.y * e.y + e.z * e.z + 1e-9);
	bx->phys.inv_inertia.y = 3.0 / (e.x * e.x + e.z * e.z + 1e-9);
	bx->phys.inv_inertia.z = 3.0 / (e.x * e.x + e.y * e.y + 1e-9);
}

static void	integrate_box(t_box *bx, double dt, t_physics_state *state)
{
	t_vec3	rot_d;

	if (bx->phys.is_static)
		return ;
	if (bx->phys.mass < 1e-6)
		bx->phys.mass = 1.0;
	init_box_inertia(bx);
	bx->phys.velocity = vec3_add(bx->phys.velocity,
			vec3_scale(state->gravity, dt));
	bx->phys.velocity = vec3_scale(bx->phys.velocity,
			clamp_d(1.0 - state->global_damping * dt, 0, 1));
	bx->phys.angular_velocity = vec3_scale(bx->phys.angular_velocity,
			clamp_d(1.0 - state->global_damping * 0.5 * dt, 0, 1));
	rot_d = vec3_scale(bx->phys.angular_velocity, dt * (180.0 / M_PI));
	bx->transform.rotation.pitch += rot_d.x;
	bx->transform.rotation.yaw += rot_d.y;
	bx->transform.rotation.roll += rot_d.z;
	bx->transform.forward = vec3_norm(rot_by_ang(bx->transform.forward,
			bx->phys.angular_velocity, dt));
	bx->transform.pos = vec3_add(bx->transform.pos,
			vec3_scale(bx->phys.velocity, dt));
	bx->phys.center = bx->transform.pos;
}

static void	init_capsule_inertia(t_capsule *cap)
{
	double	r2;
	double	h2;

	if (vec3_mag_sq(cap->phys.inv_inertia) > 1e-9)
		return ;
	r2 = cap->radius * cap->radius + 1e-9;
	h2 = 4.0 * cap->half_height * cap->half_height;
	cap->phys.inv_inertia.x = 12.0 / (3.0 * r2 + h2);
	cap->phys.inv_inertia.y = 2.0 / r2;
	cap->phys.inv_inertia.z = 12.0 / (3.0 * r2 + h2);
}

static void	integrate_capsule(t_capsule *cap, double dt, t_physics_state *state)
{
	t_vec3	rot_d;

	if (cap->phys.is_static)
		return ;
	if (cap->phys.mass < 1e-6)
		cap->phys.mass = 1.0;
	init_capsule_inertia(cap);
	cap->phys.velocity = vec3_add(cap->phys.velocity,
			vec3_scale(state->gravity, dt));
	cap->phys.velocity = vec3_scale(cap->phys.velocity,
			clamp_d(1.0 - state->global_damping * dt, 0, 1));
	cap->phys.angular_velocity = vec3_scale(cap->phys.angular_velocity,
			clamp_d(1.0 - state->global_damping * 0.5 * dt, 0, 1));
	rot_d = vec3_scale(cap->phys.angular_velocity, dt * (180.0 / M_PI));
	cap->transform.rotation.pitch += rot_d.x;
	cap->transform.rotation.yaw += rot_d.y;
	cap->transform.rotation.roll += rot_d.z;
	cap->axis = vec3_norm(rot_by_ang(cap->axis, cap->phys.angular_velocity, dt));
	cap->transform.pos = vec3_add(cap->transform.pos,
			vec3_scale(cap->phys.velocity, dt));
	cap->phys.center = cap->transform.pos;
}

static void	init_tri_inertia(t_tri_shape *tr)
{
	double	a2;
	double	b2;

	if (vec3_mag_sq(tr->phys.inv_inertia) > 1e-9)
		return ;
	a2 = vec3_mag_sq(vec3_sub(tr->v[1], tr->v[0])) + 1e-9;
	b2 = vec3_mag_sq(vec3_sub(tr->v[2], tr->v[0])) + 1e-9;
	tr->phys.inv_inertia.x = 18.0 / b2;
	tr->phys.inv_inertia.y = 18.0 / (a2 + b2);
	tr->phys.inv_inertia.z = 18.0 / a2;
}

static void	integrate_tri(t_tri_shape *tr, double dt, t_physics_state *state)
{
	t_vec3	delta;
	t_vec3	rot_d;
	int		i;

	if (tr->phys.is_static)
		return ;
	if (tr->phys.mass < 1e-6)
		tr->phys.mass = 1.0;
	init_tri_inertia(tr);
	delta = vec3_scale(vec3_add(vec3_add(tr->v[0], tr->v[1]), tr->v[2]),
			1.0 / 3.0);
	delta = vec3_sub(tr->xform.pos, delta);
	i = 0;
	while (i < 3)
	{
		tr->v[i] = vec3_add(tr->v[i], delta);
		i++;
	}
	tr->phys.velocity = vec3_add(tr->phys.velocity,
			vec3_scale(state->gravity, dt));
	tr->phys.velocity = vec3_scale(tr->phys.velocity,
			clamp_d(1.0 - state->global_damping * dt, 0, 1));
	tr->phys.angular_velocity = vec3_scale(tr->phys.angular_velocity,
			clamp_d(1.0 - state->global_damping * 0.5 * dt, 0, 1));
	delta = vec3_scale(tr->phys.velocity, dt);
	rot_d = vec3_scale(tr->phys.angular_velocity, dt * (180.0 / M_PI));
	tr->xform.rotation.pitch += rot_d.x;
	tr->xform.rotation.yaw += rot_d.y;
	tr->xform.rotation.roll += rot_d.z;
	tr->normal = rot_by_ang(tr->normal, tr->phys.angular_velocity, dt);
	i = 0;
	while (i < 3)
	{
		tr->v[i] = vec3_add(vec3_add(tr->xform.pos,
				rot_by_ang(vec3_sub(tr->v[i], tr->xform.pos),
					tr->phys.angular_velocity, dt)), delta);
		i++;
	}
	tr->xform.pos = vec3_add(tr->xform.pos, delta);
	tr->phys.center = tr->xform.pos;
}

static void	init_cylinder_inertia(t_cylinder *cy)
{
	double	r2;
	double	h2;

	if (vec3_mag_sq(cy->phys.inv_inertia) > 1e-9)
		return ;
	r2 = cy->transform.scale.x * cy->transform.scale.x + 1e-9;
	h2 = 4.0 * cy->transform.scale.y * cy->transform.scale.y;
	cy->phys.inv_inertia.x = 12.0 / (3.0 * r2 + h2);
	cy->phys.inv_inertia.y = 2.0 / r2;
	cy->phys.inv_inertia.z = 12.0 / (3.0 * r2 + h2);
}

static void	integrate_cylinder(t_cylinder *cy, double dt, t_physics_state *state)
{
	t_vec3	rot_d;

	if (cy->phys.is_static)
		return ;
	if (cy->phys.mass < 1e-6)
		cy->phys.mass = 1.0;
	init_cylinder_inertia(cy);
	cy->phys.velocity = vec3_add(cy->phys.velocity,
			vec3_scale(state->gravity, dt));
	cy->phys.velocity = vec3_scale(cy->phys.velocity,
			clamp_d(1.0 - state->global_damping * dt, 0, 1));
	cy->phys.angular_velocity = vec3_scale(cy->phys.angular_velocity,
			clamp_d(1.0 - state->global_damping * 0.5 * dt, 0, 1));
	rot_d = vec3_scale(cy->phys.angular_velocity, dt * (180.0 / M_PI));
	cy->transform.rotation.pitch += rot_d.x;
	cy->transform.rotation.yaw += rot_d.y;
	cy->transform.rotation.roll += rot_d.z;
	cy->transform.forward = vec3_norm(rot_by_ang(cy->transform.forward,
			cy->phys.angular_velocity, dt));
	cy->transform.pos = vec3_add(cy->transform.pos,
			vec3_scale(cy->phys.velocity, dt));
	cy->phys.center = vec3_add(cy->transform.pos,
			vec3_scale(vec3_norm(cy->transform.forward),
				cy->transform.scale.y * 0.5));
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
		integrate_sphere(&scene->spheres[i++], dt, state);
	i = 0;
	while (i < scene->rect_count)
		integrate_rect(&scene->rects[i++], dt, state);
	i = 0;
	while (i < scene->pyramid_count)
		integrate_pyramid(&scene->pyramids[i++], dt, state);
	i = 0;
	while (i < scene->box_count)
		integrate_box(&scene->boxes[i++], dt, state);
	i = 0;
	while (i < scene->capsule_count)
		integrate_capsule(&scene->capsules[i++], dt, state);
	i = 0;
	while (i < scene->tri_count)
		integrate_tri(&scene->tris[i++], dt, state);
	i = 0;
	while (i < scene->cylinder_count)
		integrate_cylinder(&scene->cylinders[i++], dt, state);
}
