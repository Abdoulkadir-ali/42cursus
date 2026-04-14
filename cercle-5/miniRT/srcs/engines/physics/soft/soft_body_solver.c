/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soft_body_solver.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

void	accumulate_ext_f(t_soft_body *sb, const t_physics_settings *s)
{
	size_t	i;
	double	m;

	i = 0;
	while (i < sb->particle_count)
	{
		sb->particles[i].force = vec3(0, 0, 0);
		if (sb->particles[i].inv_mass > 0.0)
		{
			m = 1.0 / sb->particles[i].inv_mass;
			sb->particles[i].force = vec3_scale(s->gravity, m);
			if (vec3_mag_sq(s->wind) > 1e-9 || s->wind_turbulence > 1e-9)
				sb->particles[i].force = vec3_add(sb->particles[i].force,
						vec3_scale(s->wind, m));
		}
		i++;
	}
}

void	accumulate_spring_f(t_soft_body *sb)
{
	size_t			i;
	t_sb_spring		*sp;
	t_vec3			ab;
	t_vec3			rv;
	double			d[2];

	i = 0;
	while (i < sb->spring_count)
	{
		sp = &sb->springs[i++];
		ab = vec3_sub(sb->particles[sp->b].pos, sb->particles[sp->a].pos);
		d[0] = vec3_mag(ab);
		if (d[0] < 1e-9)
			continue ;
		d[1] = sp->stiffness * (d[0] - sp->rest_len);
		rv = vec3_sub(sb->particles[sp->b].vel, sb->particles[sp->a].vel);
		d[1] += sp->damping * vec3_dot(rv, vec3_scale(ab, 1.0 / d[0]));
		if (sb->particles[sp->a].inv_mass > 0.0)
			sb->particles[sp->a].force = vec3_add(sb->particles[sp->a].force,
					vec3_scale(ab, d[1] / d[0]));
		if (sb->particles[sp->b].inv_mass > 0.0)
			sb->particles[sp->b].force = vec3_sub(sb->particles[sp->b].force,
					vec3_scale(ab, d[1] / d[0]));
	}
}
