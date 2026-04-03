/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   face.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 10:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Creates a polytope face with a normal pointing outward from origin.
 */
t_epa_face	epa_make_face(t_epa_poly *p, size_t i0, size_t i1, size_t i2)
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
		return ((t_epa_face){{i0, i1, i2}, vec3(0, 1, 0), 0.0});
	f.normal = vec3_scale(n, 1.0 / len);
	f.dist = vec3_dot(f.normal, p->pts[i0]);
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
