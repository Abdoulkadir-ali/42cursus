/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/24 20:18:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include <xmmintrin.h>

typedef struct s_ray_oct
{
	float	ox;
	float	oy;
	float	oz;
	float	idx;
	float	idy;
	float	idz;
}	t_ray_oct;

/*
** Test all 4 BVH children AABB against the ray in one SSE pass.
** Returns a 4-bit mask: bit i set if child i is hit.
** Caller must AND with ((1 << n_children) - 1) to ignore padding slots.
*/
__attribute__((optimize("O3")))
static inline __attribute__((always_inline))
int	test_all4_occ(const t_bvh_node4 *n4, const t_ray_oct *ro, float max_t)
{
	const __m128	vox   = _mm_set1_ps(ro->ox);
	const __m128	voy   = _mm_set1_ps(ro->oy);
	const __m128	voz   = _mm_set1_ps(ro->oz);
	const __m128	vidx  = _mm_set1_ps(ro->idx);
	const __m128	vidy  = _mm_set1_ps(ro->idy);
	const __m128	vidz  = _mm_set1_ps(ro->idz);
	const __m128	vmaxt = _mm_set1_ps(max_t);
	const __m128	vzero = _mm_setzero_ps();
	__m128			t1;
	__m128			t2;
	__m128			vmn;
	__m128			vmx;

	t1  = _mm_mul_ps(_mm_sub_ps(_mm_loadu_ps(n4->min_x), vox), vidx);
	t2  = _mm_mul_ps(_mm_sub_ps(_mm_loadu_ps(n4->max_x), vox), vidx);
	vmn = _mm_min_ps(t1, t2);
	vmx = _mm_max_ps(t1, t2);
	t1  = _mm_mul_ps(_mm_sub_ps(_mm_loadu_ps(n4->min_y), voy), vidy);
	t2  = _mm_mul_ps(_mm_sub_ps(_mm_loadu_ps(n4->max_y), voy), vidy);
	vmn = _mm_max_ps(vmn, _mm_min_ps(t1, t2));
	vmx = _mm_min_ps(vmx, _mm_max_ps(t1, t2));
	t1  = _mm_mul_ps(_mm_sub_ps(_mm_loadu_ps(n4->min_z), voz), vidz);
	t2  = _mm_mul_ps(_mm_sub_ps(_mm_loadu_ps(n4->max_z), voz), vidz);
	vmn = _mm_max_ps(vmn, _mm_min_ps(t1, t2));
	vmx = _mm_min_ps(vmx, _mm_max_ps(t1, t2));
	return (_mm_movemask_ps(_mm_and_ps(
				_mm_and_ps(_mm_cmple_ps(vzero, vmx), _mm_cmple_ps(vmn, vmx)),
				_mm_cmplt_ps(vmn, vmaxt))));
}

__attribute__((optimize("O3")))
static inline __attribute__((always_inline))
bool	leaf_occ4(const t_bvh *bvh, const t_ray *ray, double max_t,
		size_t sd[2])
{
	size_t	j;

	j = 0;
	while (j < sd[1])
	{
		if (occlude_primitive(ray, bvh->scene,
				bvh->refs[sd[0] + j], max_t))
			return (true);
		j++;
	}
	return (false);
}

__attribute__((optimize("O3")))
static inline __attribute__((always_inline))
bool	occ_visit4(const t_bvh *bvh, const t_ray *ray, double max_t,
		t_mbvh_stk *stk, const t_ray_oct *ro)
{
	const t_bvh_node4	*n4;
	size_t				i;
	size_t				sd[2];
	int					hit_bits;

	n4 = &bvh->nodes4[stk->st[--stk->top]];
	hit_bits = test_all4_occ(n4, ro, (float)max_t)
		& ((1 << (int)n4->n_children) - 1);
	while (hit_bits)
	{
		i = (size_t)__builtin_ctz(hit_bits);
		hit_bits &= hit_bits - 1;
		if (n4->count[i] > 0)
		{
			sd[0] = n4->child[i];
			sd[1] = n4->count[i];
			if (leaf_occ4(bvh, ray, max_t, sd))
				return (true);
		}
		else if (stk->top < 62)
			stk->st[stk->top++] = n4->child[i];
	}
	return (false);
}

__attribute__((optimize("O3")))
bool	bvh_occluded4(const t_bvh *bvh, const t_ray *ray, double max_t)
{
	t_mbvh_stk	stk;
	t_ray_oct	ro;

	if (!bvh || !bvh->nodes4)
		return (bvh_occluded(bvh, ray, max_t));
	ro.ox = (float)ray->origin.x;
	ro.oy = (float)ray->origin.y;
	ro.oz = (float)ray->origin.z;
	ro.idx = (float)ray->inv_dir.x;
	ro.idy = (float)ray->inv_dir.y;
	ro.idz = (float)ray->inv_dir.z;
	stk.top = 0;
	stk.st[stk.top++] = 0;
	while (stk.top > 0)
	{
		if (occ_visit4(bvh, ray, max_t, &stk, &ro))
			return (true);
	}
	return (false);
}
