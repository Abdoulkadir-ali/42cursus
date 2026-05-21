/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/25 03:21:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "core.h"

int	parse_gravity(char **t, int n, t_scene *s)
{
	t_vec3	g;

	if (n != 2)
		return (0);
	if (!parse_vec3(t[1], &g))
		return (0);
	s->gravity = g;
	return (1);
}

static t_blackhole	*scene_push_bh(t_scene *s)
{
	t_blackhole	*tmp;
	size_t		cap;

	if (s->n_bhs + 1 > s->cap_bhs)
	{
		cap = s->cap_bhs ? s->cap_bhs * 2 : 4;
		tmp = (t_blackhole *)realloc(s->bhs, sizeof(t_blackhole) * cap);
		if (!tmp)
			return (NULL);
		s->bhs = tmp;
		s->cap_bhs = cap;
	}
	return (&s->bhs[s->n_bhs++]);
}

int	parse_blackhole(char **t, int n, t_scene *s)
{
	t_blackhole	*bh;
	int			ok;

	if (n != 3 && n != 5)
		return (0);
	bh = scene_push_bh(s);
	if (!bh)
		return (0);
	if (!parse_vec3(t[1], &bh->pos))
		return (0);
	bh->rs = ft_atof_strict(t[2], &ok);
	if (!ok || bh->rs <= 0.0f || bh->rs > 1e6f)
		return (0);
	bh->lens_strength = 1.0f;
	bh->grav_strength = 1.0f;
	if (n == 5)
	{
		bh->lens_strength = ft_atof_strict(t[3], &ok);
		if (!ok || bh->lens_strength < 0.0f || bh->lens_strength > 100.0f)
			return (0);
		bh->grav_strength = ft_atof_strict(t[4], &ok);
		if (!ok || bh->grav_strength < 0.0f || bh->grav_strength > 100.0f)
			return (0);
	}
	return (1);
}

/* dyn IDX MASS REST VX,VY,VZ
 * IDX = sphere index in bvh order (or -1 = last sphere) */
int	parse_dyn(char **t, int n, t_scene *s, t_phys_world *w)
{
	int		idx;
	float	mass;
	float	rest;
	t_vec3	vel;
	int		ok;

	if (n != 5)
		return (0);
	idx = ft_atoi_strict(t[1], &ok);
	if (!ok)
		return (0);
	if (idx < 0)
		idx = (int)s->n_bvh - 1;
	if (idx < 0 || (size_t)idx >= s->n_bvh)
		return (0);
	mass = ft_atof_strict(t[2], &ok);
	if (!ok || mass < 0.0f || mass > 1e9f)
		return (0);
	rest = ft_atof_strict(t[3], &ok);
	if (!ok || rest < 0.0f || rest > 1.0f)
		return (0);
	if (!parse_vec3(t[4], &vel))
		return (0);
	if (phys_add_body(w, idx, mass, rest, vel) < 0)
		return (0);
	w->enabled = 1;
	return (1);
}