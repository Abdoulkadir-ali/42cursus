/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/08 19:42:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/*
** EPA — Expanding Polytope Algorithm.
**
** Starts from the GJK tetrahedron simplex and iteratively expands it
** toward the Minkowski-difference boundary to find the minimum-translation
** direction (MTD) — i.e., the collision normal and penetration depth.
**
** Polytope representation: list of triangular faces, each face defined by
** three indices into a vertex list (pts[]).  We track support A/B points
** for barycentric contact generation.
*/

# define EPA_MAX_ITER   30
# define EPA_MAX_FACES  64
# define EPA_MAX_VERTS  32
# define EPA_TOL        1e-5

typedef struct s_epa_face
{
	int		idx[3];
	t_vec3	normal;
	double	dist;
}	t_epa_face;

typedef struct s_epa_poly
{
	t_vec3		pts[EPA_MAX_VERTS];
	t_vec3		a_pts[EPA_MAX_VERTS];
	t_vec3		b_pts[EPA_MAX_VERTS];
	int			n_verts;
	t_epa_face	faces[EPA_MAX_FACES];
	int			n_faces;
}	t_epa_poly;

/* ── Face normal that points outward from origin ─────────────────────── */
static t_epa_face	make_face(t_epa_poly *p, int i0, int i1, int i2)
{
	t_epa_face	f;
	t_vec3		e0;
	t_vec3		e1;
	t_vec3		n;
	double		len;

	f.idx[0] = i0;
	f.idx[1] = i1;
	f.idx[2] = i2;
	e0 = vec3_sub(p->pts[i1], p->pts[i0]);
	e1 = vec3_sub(p->pts[i2], p->pts[i0]);
	n = vec3_cross(e0, e1);
	len = vec3_mag(n);
	if (len < 1e-12)
	{
		f.normal = vec3(0, 1, 0);
		f.dist = 0.0;
		return (f);
	}
	f.normal = vec3_scale(n, 1.0 / len);
	f.dist = vec3_dot(f.normal, p->pts[i0]);
	if (f.dist < 0.0)
	{
		f.normal = vec3_scale(f.normal, -1.0);
		f.dist = -f.dist;
	}
	return (f);
}

/* ── Build initial polytope from 4-simplex ────────────────────────────── */
static void	init_polytope(t_epa_poly *p, t_simplex *s)
{
	int	i;

	i = 0;
	while (i < s->n && i < EPA_MAX_VERTS)
	{
		p->pts[i] = s->pts[i];
		p->a_pts[i] = s->a_pts[i];
		p->b_pts[i] = s->b_pts[i];
		i++;
	}
	p->n_verts = s->n;
	p->n_faces = 0;
	if (s->n == 4)
	{
		p->faces[0] = make_face(p, 0, 1, 2);
		p->faces[1] = make_face(p, 0, 1, 3);
		p->faces[2] = make_face(p, 0, 2, 3);
		p->faces[3] = make_face(p, 1, 2, 3);
		p->n_faces = 4;
	}
	else if (s->n == 3)
	{
		p->faces[0] = make_face(p, 0, 1, 2);
		p->faces[1] = make_face(p, 0, 2, 1);
		p->n_faces = 2;
	}
}

/* ── Pick face closest to origin ──────────────────────────────────────── */
static int	closest_face(t_epa_poly *p)
{
	int		best;
	double	best_d;
	int		i;

	best = 0;
	best_d = p->faces[0].dist;
	i = 1;
	while (i < p->n_faces)
	{
		if (p->faces[i].dist < best_d)
		{
			best_d = p->faces[i].dist;
			best = i;
		}
		i++;
	}
	return (best);
}

/* ── Edge silhouette: collect edges visible from new point ────────────── */
typedef struct s_edge
{
	int	a;
	int	b;
}	t_edge;

/*
** Remove and expose the silhouette edges.
** Faces visible from 'pt' are removed; their edges become candidate silhouette
** edges. An edge shared by two visible faces cancels itself.
*/
static int	collect_silhouette(t_epa_poly *p, t_vec3 pt,
		t_edge *edges, int *n_edges)
{
	bool	removed[EPA_MAX_FACES];
	int		i;
	int		j;
	int		n;
	t_edge	e;

	n = 0;
	i = 0;
	while (i < p->n_faces)
	{
		removed[i] = false;
		i++;
	}
	i = 0;
	while (i < p->n_faces)
	{
		if (vec3_dot(p->faces[i].normal,
				vec3_sub(pt, p->pts[p->faces[i].idx[0]])) > 0.0)
		{
			removed[i] = true;
			j = 0;
			while (j < 3)
			{
				e.a = p->faces[i].idx[j];
				e.b = p->faces[i].idx[(j + 1) % 3];
				/* Check twin: if already in list, remove both */
				int	found = 0;
				int	k = 0;
				while (k < n)
				{
					if (edges[k].a == e.b && edges[k].b == e.a)
					{
						edges[k] = edges[--n];
						found = 1;
						break ;
					}
					k++;
				}
				if (!found && n < EPA_MAX_VERTS * 3)
					edges[n++] = e;
				j++;
			}
		}
		i++;
	}
	/* Compact faces array */
	j = 0;
	i = 0;
	while (i < p->n_faces)
	{
		if (!removed[i])
			p->faces[j++] = p->faces[i];
		i++;
	}
	p->n_faces = j;
	*n_edges = n;
	return (n);
}

