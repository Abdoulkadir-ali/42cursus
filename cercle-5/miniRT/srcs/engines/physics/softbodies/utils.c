/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soft_body_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 11:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include <stdlib.h>

#define SB_GRAV_SOFT2     0.25
#define SB_GRAV_ACCEL_CAP 200.0

void	fill_particles(t_sb_particle *out, const t_mesh *mesh,
			size_t count, t_vec3 offset)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		out[i].pos = vec3_add(mesh->vertices[i].pos, offset);
		out[i].vel = vec3(0, 0, 0);
		out[i].force = vec3(0, 0, 0);
		out[i].inv_mass = 1.0 / SB_PARTICLE_MASS;
		i++;
	}
}

static bool	spring_exists(const t_sb_spring *springs, size_t n, size_t a,
				size_t b)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (springs[i].a == a && springs[i].b == b)
			return (true);
		i++;
	}
	return (false);
}

static void	add_spring(t_soft_body *sb, size_t a, size_t b)
{
	size_t	tmp;

	if (sb->spring_count >= MAX_SB_SPRINGS || a == b)
		return ;
	if (a > b)
	{
		tmp = a;
		a = b;
		b = tmp;
	}
	if (spring_exists(sb->springs, sb->spring_count, a, b))
		return ;
	sb->springs[sb->spring_count].a = a;
	sb->springs[sb->spring_count].b = b;
	sb->springs[sb->spring_count].rest_len = vec3_mag(vec3_sub(
				sb->particles[b].pos, sb->particles[a].pos));
	sb->springs[sb->spring_count].stiffness = sb->stiffness;
	sb->springs[sb->spring_count].damping = sb->damping;
	sb->spring_count++;
}

void	soft_body_build_springs(t_soft_body *sb, t_mesh *mesh,
				size_t p_count)
{
	size_t	i;
	size_t	*idx;

	sb->spring_count = 0;
	i = -1;
	while (++i < mesh->tri_count)
	{
		idx = (size_t *)mesh->triangles[i].v;
		if (idx[0] < p_count && idx[1] < p_count && idx[2] < p_count)
		{
			add_spring(sb, idx[0], idx[1]);
			add_spring(sb, idx[1], idx[2]);
			add_spring(sb, idx[0], idx[2]);
		}
		else
		{
			if (idx[0] < p_count)
				sb->particles[idx[0]].inv_mass = 0.0;
			if (idx[1] < p_count)
				sb->particles[idx[1]].inv_mass = 0.0;
			if (idx[2] < p_count)
				sb->particles[idx[2]].inv_mass = 0.0;
		}
	}
}

void	apply_one_body_to_sb(t_soft_body *sb, t_vec3 body_pos,
				double g_mass)
{
	t_sb_particle	*p;
	t_vec3			r_v;
	double			r[2];
	size_t			pi;

	pi = 0;
	while (pi < sb->particle_count)
	{
		p = &sb->particles[pi];
		if (p->inv_mass > 0.0)
		{
			r_v = vec3_sub(body_pos, p->pos);
			r[0] = vec3_mag_sq(r_v) + SB_GRAV_SOFT2;
			r[1] = g_mass / r[0];
			if (r[1] > SB_GRAV_ACCEL_CAP)
				r[1] = SB_GRAV_ACCEL_CAP;
			p->force = vec3_add(p->force,
					vec3_scale(vec3_norm(r_v), r[1] / p->inv_mass));
		}
		pi++;
	}
}
