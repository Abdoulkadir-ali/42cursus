/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   face.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 10:59:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Creates a polytope face with a normal pointing outward from origin.
 */
t_epa_face	epa_make_face(t_epa_poly *p, t_vec3s tri)
{
	t_epa_face	f;
	t_vec3		e0;
	t_vec3		e1;
	t_vec3		n;
	double		len;

	f.idx[0] = tri.x;
	f.idx[1] = tri.y;
	f.idx[2] = tri.z;
	e0 = vec3_sub(p->pts[tri.y], p->pts[tri.x]);
	e1 = vec3_sub(p->pts[tri.z], p->pts[tri.x]);
	n = vec3_cross(e0, e1);
	len = vec3_mag(n);
	if (len < 1e-12)
		return ((t_epa_face){{tri.x, tri.y, tri.z}, vec3(0, 1, 0), 0.0});
	f.normal = vec3_scale(n, 1.0 / len);
	f.dist = vec3_dot(f.normal, p->pts[tri.x]);
	if (f.dist < 0.0)
	{
		f.normal = vec3_scale(f.normal, -1.0);
		f.dist = -f.dist;
	}
	return (f);
}

/**
 * @brief Finds the face in the polytope closest to the origin.
 */
size_t	epa_closest_face(t_epa_poly *p)
{
	size_t	best;
	double	best_d;
	size_t	i;

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
