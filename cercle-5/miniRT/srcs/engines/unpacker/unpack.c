/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unpack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 12:47:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



t_sphere	unpack_sphere(const t_primitive_array *p, int i)
{
	t_sphere	s;

	s.center = vec3(p->px[i], p->py[i], p->pz[i]);
	s.radius = p->radii[i];
	s.mat_idx = p->mat_ids[i];
	return (s);
}

t_plane	unpack_plane(const t_primitive_array *p, int i)
{
	t_plane	pl;

	pl.point = vec3(p->px[i], p->py[i], p->pz[i]);
	pl.normal = vec3(p->ax[i], p->ay[i], p->az[i]);
	pl.mat_idx = p->mat_ids[i];
	return (pl);
}

t_cylinder	unpack_cylinder(const t_primitive_array *p, int i)
{
	t_cylinder	cy;

	cy.pos = vec3(p->px[i], p->py[i], p->pz[i]);
	cy.axis = vec3(p->ax[i], p->ay[i], p->az[i]);
	cy.radius = p->radii[i];
	cy.height = p->heights[i];
	cy.mat_idx = p->mat_ids[i];
	return (cy);
}

t_cone	unpack_cone(const t_primitive_array *p, int i)
{
	t_cone	co;

	co.tip = vec3(p->px[i], p->py[i], p->pz[i]);
	co.axis = vec3(p->ax[i], p->ay[i], p->az[i]);
	co.height = p->heights[i];
	co.angle = p->radii[i];
	co.mat_idx = p->mat_ids[i];
	return (co);
}

t_box	unpack_box(const t_primitive_array *p, int i)
{
	t_box	b;
	t_vec3	pos;
	t_vec3	ext;

	pos = vec3(p->px[i], p->py[i], p->pz[i]);
	ext = vec3(p->ex[i], p->ey[i], p->ez[i]);
	b.min = vec3_sub(pos, ext);
	b.max = vec3_add(pos, ext);
	b.mat_idx = p->mat_ids[i];
	return (b);
}

t_capsule	unpack_capsule(const t_primitive_array *p, int i)
{
	t_capsule	ca;
	t_vec3		pos;
	t_vec3		axis;

	pos = vec3(p->px[i], p->py[i], p->pz[i]);
	axis = vec3(p->ax[i], p->ay[i], p->az[i]);
	ca.a = pos;
	ca.b = vec3_add(pos, vec3_scale(axis, p->heights[i]));
	ca.radius = p->radii[i];
	ca.mat_idx = p->mat_ids[i];
	return (ca);
}

t_rect	unpack_rect(const t_primitive_array *p, int i)
{
	t_rect	re;

	re.pos = vec3(p->px[i], p->py[i], p->pz[i]);
	re.normal = vec3(p->ax[i], p->ay[i], p->az[i]);
	re.ex = p->ex[i];
	re.ey = p->ey[i];
	re.mat_idx = p->mat_ids[i];
	return (re);
}

t_pyramid	unpack_pyramid(const t_primitive_array *p, int i)
{
	t_pyramid	py;

	py.pos = vec3(p->px[i], p->py[i], p->pz[i]);
	py.up = vec3(p->ax[i], p->ay[i], p->az[i]);
	py.size = p->radii[i];
	py.height = p->heights[i];
	py.mat_idx = p->mat_ids[i];
	return (py);
}

t_tri_view	unpack_tri(const t_tri_array *t, int i)
{
	t_tri_view	tri;

	tri.v0 = vec3(t->vx[0][i], t->vy[0][i], t->vz[0][i]);
	tri.v1 = vec3(t->vx[1][i], t->vy[1][i], t->vz[1][i]);
	tri.v2 = vec3(t->vx[2][i], t->vy[2][i], t->vz[2][i]);
	tri.n = vec3(t->nx[i], t->ny[i], t->nz[i]);
	tri.mat_idx = t->mat_ids[i];
	return (tri);
}
