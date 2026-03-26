/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

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
	if (*n < EPA_MAX_VERTS * 3)
		edges[(*n)++] = (t_edge){a, b};
}

/**
 * @brief Removes visible faces and builds the silhouette edges.
 */
void	collect_silhouette(t_epa_poly *p, t_vec3 pt, t_edge *edges, int *n_e)
{
	bool	rem[EPA_MAX_FACES];
	int		v[2];

	*n_e = 0;
	v[0] = -1;
	while (++v[0] < p->n_faces)
		rem[v[0]] = (vec3_dot(p->faces[v[0]].normal,
					vec3_sub(pt, p->pts[p->faces[v[0]].idx[0]])) > 0.0);
	v[0] = -1;
	while (++v[0] < p->n_faces)
	{
		if (rem[v[0]])
		{
			v[1] = -1;
			while (++v[1] < 3)
				add_edge(edges, n_e, p->faces[v[0]].idx[v[1]],
					p->faces[v[0]].idx[(v[1] + 1) % 3]);
		}
	}
	v[1] = 0;
	v[0] = -1;
	while (++v[0] < p->n_faces)
		if (!rem[v[0]])
			p->faces[v[1]++] = p->faces[v[0]];
	p->n_faces = v[1];
}
