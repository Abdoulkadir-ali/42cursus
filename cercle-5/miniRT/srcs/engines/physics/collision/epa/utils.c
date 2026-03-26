/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

t_vec3	bary(const t_vec3 tri[3], t_vec3 p)
{
	t_vec3	v[2];
	t_vec3	v0p;
	double	d[6];
	double	denom;

	v[0] = vec3_sub(tri[1], tri[0]);
	v[1] = vec3_sub(tri[2], tri[0]);
	v0p = vec3_sub(p, tri[0]);
	d[0] = vec3_dot(v[0], v[0]);
	d[1] = vec3_dot(v[0], v[1]);
	d[2] = vec3_dot(v[1], v[1]);
	d[3] = vec3_dot(v0p, v[0]);
	d[4] = vec3_dot(v0p, v[1]);
	denom = d[0] * d[2] - d[1] * d[1];
	if (fabs(denom) < 1e-12)
		return ((t_vec3){1, 0, 0, 0});
	d[5] = (d[2] * d[3] - d[1] * d[4]) / denom;
	denom = (d[0] * d[4] - d[1] * d[3]) / denom;
	return ((t_vec3){1.0 - d[5] - denom, d[5], denom, 0});
}

int	closest_face(t_epa_poly *p)
{
	int		idx;
	int		i;
	double	min_dist;

	idx = 0;
	min_dist = 1e30;
	i = -1;
	while (++i < p->n_faces)
	{
		if (p->faces[i].dist < min_dist)
		{
			min_dist = p->faces[i].dist;
			idx = i;
		}
	}
	return (idx);
}

void	get_contact_points(t_epa_poly *p, t_epa_face *f, t_vec3 *ca, t_vec3 *cb)
{
	t_vec3	ba;
	t_vec3	v[3];

	v[0] = p->pts[f->idx[0]];
	v[1] = p->pts[f->idx[1]];
	v[2] = p->pts[f->idx[2]];
	ba = bary(v, vec3_scale(f->normal, f->dist));
	*ca = vec3_add(vec3_scale(p->a_pts[f->idx[0]], ba.x),
			vec3_add(vec3_scale(p->a_pts[f->idx[1]], ba.y),
				vec3_scale(p->a_pts[f->idx[2]], ba.z)));
	*cb = vec3_add(vec3_scale(p->b_pts[f->idx[0]], ba.x),
			vec3_add(vec3_scale(p->b_pts[f->idx[1]], ba.y),
				vec3_scale(p->b_pts[f->idx[2]], ba.z)));
}
