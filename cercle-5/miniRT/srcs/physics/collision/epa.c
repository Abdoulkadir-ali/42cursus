/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 15:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

t_vec3	bary(const t_vec3 tri[3], t_vec3 p)
{
	t_vec3	v01;
	t_vec3	v02;
	t_vec3	v0p;
	double	d[6];
	double	denom;

	v01 = vec3_sub(tri[1], tri[0]);
	v02 = vec3_sub(tri[2], tri[0]);
	v0p = vec3_sub(p, tri[0]);
	d[0] = vec3_dot(v01, v01);
	d[1] = vec3_dot(v01, v02);
	d[2] = vec3_dot(v02, v02);
	d[3] = vec3_dot(v0p, v01);
	d[4] = vec3_dot(v0p, v02);
	denom = d[0] * d[2] - d[1] * d[1];
	if (fabs(denom) < 1e-12)
		return ((t_vec3){1, 0, 0, 0});
	d[5] = (d[2] * d[3] - d[1] * d[4]) / denom;
	denom = (d[0] * d[4] - d[1] * d[3]) / denom;
	return ((t_vec3){1.0 - d[5] - denom, d[5], denom, 0});
}

void	init_polytope(t_epa_poly *p, t_simplex *s)
{
	p->n_verts = 4;
	p->n_faces = 0;
	memcpy(p->pts, s->pts, sizeof(t_vec3) * 4);
	memcpy(p->a_pts, s->a_pts, sizeof(t_vec3) * 4);
	memcpy(p->b_pts, s->b_pts, sizeof(t_vec3) * 4);
	push_face(p, 0, 1, 2);
	push_face(p, 0, 2, 3);
	push_face(p, 0, 3, 1);
	push_face(p, 1, 3, 2);
}

void	get_contact_points(t_epa_poly *p, t_epa_face *f, t_vec3 *ca, t_vec3 *cb)
{
	t_vec3	ba;
	t_vec3	v[3];

	v[0] = p->pts[f->idx[0]];
	v[1] = p->pts[f->idx[1]];
	v[2] = p->pts[f->idx[2]];
	ba = bary(v, vec3_mul(f->normal, f->dist));
	*ca = vec3_add(vec3_mul(p->a_pts[f->idx[0]], ba.x),
			vec3_add(vec3_mul(p->a_pts[f->idx[1]], ba.y),
				vec3_mul(p->a_pts[f->idx[2]], ba.z)));
	*cb = vec3_add(vec3_mul(p->b_pts[f->idx[0]], ba.x),
			vec3_add(vec3_mul(p->b_pts[f->idx[1]], ba.y),
				vec3_mul(p->b_pts[f->idx[2]], ba.z)));
}

/**
 * @brief Finds the face on the current polytope closest to the origin.
 */
int	closest_face(t_epa_poly *p)
{
	int		idx;
	int		i;
	double	min_dist;

	idx = 0;
	min_dist = 1e30;
	i = 0;
	while (i < p->n_faces)
	{
		if (p->faces[i].dist < min_dist)
		{
			min_dist = p->faces[i].dist;
			idx = i;
		}
		i++;
	}
	return (idx);
}

/**
 * @brief Creates a new face for the EPA polytope and computes its plane.
 */
t_epa_face	make_face(t_epa_poly *p, int i0, int i1, int i2)
{
	t_epa_face	f;
	t_vec3		v0;
	t_vec3		v1;
	t_vec3		v2;

	f.idx[0] = i0;
	f.idx[1] = i1;
	f.idx[2] = i2;
	v0 = p->pts[i0];
	v1 = p->pts[i1];
	v2 = p->pts[i2];
	f.normal = vec3_unit(vec3_cross(vec3_sub(v1, v0), vec3_sub(v2, v0)));
	f.dist = vec3_dot(f.normal, v0);
	if (f.dist < 0)
	{
		f.normal = vec3_mul(f.normal, -1);
		f.dist = -f.dist;
	}
	return (f);
}

/**
 * @brief Adds a point to the polytope and updates the silhouette boundary.
 */
static void	push_face(t_epa_poly *p, int i0, int i1, int i2)
{
	if (p->n_faces >= EPA_MAX_FACES) return ;
	p->faces[p->n_faces++] = make_face(p, i0, i1, i2);
}

static void	add_edge(t_edge *edges, int *n, int a, int b)
{
	int	i;

	i = 0;
	while (i < *n)
	{
		if (edges[i].a == b && edges[i].b == a)
		{
			edges[i] = edges[--(*n)];
			return ;
		}
		i++;
	}
	edges[(*n)].a = a;
	edges[(*n)++].b = b;
}

static void	expand(t_epa_poly *p, int cf, t_vec3 pt, t_vec3 pa, t_vec3 pb)
{
	t_edge	edges[EPA_MAX_FACES * 3];
	int		ne;
	int		i;
	int		pidx;

	ne = 0;
	pidx = p->n_verts;
	p->pts[p->n_verts] = pt;
	p->a_pts[p->n_verts] = pa;
	p->b_pts[p->n_verts++] = pb;
	i = 0;
	while (i < p->n_faces)
	{
		if (vec3_dot(p->faces[i].normal, vec3_sub(pt, p->pts[p->faces[i].idx[0]])) > 0)
		{
			add_edge(edges, &ne, p->faces[i].idx[0], p->faces[i].idx[1]);
			add_edge(edges, &ne, p->faces[i].idx[1], p->faces[i].idx[2]);
			add_edge(edges, &ne, p->faces[i].idx[2], p->faces[i].idx[0]);
			p->faces[i] = p->faces[--p->n_faces];
			continue ;
		}
		i++;
	}
	i = 0;
	while (i < ne)
	{
		push_face(p, edges[i].a, edges[i].b, pidx);
		i++;
	}
}

/**
 * @brief Core EPA Solver entry. Expands the Minkowski simplex until convergence.
 */
bool	gjk_epa(t_gjk_shape *a, t_gjk_shape *b, t_simplex *s, t_epa_res *res)
{
	t_epa_poly	poly;
	int			cf;
	t_vec3		p;
	t_vec3		pa;
	t_vec3		pb;
	int			iter;

	init_polytope(&poly, s);
	iter = 0;
	while (iter < EPA_MAX_ITER)
	{
		cf = closest_face(&poly);
		p = md_support(a, b, poly.faces[cf].normal, &pa, &pb);
		if (vec3_dot(poly.faces[cf].normal, p) - poly.faces[cf].dist < EPA_TOL)
		{
			res->normal = poly.faces[cf].normal;
			res->depth = poly.faces[cf].dist;
			get_contact_points(&poly, &poly.faces[cf], &res->contact_a, &res->contact_b);
			return (true);
		}
		expand(&poly, cf, p, pa, pb);
		iter++;
	}
	return (false);
}
