/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particles.h"
#include <math.h>

static void	get_bb_stops(t_blackbody_stop s[BB_STOP_COUNT])
{
	s[0].stop = 0.0;
	s[0].color = vec3(0, 0, 0);
	s[1].stop = 0.15;
	s[1].color = vec3(160, 15, 0);
	s[2].stop = 0.4;
	s[2].color = vec3(255, 90, 0);
	s[3].stop = 0.7;
	s[3].color = vec3(255, 200, 40);
	s[4].stop = 1.0;
	s[4].color = vec3(255, 245, 210);
}

t_vec3	blackbody_color(double t)
{
	t_blackbody_stop	s[BB_STOP_COUNT];
	int					i;
	double				f;

	get_bb_stops(s);
	i = 0;
	while (i < 3 && t > s[i + 1].stop)
		i++;
	f = (t - s[i].stop) / (s[i + 1].stop - s[i].stop + 1e-9);
	return (vec3(
			s[i].color.x + (s[i + 1].color.x - s[i].color.x) * f,
			s[i].color.y + (s[i + 1].color.y - s[i].color.y) * f,
			s[i].color.z + (s[i + 1].color.z - s[i].color.z) * f));
}

void	init_proxy_spheres(t_scene *scene)
{
	t_sphere	sp;
	size_t		i;
	t_index		idx;

	scene->proxy_sphere_base = scene->sphere_count;
	scene->proxy_mat_base = scene->mat_count;
	i = -1;
	while (++i < MAX_PROXY_SPHERES)
	{
		ft_memset(&sp, 0, sizeof(sp));
		sp.transform.scale = vec3(1.0, 1.0, 1.0);
		sp.inv_scale = vec3(1.0, 1.0, 1.0);
		sp.phys.is_static = true;
		idx = scene_add_fresh_material(scene, vec3(0, 0, 0));
		sp.mat_id = idx.i;
		sp.mat_slots[0] = idx.i;
		sp.mat_slots[1] = scene->mat_slot_checker;
		sp.mat_slots[2] = scene->mat_slot_solid;
		if (scene_allocate_object_slot((void **)&scene->spheres,
				&scene->sphere_count, &scene->sphere_cap, sizeof(sp)).error)
			break ;
		scene->spheres[scene->sphere_count - 1] = sp;
	}
	scene->proxy_sphere_count = i;
	scene->psoa_ready = true;
}

static void	write_proxy(t_scene *sc, size_t i, t_particle_soa *soa)
{
	t_sphere	*sp;
	t_material	*mat;
	t_vec3		col;

	sp = &sc->spheres[sc->proxy_sphere_base + i];
	sp->transform.pos.x = soa->px[i];
	sp->transform.pos.y = soa->py[i];
	sp->transform.pos.z = soa->pz[i];
	sp->phys.pos = sp->transform.pos;
	sp->phys.center = sp->transform.pos;
	sp->radius_sq = soa->size[i] * soa->size[i];
	col = blackbody_color(soa->temp[i]);
	mat = &sc->materials[sc->proxy_mat_base + i];
	mat->albedo_map.color_a = col;
	mat->albedo_map.type = TEX_SOLID;
	mat->emission = col;
	mat->em_intensity = soa->temp[i] * 4.0;
}

void	update_proxy_spheres(t_scene *scene)
{
	t_particle_soa	*soa;
	size_t			n;
	size_t			i;

	soa = scene->psoa;
	if (soa->alive < scene->proxy_sphere_count)
		n = soa->alive;
	else
		n = scene->proxy_sphere_count;
	i = 0;
	while (i < n)
		write_proxy(scene, i++, soa);
	while (i < scene->proxy_sphere_count)
	{
		scene->spheres[scene->proxy_sphere_base + i].radius_sq = 0.0;
		scene->materials[scene->proxy_mat_base + i].emission = vec3(0, 0, 0);
		scene->materials[scene->proxy_mat_base + i].em_intensity = 0.0;
		i++;
	}
}
