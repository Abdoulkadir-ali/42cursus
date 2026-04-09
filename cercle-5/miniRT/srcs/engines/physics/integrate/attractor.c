/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 20:50:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static void	apply_to_body(t_physics_body *b, t_vec3 at_pos,
				double g_mass)
{
	t_vec3	r;
	double	r_sq;
	double	accel_mag;

	if (b->is_static)
		return ;
	r = vec3_sub(at_pos, b->pos);
	r_sq = vec3_mag_sq(r);
	if (r_sq < 1.0)
		return ;
	accel_mag = g_mass / r_sq;
	b->accel = vec3_add(b->accel, vec3_scale(vec3_norm(r), accel_mag));
}

static void	apply_one_attractor(t_scene *s, t_attractor *at, double big_g)
{
	double	g_mass;
	size_t	i;

	g_mass = big_g * at->mass;
	i = 0;
	while (i < s->sphere_count)
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
