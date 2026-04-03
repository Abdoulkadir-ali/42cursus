/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:10:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:27:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static void	handle_negative_s(double *st, double *abcde, double t)
{
	if (t < 0.0 && abcde[3] < 0.0)
	{
		st[0] = clamp_d(-abcde[3] / abcde[0], 0.0, 1.0);
		st[1] = 0.0;
	}
	else
	{
		st[0] = 0.0;
		st[1] = clamp_d(-abcde[4] / abcde[2], 0.0, 1.0);
	}
}

static void	handle_large_det(double *st, double *abcde, double det)
{
	double	s;
	double	t;

	s = abcde[1] * abcde[4] - abcde[2] * abcde[3];
	t = abcde[1] * abcde[3] - abcde[0] * abcde[4];
	if (s < 0.0)
		handle_negative_s(st, abcde, t);
	else if (t < 0.0)
	{
		st[0] = clamp_d(-abcde[3] / abcde[0], 0.0, 1.0);
		st[1] = 0.0;
	}
	else
	{
		st[0] = s / det;
		st[1] = t / det;
	}
}

static void	handle_negative_d(double *abcde, double *st)
{
	double	tmp[3];

	tmp[0] = abcde[1] + abcde[3];
	tmp[1] = abcde[2] + abcde[4];
	if (tmp[1] > tmp[0])
	{
		tmp[2] = abcde[0] - 2.0 * abcde[1] + abcde[2];
		st[0] = clamp_d((tmp[1] - tmp[0]) / tmp[2], 0.0, 1.0);
		st[1] = 1.0 - st[0];
	}
	else
	{
		st[1] = clamp_d(-abcde[4] / abcde[2], 0.0, 1.0);
		st[0] = 0.0;
	}
}

static void	compute_closest_st_more(double *abcde, double *st)
{
	if (abcde[3] < 0.0)
		handle_negative_d(abcde, st);
	else if (abcde[1] + abcde[3] > abcde[1] + abcde[4])
	{
		st[0] = clamp_d((abcde[2] + abcde[4] - abcde[1] - abcde[3])
				/ (abcde[0] - 2.0 * abcde[1] + abcde[2]), 0.0, 1.0);
		st[1] = 1.0 - st[0];
	}
	else
	{
		st[0] = clamp_d(-abcde[4] / abcde[2], 0.0, 1.0);
		st[1] = 0.0;
	}
}

t_vec3	closest_point_on_triangle(t_vec3 p, t_vec3 v0, t_vec3 v1, t_vec3 v2)
{
	double	st[2];
	t_vec3	e[2];
	double	abcde[5];
	double	det;

	e[0] = vec3_sub(v1, v0);
	e[1] = vec3_sub(v2, v0);
	abcde[0] = vec3_dot(e[0], e[0]);
	abcde[1] = vec3_dot(e[0], e[1]);
	abcde[2] = vec3_dot(e[1], e[1]);
	abcde[3] = vec3_dot(e[0], vec3_sub(p, v0));
	abcde[4] = vec3_dot(e[1], vec3_sub(p, v0));
	det = abcde[0] * abcde[2] - abcde[1] * abcde[1];
	if (abcde[1] * abcde[4] - abcde[2] * abcde[3]
		+ abcde[1] * abcde[3] - abcde[0] * abcde[4] < det)
		handle_large_det(st, abcde, det);
	else
		compute_closest_st_more(abcde, st);
	return (vec3_add(v0, vec3_add(vec3_scale(e[0], st[0]),
				vec3_scale(e[1], st[1]))));
}
