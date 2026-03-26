/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polytope.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

t_epa_face	make_face(t_epa_poly *p, int i0, int i1, int i2)
{
	t_epa_face	f;
	t_vec3		v[3];

	f.idx[0] = i0;
	f.idx[1] = i1;
	f.idx[2] = i2;
	v[0] = p->pts[i0];
	v[1] = p->pts[i1];
	v[2] = p->pts[i2];
	f.normal = vec3_norm(vec3_cross(vec3_sub(v[1], v[0]), vec3_sub(v[2], v[0])));
	f.dist = vec3_dot(f.normal, v[0]);
	if (f.dist < 0)
	{
		f.normal = vec3_scale(f.normal, -1);
		f.dist = -f.dist;
	}
	return (f);
}

void	push_face(t_epa_poly *p, int i0, int i1, int i2)
{
	if (p->n_faces >= EPA_MAX_FACES)
		return ;
	p->faces[p->n_faces++] = make_face(p, i0, i1, i2);
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
