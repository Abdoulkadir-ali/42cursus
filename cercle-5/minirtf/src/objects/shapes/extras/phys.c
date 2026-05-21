/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:53:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:53:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_g_const(char **t, int n, t_scene *s)
{
	int		ok;
	float	v;

	(void)s;
	if (n != 2)
		return (0);
	v = ft_atof_strict(t[1], &ok);
	if (!ok || v < 0.0f || v > 1e12f)
		return (0);
	return (1);
}

int	parse_damp(char **t, int n, t_scene *s)
{
	int		ok;
	float	v;

	(void)s;
	if (n != 2)
		return (0);
	v = ft_atof_strict(t[1], &ok);
	if (!ok || v < 0.0f || v > 100.0f)
		return (0);
	return (1);
}

int	parse_phys(char **t, int n, t_scene *s)
{
	int		ok;
	float	f;
	t_vec3	v;

	(void)s;
	if (n < 3)
		return (0);
	if (!strcmp(t[1], "mass") && n == 3)
	{
		f = ft_atof_strict(t[2], &ok);
		return (ok && f >= 0.0f && f <= 1e15f);
	}
	if (!strcmp(t[1], "static") && n == 3)
	{
		f = ft_atof_strict(t[2], &ok);
		return (ok && (f == 0.0f || f == 1.0f));
	}
	if (!strcmp(t[1], "vel") && n == 3)
		return (parse_vec3(t[2], &v));
	if (!strcmp(t[1], "rest") && n == 3)
	{
		f = ft_atof_strict(t[2], &ok);
		return (ok && f >= 0.0f && f <= 1.0f);
	}
	return (0);
}

int	parse_mass(char **t, int n, t_scene *s)
{
	int		ok;
	float	f;

	(void)s;
	if (n != 2)
		return (0);
	f = ft_atof_strict(t[1], &ok);
	return (ok && f >= 0.0f && f <= 1e15f);
}

int	parse_vel(char **t, int n, t_scene *s)
{
	t_vec3	v;

	(void)s;
	if (n != 2)
		return (0);
	return (parse_vec3(t[1], &v));
}

int	parse_pe(char **t, int n, t_scene *s)
{
	t_vec3	v;
	int		i;
	int		ok;
	float	f;

	(void)s;
	if (n != 11)
		return (0);
	if (!parse_vec3(t[1], &v) || !parse_unit_vec3(t[2], &v))
		return (0);
	i = 3;
	while (i < 11)
	{
		f = ft_atof_strict(t[i], &ok);
		if (!ok || f < 0.0f || f > 1e9f)
			return (0);
		i++;
	}
	return (1);
}

int	parse_bhole(char **t, int n, t_scene *s)
{
	char	*sub[3];
	float	mass;
	float	rs;
	int		ok;
	char	rsbuf[64];

	if (n != 3)
		return (0);
	mass = ft_atof_strict(t[2], &ok);
	if (!ok || mass <= 0.0f || mass > 1e18f)
		return (0);
	rs = 2e-8f * mass;
	if (rs < 0.001f)
		rs = 0.001f;
	if (rs > 1e6f)
		rs = 1e6f;
	snprintf(rsbuf, sizeof(rsbuf), "%g", (double)rs);
	sub[0] = (char *)"bh";
	sub[1] = t[1];
	sub[2] = rsbuf;
	return (parse_blackhole(sub, 3, s));
}

int	parse_sb(char **t, int n, t_scene *s)
{
	int		ok;
	float	stiff;
	float	damp;
	t_vec3	pos;

	(void)s;
	if (n != 5)
		return (0);
	stiff = ft_atof_strict(t[2], &ok);
	if (!ok || stiff < 0.0f || stiff > 1e6f)
		return (0);
	damp = ft_atof_strict(t[3], &ok);
	if (!ok || damp < 0.0f || damp > 1e6f)
		return (0);
	if (!parse_vec3(t[4], &pos))
		return (0);
	(void)t;
	return (1);
}
