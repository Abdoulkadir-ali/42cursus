/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/24 20:18:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include <xmmintrin.h>

/*
** Test all 4 BVH children AABB against the primary ray using SSE.
** Returns a 4-bit mask; caller ANDs with ((1 << n_children) - 1).
** Additionally out_mn[0..3] receives the near-t for ordering purposes.
*/
__attribute__((optimize("O3")))
static inline __attribute__((always_inline))
int	test_all4_hit(const t_bvh_node4 *n4, const t_ray *ray,
		float max_t, float out_mn[4])
{
	const __m128	vox   = _mm_set1_ps((float)ray->origin.x);
	const __m128	voy   = _mm_set1_ps((float)ray->origin.y);
	const __m128	voz   = _mm_set1_ps((float)ray->origin.z);
	const __m128	vidx  = _mm_set1_ps((float)ray->inv_dir.x);
	const __m128	vidy  = _mm_set1_ps((float)ray->inv_dir.y);
	const __m128	vidz  = _mm_set1_ps((float)ray->inv_dir.z);
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
	_mm_storeu_ps(out_mn, vmn);
	return (_mm_movemask_ps(_mm_and_ps(
				_mm_and_ps(_mm_cmple_ps(vzero, vmx), _mm_cmple_ps(vmn, vmx)),
				_mm_cmplt_ps(vmn, vmaxt))));
}

__attribute__((optimize("O3")))
static bool	check_leaf4(const t_bvh *bvh, const t_ray *ray, t_hit *hit,
		size_t sd[2])
{
	size_t	j;
	t_hit	tmp;
	bool	any;

	any = false;
	j = 0;
	while (j < sd[1])
	{
		tmp.t = hit->t;
		if (intersect_object(ray, bvh->scene, bvh->refs[sd[0] + j], &tmp))
		{
			if (tmp.t < hit->t)
			{
				*hit = tmp;
				any = true;
			}
		}
		j++;
	}
	return (any);
}

__attribute__((optimize("O3")))
static void	visit_node4(const t_bvh *bvh, const t_ray *ray, t_hit *hit,
		t_mbvh_stk *stk)
{
	const t_bvh_node4	*n4;
	size_t				i;
	size_t				sd[2];
	float				mn[4];
	int					hit_bits;

	n4 = &bvh->nodes4[stk->st[--stk->top]];
	hit_bits = test_all4_hit(n4, ray, (float)hit->t, mn)
		& ((1 << (int)n4->n_children) - 1);
	while (hit_bits)
	{
		i = (size_t)__builtin_ctz(hit_bits);
		hit_bits &= hit_bits - 1;
		if (n4->count[i] > 0)
		{
			sd[0] = n4->child[i];
			sd[1] = n4->count[i];
			stk->any |= check_leaf4(bvh, ray, hit, sd);
		}
		else if (stk->top < 62)
			stk->st[stk->top++] = n4->child[i];
	}
	(void)mn;
}

__attribute__((optimize("O3")))
bool	bvh_intersect4(const t_bvh *bvh, const t_ray *ray, t_hit *hit)
{
	t_mbvh_stk	stk;

	if (!bvh || !bvh->nodes4)
		return (bvh_intersect(bvh, ray, hit));
	stk.any = false;
	stk.top = 0;
	stk.st[stk.top++] = 0;
	while (stk.top > 0)
		visit_node4(bvh, ray, hit, &stk);
	return (stk.any);
}
