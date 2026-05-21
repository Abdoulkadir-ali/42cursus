/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simd.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 18:26:40 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 18:26:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMD_H
# define SIMD_H

# include <immintrin.h>
# include "maths.h"
# include "raytracing.h"

/* SIMD (SSE4.1) - Vector Extensions Approach */
typedef float	t_v128 __attribute__((vector_size(16)));

typedef struct s_sv3
{
	t_v128	x;
	t_v128	y;
	t_v128	z;
}	t_sv3;

static inline t_v128	sv3_dot(t_sv3 a, t_sv3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

static inline t_sv3	sv3_cross(t_sv3 a, t_sv3 b)
{
	return ((t_sv3){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	});
}

static inline t_sv3	sv3_sub(t_sv3 a, t_sv3 b)
{
	return ((t_sv3){a.x - b.x, a.y - b.y, a.z - b.z});
}

void	load_sse_tri(t_sv3 *rd, t_sv3 *ro, t_sv3 *e1, t_sv3 *e2, t_sv3 *a, \
			const t_tri_soa4 *t, const t_ray *r);
int		find_best_hit(t_hit *h, t_v128 tt, t_v128 u, t_v128 v, \
			int m, float res[2]);
void	update_hit_sse(t_hit *h, const t_tri_soa4 *t, const t_ray *r, \
			int idx, float u, float v);
int		hit_triangle_sse(const t_tri_soa4 *t, const t_ray *r, t_hit *h);

#endif
