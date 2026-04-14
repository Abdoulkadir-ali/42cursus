/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wind.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 13:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "particles.h"

static double	turb_layer(t_vec3 p, double scale, double weight)
{
	return (value_noise3(p.x * scale, p.y * scale, p.z * scale) * weight);
}

static t_vec3	turbulence_offset(t_vec3 pos, double freq, double amp)
{
	t_vec3	offset;
	t_vec3	p;

	p = vec3_scale(pos, freq);
	offset.x = turb_layer(p, 1.0, amp);
	offset.y = turb_layer(vec3_add(p, vec3(10, 10, 10)), 1.0, amp);
	offset.z = turb_layer(vec3_add(p, vec3(20, 20, 20)), 1.0, amp);
	return (offset);
}

t_vec3	wind_accel_at(t_vec3 pos, const t_physics_settings *s)
{
	t_vec3	turb;
	t_vec3	final_wind;

	turb = turbulence_offset(pos, 0.1, s->wind_turbulence);
	final_wind = vec3_add(s->wind, turb);
	return (final_wind);
}

void	apply_wind_to_physics_body(t_physics_body *b,
			const t_physics_settings *s, double dt)
{
	t_vec3	w;

	if (b->is_static)
		return ;
	w = wind_accel_at(b->pos, s);
	b->velocity = vec3_add(b->velocity, vec3_scale(w, dt));
}

void	apply_wind_pass(t_scene *scene, t_physics_settings *s, double dt)
{
	if (!scene || vec3_mag_sq(s->wind) < 1e-6)
		return ;
	apply_wind_vols(scene, s, dt);
	apply_wind_surfs(scene, s, dt);
	apply_wind_to_soft_bodies(scene, s);
	apply_wind_to_particles(scene->psoa, s, dt);
}
