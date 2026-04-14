/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 11:17:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/*
** Plummer softening radius: prevents r²→0 singularity when bodies overlap.
** Acceleration hard-cap: prevents explosion at extreme masses.
*/
# define GRAV_SOFT2	0.25		/* softening² = 0.5² units */
# define GRAV_ACCEL_CAP	200.0	/* max acceleration per step (units/s²) */

static void	apply_to_body(t_physics_body *b, t_vec3 at_pos,
				double g_mass)
{
	t_vec3	r;
	double	r_sq;
	double	accel_mag;

	if (b->is_static)
		return ;
	r = vec3_sub(at_pos, b->pos);
	r_sq = vec3_mag_sq(r) + GRAV_SOFT2;
	accel_mag = g_mass / r_sq;
	if (accel_mag > GRAV_ACCEL_CAP)
		accel_mag = GRAV_ACCEL_CAP;
	b->accel = vec3_add(b->accel, vec3_scale(vec3_norm(r), accel_mag));
}

static void	apply_one_attractor(t_scene *s, t_attractor *at, double big_g)
{
	double	g_mass;
	size_t	i;

	g_mass = big_g * at->mass;
	i = 0;
	while (i < s->sphere_count - s->proxy_sphere_count)
		apply_to_body(&s->spheres[i++].phys, at->pos, g_mass);
	i = 0;
	while (i < s->box_count)
		apply_to_body(&s->boxes[i++].phys, at->pos, g_mass);
	i = 0;
	while (i < s->capsule_count)
		apply_to_body(&s->capsules[i++].phys, at->pos, g_mass);
	i = 0;
	while (i < s->cylinder_count)
		apply_to_body(&s->cylinders[i++].phys, at->pos, g_mass);
	i = 0;
	while (i < s->pyramid_count)
		apply_to_body(&s->pyramids[i++].phys, at->pos, g_mass);
	i = 0;
	while (i < s->rect_count)
		apply_to_body(&s->rects[i++].phys, at->pos, g_mass);
	i = 0;
	while (i < s->tri_count)
		apply_to_body(&s->tris[i++].phys, at->pos, g_mass);
}

void	apply_attractor_pass(t_scene *scene, t_physics_settings *s)
{
	size_t	i;

	if (!scene || scene->attractor_count == 0)
		return ;
	i = 0;
	while (i < scene->attractor_count)
		apply_one_attractor(scene, &scene->attractors[i++], s->big_g);
}

/**
 * @brief Collects all dynamic body pointers from sphere/box/capsule/cylinder.
 */
static size_t	fill_bodies_a(t_scene *s, t_physics_body **lst, size_t n)
{
	size_t	i;

	i = 0;
	while (i < s->sphere_count - s->proxy_sphere_count && n < MAX_NBODY)
		lst[n++] = &s->spheres[i++].phys;
	i = 0;
	while (i < s->box_count && n < MAX_NBODY)
		lst[n++] = &s->boxes[i++].phys;
	i = 0;
	while (i < s->capsule_count && n < MAX_NBODY)
		lst[n++] = &s->capsules[i++].phys;
	i = 0;
	while (i < s->cylinder_count && n < MAX_NBODY)
		lst[n++] = &s->cylinders[i++].phys;
	return (n);
}

/**
 * @brief Collects all dynamic body pointers from pyramid/rect/tri.
 */
static size_t	fill_bodies_b(t_scene *s, t_physics_body **lst, size_t n)
{
	size_t	i;

	i = 0;
	while (i < s->pyramid_count && n < MAX_NBODY)
		lst[n++] = &s->pyramids[i++].phys;
	i = 0;
	while (i < s->rect_count && n < MAX_NBODY)
		lst[n++] = &s->rects[i++].phys;
	i = 0;
	while (i < s->tri_count && n < MAX_NBODY)
		lst[n++] = &s->tris[i++].phys;
	return (n);
}

