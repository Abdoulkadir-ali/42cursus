/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 05:54:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 05:54:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

bool	realloc_physics_soa(t_physics_soa *p, size_t new_cap)
{
	int		*ni, *nf, *npc;
	float	*nvx, *nax, *nm, *ne, *am, *ax, *ni_inv;
	uint8_t	*ns, *nc;

	ni = realloc(p->prim_idx, new_cap * sizeof(int));
	nvx = realloc(p->hot.vx, new_cap * 4 * 3); /* linear v 3 components */
	nax = realloc(p->hot.ang_vx, new_cap * 4 * 3); /* angular v 3 components */
	nm = realloc(p->mass, new_cap * 4 * 2); /* mass + inv_mass */
	ne = realloc(p->elasticity, new_cap * 4 * 2); /* elasticity + friction */
	ni_inv = realloc(p->inv_ix, new_cap * 4 * 3); /* inv_ix, iy, iz */
	am = realloc(p->hot.amin_x, new_cap * 4 * 3);
	ax = realloc(p->hot.amax_x, new_cap * 4 * 3);
	ns = realloc(p->is_static, new_cap);
	nc = realloc(p->is_compound, new_cap);
	nf = realloc(p->first_part, new_cap * sizeof(int));
	npc = realloc(p->part_count, new_cap * sizeof(int));
	if (!ni || !nvx || !nax || !nm || !ne || !ni_inv || !am || !ax || !ns || !nc || !nf || !npc)
		return (false);
	p->prim_idx = ni;
	p->hot.vx = nvx; p->hot.vy = nvx + new_cap; p->hot.vz = nvx + 2 * new_cap;
	p->hot.ang_vx = nax; p->hot.ang_vy = nax + new_cap; p->hot.ang_vz = nax + 2 * new_cap;
	p->mass = nm; p->inv_mass = nm + new_cap;
	p->elasticity = ne; p->friction = ne + new_cap;
	p->inv_ix = ni_inv; p->inv_iy = ni_inv + new_cap; p->inv_iz = ni_inv + 2 * new_cap;
	p->hot.amin_x = am; p->hot.amin_y = am + new_cap; p->hot.amin_z = am + 2 * new_cap;
	p->hot.amax_x = ax; p->hot.amax_y = ax + new_cap; p->hot.amax_z = ax + 2 * new_cap;
	p->is_static = ns; p->is_compound = nc;
	p->first_part = nf; p->part_count = npc;
	p->cap = new_cap;
	return (true);
}

void	destroy_physics_soa(t_physics_soa *p)
{
	if (!p)
		return ;
	free(p->prim_idx);
	free(p->hot.vx);
	free(p->hot.ang_vx);
	free(p->mass);
	free(p->elasticity);
	free(p->inv_ix);
	free(p->hot.amin_x);
	free(p->hot.amax_x);
	free(p->is_static);
	free(p->is_compound);
	free(p->first_part);
	free(p->part_count);
	memset(p, 0, sizeof(t_physics_soa));
}

bool	soa_add_body(t_physics_soa *p, t_primitive_array *prims, int prim_idx)
{
	int	idx;

	if (p->count >= p->cap)
		if (!realloc_physics_soa(p, (p->cap == 0) ? 1024 : p->cap * 2))
			return (false);
	idx = (int)p->count++;
	p->prim_idx[idx] = prim_idx;
	prims->phys_idx[prim_idx] = idx;
	p->hot.vx[idx] = 0; p->hot.vy[idx] = 0; p->hot.vz[idx] = 0;
	p->hot.ang_vx[idx] = 0; p->hot.ang_vy[idx] = 0; p->hot.ang_vz[idx] = 0;
	p->mass[idx] = 1.0f; p->inv_mass[idx] = 1.0f;
	p->elasticity[idx] = 0.5f; p->friction[idx] = 0.5f;
	p->inv_ix[idx] = 1.0f; p->inv_iy[idx] = 1.0f; p->inv_iz[idx] = 1.0f;
	p->is_static[idx] = 0; p->is_compound[idx] = 0;
	p->first_part[idx] = -1; p->part_count[idx] = 0;
	return (true);
}

