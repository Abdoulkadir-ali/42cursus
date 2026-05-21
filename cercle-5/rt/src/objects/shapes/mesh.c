/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 23:27:53 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/24 23:27:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* fdf PATH ORIGIN SCALE ZSCALE R,G,B */
int	parse_fdf(char **t, int n, t_scene *s)
{
	t_vec3	origin;
	t_vec3	color;
	float	scale;
	float	zscale;
	int		ok;

	if (n != 6)
		return (0);
	if (!parse_vec3(t[2], &origin))
		return (0);
	scale = ft_atof_strict(t[3], &ok);
	if (!ok || scale <= 0.0f)
		return (0);
	zscale = ft_atof_strict(t[4], &ok);
	if (!ok)
		return (0);
	if (!parse_color(t[5], &color))
		return (0);
	{
		t_mesh_conf	conf;
		conf.origin = origin;
		conf.rot = v3(0, 0, 0);
		conf.scale = scale;
		conf.zscale = zscale;
		conf.color = color;
		conf.emit = v3(0, 0, 0);
		if (mesh_load_fdf(s, t[1], &conf) < 0)
			return (0);
	}
	return (1);
}

/* glb PATH ORIGIN [ROT_DEG] SCALE COLOR [EMIT]
 *   short:  glb PATH ORIGIN SCALE R,G,B           (n==5)
 *   long :  glb PATH ORIGIN ROT SCALE R,G,B EMIT  (n==7) */
int	parse_glb(char **t, int n, t_scene *s)
{
	t_vec3	origin;
	t_vec3	rot;
	t_vec3	color;
	t_vec3	emit;
	float	scale;
	int		ok;

	if (n != 5 && n != 6 && n != 7)
		return (0);
	if (!parse_vec3(t[2], &origin))
		return (0);
	if (n == 5)
	{
		rot = v3(0, 0, 0);
		emit = v3(0, 0, 0);
		scale = ft_atof_strict(t[3], &ok);
		if (!ok || scale <= 0.0f)
			return (0);
		if (!parse_color(t[4], &color))
			return (0);
	}
	else
	{
		if (!parse_vec3(t[3], &rot))
			return (0);
		scale = ft_atof_strict(t[4], &ok);
		if (!ok || scale <= 0.0f)
			return (0);
		if (!parse_color(t[5], &color))
			return (0);
		if (n == 7)
		{
			if (!parse_color(t[6], &emit))
				return (0);
		}
		else
			emit = v3(0, 0, 0);
	}
	{
		t_mesh_conf	conf;
		conf.origin = origin;
		conf.rot = rot;
		conf.scale = scale;
		conf.zscale = 1.0f;
		conf.color = color;
		conf.emit = emit;
		if (mesh_load_glb(s, t[1], &conf) < 0)
			return (0);
	}
	return (1);
}
