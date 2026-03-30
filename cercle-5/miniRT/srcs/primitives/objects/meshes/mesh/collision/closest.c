/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:10:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 17:10:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collision.h"

static void	handle_outside_region(double *st, double a, double d)
{
	st[0] = clamp_d(-d / a, 0.0, 1.0);
	st[1] = 0.0;
}

static void	handle_large_det(double *st, double *abcde, double det)
{
	double	s;
	double	t;

	s = abcde[1] * abcde[4] - abcde[2] * abcde[3];
	t = abcde[1] * abcde[3] - abcde[0] * abcde[4];
	if (s < 0.0)
	{
		if (t < 0.0)
		{
			if (abcde[3] < 0.0)
				handle_outside_region(st, abcde[0], abcde[3]);
			else
			{
				st[0] = 0.0;
				st[1] = clamp_d(-abcde[4] / abcde[2], 0.0, 1.0);
			}
		}
		else
		{
			st[0] = 0.0;
			st[1] = clamp_d(-abcde[4] / abcde[2], 0.0, 1.0);
		}
	}
	else if (t < 0.0)
		handle_outside_region(st, abcde[0], abcde[3]);
	else
	{
		st[0] = s / det;
		st[1] = t / det;
	}
}

static void	handle_edge_det(double *st, double *abcde)
{
	double	numer;
	double	denom;

	if (abcde[1] + abcde[3] > abcde[1] + abcde[4])
	{
		numer = abcde[2] + abcde[4] - abcde[1] - abcde[3];
		denom = abcde[0] - 2.0 * abcde[1] + abcde[2];
		st[0] = clamp_d(numer / denom, 0.0, 1.0);
		st[1] = 1.0 - st[0];
	}
	else
	{
		st[0] = clamp_d(-abcde[4] / abcde[2], 0.0, 1.0);
		st[1] = 0.0;
	}
}

static void	compute_closest_st_more(t_vec3 v[3], double *abcde, double *st)
{
	double	tmp0;
	double	tmp1;
	double	denom;

	if (abcde[3] < 0.0)
	{
		tmp0 = abcde[1] + abcde[3];
		tmp1 = abcde[2] + abcde[4];
		if (tmp1 > tmp0)
		{
			denom = abcde[0] - 2.0 * abcde[1] + abcde[2];
			st[0] = clamp_d((tmp1 - tmp0) / denom, 0.0, 1.0);
			st[1] = 1.0 - st[0];
		}
		else
		{
			st[1] = clamp_d(-abcde[4] / abcde[2], 0.0, 1.0);
			st[0] = 0.0;
		}
	}
	else
		handle_edge_det(st, abcde);
	(void)v;
}

static void	compute_closest_st(t_vec3 v[3], t_vec3 p, double st[2])
{
	t_vec3	e[2];
	t_vec3	v0_p;
	double	abcde[5];
	double	det;

	e[0] = vec3_sub(v[1], v[0]);
	e[1] = vec3_sub(v[2], v[0]);
	v0_p = vec3_sub(p, v[0]);
	abcde[0] = vec3_dot(e[0], e[0]);
	abcde[1] = vec3_dot(e[0], e[1]);
	abcde[2] = vec3_dot(e[1], e[1]);
	abcde[3] = vec3_dot(e[0], v0_p);
	abcde[4] = vec3_dot(e[1], v0_p);
	det = abcde[0] * abcde[2] - abcde[1] * abcde[1];
	if (abcde[1] * abcde[4] - abcde[2] * abcde[3]
		+ abcde[1] * abcde[3] - abcde[0] * abcde[4] < det)
		handle_large_det(st, abcde, det);
	else
		compute_closest_st_more(v, abcde, st);
}

t_vec3	closest_point_on_triangle(t_vec3 p, t_vec3 v0, t_vec3 v1, t_vec3 v2)
{
	double	st[2];
	t_vec3	v[3];
	t_vec3	edge0;
	t_vec3	edge1;

	v[0] = v0;
	v[1] = v1;
	v[2] = v2;
	edge0 = vec3_sub(v1, v0);
	edge1 = vec3_sub(v2, v0);
	compute_closest_st(v, p, st);
	return (vec3_add(v0, vec3_add(vec3_scale(edge0, st[0]),
				vec3_scale(edge1, st[1]))));
}
