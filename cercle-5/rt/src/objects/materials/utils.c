/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 02:22:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	mat_init_default(t_material *m, t_vec3 albedo)
{
	memset(m, 0, sizeof(*m));
	m->albedo = albedo;
	m->ks = 0.2f;
	m->shininess = 32.0f;
	m->reflectivity = 0.0f;
	m->tex_id = -1;
	m->emit_tex_id = -1;
	m->roughness = 0.6f;
	m->metallic = 0.0f;
	m->opacity = 1.0f;
	m->ior = 1.5f;
	m->emit_color = (t_vec3){0, 0, 0};
	m->emit_power = 0.0f;
	m->name[0] = '\0';
}

t_object	*scene_push_bvh(t_scene *s)
{
	t_object	*tmp;
	int			new_cap;

	if (s->n_bvh >= s->cap_bvh)
	{
		new_cap = s->cap_bvh * 2;
		tmp = (t_object *)realloc(s->bvh_objs, sizeof(t_object) * new_cap);
		if (!tmp)
			return (NULL);
		s->bvh_objs = tmp;
		s->cap_bvh = new_cap;
	}
	memset(&s->bvh_objs[s->n_bvh], 0, sizeof(t_object));
	return (&s->bvh_objs[s->n_bvh++]);
}

t_object	*scene_push_plane(t_scene *s)
{
	t_object	*tmp;
	int			new_cap;

	if (s->n_planes >= s->cap_planes)
	{
		new_cap = s->cap_planes * 2;
		tmp = (t_object *)realloc(s->planes, sizeof(t_object) * new_cap);
		if (!tmp)
			return (NULL);
		s->planes = tmp;
		s->cap_planes = new_cap;
	}
	memset(&s->planes[s->n_planes], 0, sizeof(t_object));
	return (&s->planes[s->n_planes++]);
}

t_light	*scene_push_light(t_scene *s)
{
	t_light	*tmp;
	int		new_cap;

	if (s->n_lights >= s->cap_lights)
	{
		new_cap = s->cap_lights * 2;
		tmp = (t_light *)realloc(s->lights, sizeof(t_light) * new_cap);
		if (!tmp)
			return (NULL);
		s->lights = tmp;
		s->cap_lights = new_cap;
	}
	memset(&s->lights[s->n_lights], 0, sizeof(t_light));
	return (&s->lights[s->n_lights++]);
}