/* ── Add vertex + new faces ───────────────────────────────────────────── */
static void	expand_polytope(t_epa_poly *p, t_vec3 pt, t_vec3 apt, t_vec3 bpt,
		t_edge *edges, int n_edges)
{
	int	vi;
	int	i;

	if (p->n_verts >= EPA_MAX_VERTS)
		return ;
	vi = p->n_verts;
	p->pts[vi] = pt;
	p->a_pts[vi] = apt;
	p->b_pts[vi] = bpt;
	p->n_verts++;
	i = 0;
	while (i < n_edges && p->n_faces < EPA_MAX_FACES)
	{
		p->faces[p->n_faces] = make_face(p, edges[i].a, edges[i].b, vi);
		p->n_faces++;
		i++;
	}
}

/*
** Barycentric coordinates of point p on triangle (a,b,c).
** Returns (u, v, w) such that p ≈ u*a + v*b + w*c.
*/
static t_vec3	bary(t_vec3 a, t_vec3 b, t_vec3 c, t_vec3 p_pt)
{
	t_vec3	v0;
	t_vec3	v1;
	t_vec3	v2;
	double	d00;
	double	d01;
	double	d11;
	double	d20;
	double	d21;
	double	denom;
	double	v;
	double	w;

	v0 = vec3_sub(b, a);
	v1 = vec3_sub(c, a);
	v2 = vec3_sub(p_pt, a);
	d00 = vec3_dot(v0, v0);
	d01 = vec3_dot(v0, v1);
	d11 = vec3_dot(v1, v1);
	d20 = vec3_dot(v2, v0);
	d21 = vec3_dot(v2, v1);
	denom = d00 * d11 - d01 * d01;
	if (fabs(denom) < 1e-12)
		return (vec3(0.333, 0.333, 0.334));
	v = (d11 * d20 - d01 * d21) / denom;
	w = (d00 * d21 - d01 * d20) / denom;
	return (vec3(1.0 - v - w, v, w));
}

bool	gjk_epa(t_gjk_shape *a, t_gjk_shape *b, t_simplex *s,
		t_vec3 *normal, double *depth,
		t_vec3 *contact_a, t_vec3 *contact_b)
{
	t_epa_poly	poly;
	t_edge		edges[EPA_MAX_VERTS * 3];
	int			n_edges;
	t_vec3		pt;
	t_vec3		apt;
	t_vec3		bpt;
	t_vec3		bary_w;
	int			fi;
	double		new_dist;
	int			iter;
	t_epa_face	*f;

	init_polytope(&poly, s);
	if (poly.n_faces == 0)
		return (false);
	iter = 0;
	while (iter < EPA_MAX_ITER)
	{
		fi = closest_face(&poly);
		f = &poly.faces[fi];
		apt = a->support(a->data, f->normal);
		bpt = b->support(b->data, vec3_scale(f->normal, -1.0));
		pt = vec3_sub(apt, bpt);
		new_dist = vec3_dot(f->normal, pt);
		if (new_dist - f->dist < EPA_TOL)
		{
			/* Converged: compute contact points via barycentric interpolation */
			bary_w = bary(poly.pts[f->idx[0]], poly.pts[f->idx[1]],
					poly.pts[f->idx[2]],
					vec3_scale(f->normal, f->dist));
			*contact_a = vec3_add(
					vec3_add(
						vec3_scale(poly.a_pts[f->idx[0]], bary_w.x),
						vec3_scale(poly.a_pts[f->idx[1]], bary_w.y)),
					vec3_scale(poly.a_pts[f->idx[2]], bary_w.z));
			*contact_b = vec3_add(
					vec3_add(
						vec3_scale(poly.b_pts[f->idx[0]], bary_w.x),
						vec3_scale(poly.b_pts[f->idx[1]], bary_w.y)),
					vec3_scale(poly.b_pts[f->idx[2]], bary_w.z));
			*normal = f->normal;
			*depth = f->dist;
			return (true);
		}
		collect_silhouette(&poly, pt, edges, &n_edges);
		expand_polytope(&poly, pt, apt, bpt, edges, n_edges);
		iter++;
	}
	/* Timeout: return best face found so far */
	fi = closest_face(&poly);
	f = &poly.faces[fi];
	*normal = f->normal;
	*depth = f->dist;
	bary_w = bary(poly.pts[f->idx[0]], poly.pts[f->idx[1]],
			poly.pts[f->idx[2]], vec3_scale(f->normal, f->dist));
	*contact_a = vec3_add(
			vec3_add(
				vec3_scale(poly.a_pts[f->idx[0]], bary_w.x),
				vec3_scale(poly.a_pts[f->idx[1]], bary_w.y)),
			vec3_scale(poly.a_pts[f->idx[2]], bary_w.z));
	*contact_b = vec3_add(
			vec3_add(
				vec3_scale(poly.b_pts[f->idx[0]], bary_w.x),
				vec3_scale(poly.b_pts[f->idx[1]], bary_w.y)),
			vec3_scale(poly.b_pts[f->idx[2]], bary_w.z));
	return (true);
}
