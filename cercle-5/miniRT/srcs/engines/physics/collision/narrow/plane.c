/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:21:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 13:21:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

int	gjk_vs_all_planes(t_gjk_shape *sa, int body_idx, t_physics *phys,
		t_contact *c, int count, int max)
{
	(void)sa;
	(void)body_idx;
	(void)phys;
	(void)c;
	(void)count;
	(void)max;
	return (count);
}

int	box_vs_plane(t_physics *phys, int bi, int pi, t_contact *c)
{
	t_vec3	n;
	t_vec3	pos;
	t_vec3	ax[3];
	t_vec3	cor;
	int		count;
	int		i;

	n = vec3_norm(vec3(phys->scene->primitives.ax[pi],
				phys->scene->primitives.ay[pi], phys->scene->primitives.az[pi]));
	pos = vec3(phys->scene->primitives.px[pi], phys->scene->primitives.py[pi],
			phys->scene->primitives.pz[pi]);
	ax[0] = vec3_norm(vec3(phys->scene->primitives.ax[bi],
				phys->scene->primitives.ay[bi], phys->scene->primitives.az[bi]));
	vec3_orthonormal_basis(ax[0], &ax[1], &ax[2]);
	count = 0;
	i = -1;
	while (++i < 8)
	{
		cor = vec3_add(vec3(phys->scene->primitives.px[bi],
					phys->scene->primitives.py[bi],
					phys->scene->primitives.pz[bi]),
				vec3_add(vec3_add(vec3_scale(ax[0],
							((i & 1) ? 1 : -1) * phys->scene->primitives.ex[bi]),
						vec3_scale(ax[1],
							((i & 2) ? 1 : -1) * phys->scene->primitives.ey[bi])),
					vec3_scale(ax[2],
						((i & 4) ? 1 : -1) * phys->scene->primitives.ez[bi])));
		if (vec3_dot(vec3_sub(cor, pos), n) < 0.0)
			if (count < 8)
				gjk_vs_plane(phys, bi, pi, &c[count++]);
	}
	return (count);
}

int	tri_vs_plane(t_physics *phys, int ti, int pi, t_contact *c)
{
	t_vec3		n;
	t_vec3		pos;
	t_tri_array	*t_soa;
	int			cnt;
	int			i;
	t_tri_view	tri;
	t_vec3		v[3];

	t_soa = &phys->scene->tri_soa;
	n = vec3_norm(vec3(phys->scene->primitives.ax[pi],
				phys->scene->primitives.ay[pi], phys->scene->primitives.az[pi]));
	pos = vec3(phys->scene->primitives.px[pi], phys->scene->primitives.py[pi],
			phys->scene->primitives.pz[pi]);
	tri = unpack_tri(t_soa, ti);
	v[0] = tri.v0;
	v[1] = tri.v1;
	v[2] = tri.v2;
	cnt = 0;
	i = -1;
	while (++i < 3)
	{
		if (vec3_dot(vec3_sub(v[i], pos), n) < 0.0)
			if (cnt < 8)
				gjk_vs_plane(phys, ti, pi, &c[cnt++]);
	}
	return (cnt);
}

int	rect_vs_plane(t_physics *phys, int ri, int pi, t_contact *c)
{
	t_rect	rc;
	t_vec3	pos;
	t_vec3	n;
	t_vec3	ax[2];
	t_vec3	corners[4];
	int		cnt;
	int		i;

	rc = unpack_rect(&phys->scene->primitives, ri);
	n = vec3_norm(vec3(phys->scene->primitives.ax[pi],
				phys->scene->primitives.ay[pi], phys->scene->primitives.az[pi]));
	pos = vec3(phys->scene->primitives.px[pi], phys->scene->primitives.py[pi],
			phys->scene->primitives.pz[pi]);
	vec3_orthonormal_basis(rc.normal, &ax[0], &ax[1]);
	corners[0] = vec3_add(rc.pos, vec3_add(vec3_scale(ax[0], rc.ex), vec3_scale(ax[1], rc.ey)));
	corners[1] = vec3_add(rc.pos, vec3_add(vec3_scale(ax[0], -rc.ex), vec3_scale(ax[1], rc.ey)));
	corners[2] = vec3_add(rc.pos, vec3_add(vec3_scale(ax[0], -rc.ex), vec3_scale(ax[1], -rc.ey)));
	corners[3] = vec3_add(rc.pos, vec3_add(vec3_scale(ax[0], rc.ex), vec3_scale(ax[1], -rc.ey)));
	cnt = 0;
	i = -1;
	while (++i < 4)
	{
		if (vec3_dot(vec3_sub(corners[i], pos), n) < 0.0)
			if (cnt < 8)
				gjk_vs_plane(phys, ri, pi, &c[cnt++]);
	}
	return (cnt);
}

int	prim_plane_contacts(t_physics *phys, int idx, t_gjk_shape *sa,
		t_contact *c, int count, int max)
{
	t_scene		*s;
	int			p;

	(void)sa;
	s = phys->scene;
	p = -1;
	while (++p < (int)s->primitives.count && count < max)
	{
		if (s->primitives.types[p] != PRIM_PLANE)
			continue ;
		if (idx == p)
			continue ;
		if (s->primitives.types[idx] == PRIM_BOX)
			count += box_vs_plane(phys, idx, p, &c[count]);
		else if (s->primitives.types[idx] == PRIM_TRIANGLE)
			count += tri_vs_plane(phys, idx, p, &c[count]);
		else if (s->primitives.types[idx] == PRIM_RECT)
			count += rect_vs_plane(phys, idx, p, &c[count]);
		else
			count += gjk_vs_plane(phys, idx, p, &c[count]);
	}
	return (count);
}
