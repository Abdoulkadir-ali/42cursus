/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   silhouette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:42:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Removes an edge if it already exists in the silhouette.
 */
static bool	check_edge(t_edge *edges, size_t *n, t_edge e)
{
	size_t	k;

	k = 0;
	while (k < *n)
	{
		if (edges[k].a == e.b && edges[k].b == e.a)
		{
			edges[k] = edges[--(*n)];
			return (true);
		}
		k++;
	}
	return (false);
}

static void	add_edges(t_epa_poly *p, size_t f_idx, t_edge *edges, size_t *n)
{
	size_t	j;
	t_edge	e;

	j = 0;
	while (j < 3)
	{
		e = (t_edge){p->faces[f_idx].idx[j],
			p->faces[f_idx].idx[(j + 1) % 3]};
		if (!check_edge(edges, n, e) && *n < EPA_MAX_VERTS * 3)
			edges[(*n)++] = e;
		j++;
	}
	p->faces[f_idx].dist = -1.0;
}

/**
 * @brief Identifies edges visible from point pt and removes corresponding faces.
 */
static void	process_visible(t_epa_poly *p, t_vec3 pt, t_edge *edges, size_t *n)
{
	size_t	i;
	bool	rem[EPA_MAX_FACES];

	i = 0;
	while (i < p->n_faces)
	{
		rem[i] = (vec3_dot(p->faces[i].normal,
					vec3_sub(pt, p->pts[p->faces[i].idx[0]])) > 0.0);
		i++;
	}
	i = 0;
	while (i < p->n_faces)
	{
		if (rem[i])
			add_edges(p, i, edges, n);
		i++;
	}
}

/**
 * @brief Collects the silhouette of the polytope as seen from point pt.
 */
void	epa_collect_silhouette(t_epa_poly *p, t_vec3 pt, t_edge *edges,
		size_t *n)
{
	size_t	i;
	size_t	j;

	*n = 0;
	process_visible(p, pt, edges, n);
	j = 0;
	i = 0;
	while (i < p->n_faces)
	{
		if (p->faces[i].dist >= 0.0)
			p->faces[j++] = p->faces[i];
		i++;
	}
	p->n_faces = j;
}
