/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gjk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/08 19:42:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/*
** GJK — Gilbert-Johnson-Keerthi collision detection.
**
** We work in Minkowski-difference space: each simplex point is
**   support_A(dir) - support_B(-dir)
**
** The simplex is stored in s->pts[4], s->n tracks how many points we have.
** After a successful (overlapping) return the simplex is fed to EPA.
*/

# define GJK_MAX_ITER 20

/* Minkowski-difference support */
static t_vec3	md_support(t_gjk_shape *a, t_gjk_shape *b, t_vec3 dir,
		t_vec3 *pa, t_vec3 *pb)
{
	*pa = a->support(a->data, dir);
	*pb = b->support(b->data, vec3_scale(dir, -1.0));
	return (vec3_sub(*pa, *pb));
}

/* ── Line case ─────────────────────────────────────────────────────────── */
static bool	simplex_line(t_simplex *s, t_vec3 *dir)
{
	t_vec3	b;
	t_vec3	a;
	t_vec3	ab;
	t_vec3	ao;
	t_vec3	ref;

	a = s->pts[1];
	b = s->pts[0];
	ab = vec3_sub(b, a);
	ao = vec3_scale(a, -1.0);
	if (vec3_dot(ab, ao) > 0.0)
	{
		/* Triple product (AB × AO) × AB = AO*||AB||² - AB*dot(AO,AB) */
		*dir = vec3_sub(vec3_scale(ao, vec3_dot(ab, ab)),
				vec3_scale(ab, vec3_dot(ao, ab)));
		/* Degenerate: origin ON the segment (e.g. aligned spheres).
		** Pick any perpendicular to AB so GJK can build a triangle. */
		if (vec3_mag_sq(*dir) < 1e-12)
		{
			ref = (fabs(ab.x) < 0.9) ? vec3(1, 0, 0) : vec3(0, 1, 0);
			*dir = vec3_cross(ab, ref);
		}
	}
	else
	{
		s->pts[0] = a;
		s->a_pts[0] = s->a_pts[1];
		s->b_pts[0] = s->b_pts[1];
		s->n = 1;
		*dir = ao;
	}
	return (false);
}

/* ── Triangle case ──────────────────────────────────────────────────────── */
static bool	simplex_triangle(t_simplex *s, t_vec3 *dir)
{
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;
	t_vec3	ab;
	t_vec3	ac;
	t_vec3	ao;
	t_vec3	abc;

	a = s->pts[2];
	b = s->pts[1];
	c = s->pts[0];
	ab = vec3_sub(b, a);
	ac = vec3_sub(c, a);
	ao = vec3_scale(a, -1.0);
	abc = vec3_cross(ab, ac);
	if (vec3_dot(vec3_cross(abc, ac), ao) > 0.0)
	{
		if (vec3_dot(ac, ao) > 0.0)
		{
			s->pts[1] = a;
			s->a_pts[1] = s->a_pts[2];
			s->b_pts[1] = s->b_pts[2];
			s->n = 2;
			/* (AC × AO) × AC = AO*||AC||² - AC*dot(AO,AC) */
			*dir = vec3_sub(vec3_scale(ao, vec3_dot(ac, ac)),
					vec3_scale(ac, vec3_dot(ao, ac)));
		}
		else
		{
			s->pts[0] = b;
			s->pts[1] = a;
			s->a_pts[0] = s->a_pts[1];
			s->a_pts[1] = s->a_pts[2];
			s->b_pts[0] = s->b_pts[1];
			s->b_pts[1] = s->b_pts[2];
			s->n = 2;
			/* (AB × AO) × AB = AO*||AB||² - AB*dot(AO,AB) */
			*dir = vec3_sub(vec3_scale(ao, vec3_dot(ab, ab)),
					vec3_scale(ab, vec3_dot(ao, ab)));
		}
		return (false);
	}
	if (vec3_dot(vec3_cross(ab, abc), ao) > 0.0)
	{
		s->pts[0] = b;
		s->pts[1] = a;
		s->a_pts[0] = s->a_pts[1];
		s->a_pts[1] = s->a_pts[2];
		s->b_pts[0] = s->b_pts[1];
		s->b_pts[1] = s->b_pts[2];
		s->n = 2;
		/* (AB × AO) × AB = AO*||AB||² - AB*dot(AO,AB) */
		*dir = vec3_sub(vec3_scale(ao, vec3_dot(ab, ab)),
				vec3_scale(ab, vec3_dot(ao, ab)));
		return (false);
	}
	if (vec3_dot(abc, ao) > 0.0)
		*dir = abc;
	else
	{
		t_vec3	tmp;
		tmp = s->pts[0];
		s->pts[0] = s->pts[1];
		s->pts[1] = tmp;
		tmp = s->a_pts[0]; s->a_pts[0] = s->a_pts[1]; s->a_pts[1] = tmp;
		tmp = s->b_pts[0]; s->b_pts[0] = s->b_pts[1]; s->b_pts[1] = tmp;
		*dir = vec3_scale(abc, -1.0);
	}
	return (false);
}

