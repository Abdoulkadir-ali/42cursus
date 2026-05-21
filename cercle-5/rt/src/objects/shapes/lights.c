/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 02:43:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_ambient(char **t, int n, t_scene *s)
{
	int	ok;

	if (n != 3 || s->amb.set)
		return (0);
	s->amb.ratio = ft_atof_strict(t[1], &ok);
	if (!ok || s->amb.ratio < 0.0f || s->amb.ratio > 1.0f)
		return (0);
	if (!parse_color(t[2], &s->amb.color))
		return (0);
	s->amb.set = 1;
	return (1);
}

int	parse_camera(char **t, int n, t_scene *s)
{
	int	ok;

	if (n != 4 || s->cam_set)
		return (0);
	if (!parse_vec3(t[1], &s->cam.pos) || !parse_unit_vec3(t[2], &s->cam.dir))
		return (0);
	s->cam.fov = ft_atof_strict(t[3], &ok);
	if (!ok || s->cam.fov <= 0.0f || s->cam.fov >= 180.0f)
		return (0);
	s->cam.aperture = 0.0f;
	s->cam.fdist = 10.0f;
	s->cam_set = 1;
	return (1);
}

static void	finalize_light(t_light *l)
{
	if (l->ratio > 1.0f)
	{
		l->color = v3_mul(l->color, l->ratio);
		l->ratio = 1.0f;
	}
}

int	parse_light(char **t, int n, t_scene *s)
{
	t_light	*l;
	int		ok;

	if (n < 3 || n > 4)
		return (0);
	l = scene_push_light(s);
	if (!l || !parse_vec3(t[1], &l->pos))
		return (0);
	l->ratio = ft_atof_strict(t[2], &ok);
	if (!ok || l->ratio < 0.0f || l->ratio > 100000.0f)
		return (0);
	if (n == 4)
	{
		if (!parse_color(t[3], &l->color))
			return (0);
	}
	else
		l->color = v3(1.0f, 1.0f, 1.0f);
	finalize_light(l);
	return (1);
}