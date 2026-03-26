/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

extern void	push_face(t_epa_poly *p, int i0, int i1, int i2);

static void	add_edge(t_edge *edges, int *n, int a, int b)
{
	int	i;

	i = -1;
	while (++i < *n)
	{
		if (edges[i].a == b && edges[i].b == a)
		{
			edges[i] = edges[--(*n)];
			return ;
		}
	}
	edges[(*n)].a = a;
	edges[(*n)++].b = b;
}

/**
 * @brief Adds new vertex to EPA polytope and updates the hull silhouette.
 */
void	expand(t_epa_poly *p, t_vec3 pt, t_vec3 pa, t_vec3 pb)
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
	i = -1;
	while (++i < p->n_faces)
	{
		if (vec3_dot(p->faces[i].normal, vec3_sub(pt, p->pts[p->faces[i].idx[0]])) > 0)
		{
			add_edge(edges, &ne, p->faces[i].idx[0], p->faces[i].idx[1]);
			add_edge(edges, &ne, p->faces[i].idx[1], p->faces[i].idx[2]);
			add_edge(edges, &ne, p->faces[i].idx[2], p->faces[i].idx[0]);
			p->faces[i--] = p->faces[--p->n_faces];
		}
	}
	i = -1;
	while (++i < ne)
		push_face(p, edges[i].a, edges[i].b, pidx);
}