/* ── Tetrahedron case ───────────────────────────────────────────────────── */
static bool	same_dir(t_vec3 v, t_vec3 dir)
{
	return (vec3_dot(v, dir) > 0.0);
}

static void	set_simplex3(t_simplex *s, t_vec3 a, t_vec3 b, t_vec3 c,
		int ia, int ib, int ic)
{
	t_vec3	sav_a;
	t_vec3	sav_b;
	t_vec3	sav_c;
	t_vec3	sbv_a;
	t_vec3	sbv_b;
	t_vec3	sbv_c;

	/* Save originals before any in-place write to avoid aliasing */
	sav_a = s->a_pts[ia];
	sav_b = s->a_pts[ib];
	sav_c = s->a_pts[ic];
	sbv_a = s->b_pts[ia];
	sbv_b = s->b_pts[ib];
	sbv_c = s->b_pts[ic];
	s->pts[0] = c;
	s->pts[1] = b;
	s->pts[2] = a;
	s->a_pts[0] = sav_c;
	s->a_pts[1] = sav_b;
	s->a_pts[2] = sav_a;
	s->b_pts[0] = sbv_c;
	s->b_pts[1] = sbv_b;
	s->b_pts[2] = sbv_a;
	s->n = 3;
}

static bool	simplex_tetrahedron(t_simplex *s, t_vec3 *dir)
{
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;
	t_vec3	d;
	t_vec3	ab;
	t_vec3	ac;
	t_vec3	ad;
	t_vec3	ao;
	t_vec3	abc;
	t_vec3	acd;
	t_vec3	adb;

	a = s->pts[3];
	b = s->pts[2];
	c = s->pts[1];
	d = s->pts[0];
	ab = vec3_sub(b, a);
	ac = vec3_sub(c, a);
	ad = vec3_sub(d, a);
	ao = vec3_scale(a, -1.0);
	abc = vec3_cross(ab, ac);
	acd = vec3_cross(ac, ad);
	adb = vec3_cross(ad, ab);
	if (same_dir(abc, ao))
	{
		set_simplex3(s, a, b, c, 3, 2, 1);
		return (simplex_triangle(s, dir));
	}
	if (same_dir(acd, ao))
	{
		set_simplex3(s, a, c, d, 3, 1, 0);
		return (simplex_triangle(s, dir));
	}
	if (same_dir(adb, ao))
	{
		set_simplex3(s, a, d, b, 3, 0, 2);
		return (simplex_triangle(s, dir));
	}
	return (true);
}

static bool	next_simplex(t_simplex *s, t_vec3 *dir)
{
	if (s->n == 2)
		return (simplex_line(s, dir));
	if (s->n == 3)
		return (simplex_triangle(s, dir));
	return (simplex_tetrahedron(s, dir));
}

bool	gjk_intersect(t_gjk_shape *a, t_gjk_shape *b, t_simplex *out)
{
	t_simplex	s;
	t_vec3		dir;
	t_vec3		pt;
	t_vec3		pa;
	t_vec3		pb;
	int			iter;

	s.n = 0;
	dir = vec3_sub(b->center, a->center);
	if (vec3_mag_sq(dir) < 1e-9)
		dir = vec3(1, 0, 0);
	pt = md_support(a, b, dir, &pa, &pb);
	s.pts[0] = pt;
	s.a_pts[0] = pa;
	s.b_pts[0] = pb;
	s.n = 1;
	dir = vec3_scale(pt, -1.0);
	iter = 0;
	while (iter < GJK_MAX_ITER)
	{
		if (vec3_mag_sq(dir) < 1e-12)
			break ;
		pt = md_support(a, b, dir, &pa, &pb);
		if (vec3_dot(pt, dir) < 0.0)
			return (false);
		s.pts[s.n] = pt;
		s.a_pts[s.n] = pa;
		s.b_pts[s.n] = pb;
		s.n++;
		if (next_simplex(&s, &dir))
		{
			*out = s;
			return (true);
		}
		iter++;
	}
	/* Did not enclose origin — no confirmed collision */
	return (false);
}