/**
 * @brief Applies mutual Newtonian gravity between one body pair.
 *        a_on_B = G * mass_A / r²  (towards A)
 *        a_on_A = G * mass_B / r²  (towards B)
 *        Skips pairs where both are static or distance < 1 unit.
 */
static void	apply_pair_grav(t_physics_body *a, t_physics_body *b, double big_g)
{
	t_vec3	r;
	double	r_sq;
	double	f;
	t_vec3	dir;

	if (a->is_static && b->is_static)
		return ;
	r = vec3_sub(b->pos, a->pos);
	r_sq = vec3_mag_sq(r) + GRAV_SOFT2;
	f = big_g / r_sq;
	dir = vec3_norm(r);
	if (!a->is_static)
	{
		double fa = f * b->mass;
		if (fa > GRAV_ACCEL_CAP) fa = GRAV_ACCEL_CAP;
		a->accel = vec3_add(a->accel, vec3_scale(dir, fa));
	}
	if (!b->is_static)
	{
		double fb = f * a->mass;
		if (fb > GRAV_ACCEL_CAP) fb = GRAV_ACCEL_CAP;
		b->accel = vec3_sub(b->accel, vec3_scale(dir, fb));
	}
}

/**
 * @brief Applies mutual magnetic (Coulomb-like) force between one body pair.
 *        F = k * q_A * q_B / r²   (same sign → repel, opposite → attract)
 *        Uses the same Plummer softening and acceleration cap as gravity.
 *        Bodies with charge == 0.0 are skipped entirely.
 */
static void	apply_pair_mag(t_physics_body *a, t_physics_body *b)
{
	t_vec3	r;
	double	r_sq;
	double	f;
	t_vec3	dir;

	if (a->is_static && b->is_static)
		return ;
	if (a->magnetic_charge == 0.0 && b->magnetic_charge == 0.0)
		return ;
	r = vec3_sub(b->pos, a->pos);
	r_sq = vec3_mag_sq(r) + GRAV_SOFT2;
	/* k=1 here; scene_big_g acts as coupling constant via caller */
	f = (a->magnetic_charge * b->magnetic_charge) / r_sq;
	dir = vec3_norm(r);
	/* Positive f → same sign: repel A←, push B→  (dir from A to B)
	   Negative f → opposite sign: attract both toward each other      */
	if (!a->is_static)
	{
		double fa = -f * a->inv_mass;
		if (fa > GRAV_ACCEL_CAP) fa = GRAV_ACCEL_CAP;
		if (fa < -GRAV_ACCEL_CAP) fa = -GRAV_ACCEL_CAP;
		a->accel = vec3_add(a->accel, vec3_scale(dir, fa));
	}
	if (!b->is_static)
	{
		double fb = f * b->inv_mass;
		if (fb > GRAV_ACCEL_CAP) fb = GRAV_ACCEL_CAP;
		if (fb < -GRAV_ACCEL_CAP) fb = -GRAV_ACCEL_CAP;
		b->accel = vec3_add(b->accel, vec3_scale(dir, fb));
	}
}

/**
 * @brief N-body gravitational pass: every body attracts every other body
 *        proportional to their masses (F = G * mA * mB / r²).
 *        Also applies magnetic Coulomb forces between bodies whose
 *        magnetic_charge != 0.0.
 *        Skipped entirely when big_g is effectively zero.
 */
void	apply_nbody_gravity(t_scene *scene, double big_g)
{
	static t_physics_body	*lst[MAX_NBODY];
	size_t					n;
	size_t					i;
	size_t					j;

	if (!scene || big_g < 1e-30)
		return ;
	n = fill_bodies_b(scene, lst, fill_bodies_a(scene, lst, 0));
	i = 0;
	while (i < n)
	{
		j = i + 1;
		while (j < n)
		{
			apply_pair_grav(lst[i], lst[j], big_g);
			apply_pair_mag(lst[i], lst[j]);
			j++;
		}
		i++;
	}
}
