/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 04:58:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include <immintrin.h>

/* Keep helper for non-AVX usage if needed, or remove */
double	catmull_rom_interpolate(t_vec4d c, double t)
{
	(void)c; (void)t; return (0); // Deprecated by AVX version
}

/* AVX Implementation of Catmull-Rom Spline Interpolation 
   Calculates X, Y, Z, and even a 4th component simultaneously.
*/
t_point	catmull_rom_point(t_spline s, double t)
{
	t_point result;
	
	/* Load points into AVX registers (4 doubles per register) 
	   Note: We load the struct directly. Assuming t_vec3d aligns with double[3] 
	   We use _mm256_set_pd to manually construct vectors if alignment is unsure,
	   or just load if we pad our structs. Here we construct for safety. */
	
	__m256d p0 = _mm256_set_pd(0, s.p0.pos.z, s.p0.pos.y, s.p0.pos.x);
	__m256d p1 = _mm256_set_pd(0, s.p1.pos.z, s.p1.pos.y, s.p1.pos.x);
	__m256d p2 = _mm256_set_pd(0, s.p2.pos.z, s.p2.pos.y, s.p2.pos.x);
	__m256d p3 = _mm256_set_pd(0, s.p3.pos.z, s.p3.pos.y, s.p3.pos.x);

	/* Pre-calculate powers of t */
	__m256d t_vec = _mm256_set1_pd(t);
	__m256d t2 = _mm256_mul_pd(t_vec, t_vec);
	__m256d t3 = _mm256_mul_pd(t2, t_vec);

	/* Coefficients */
	__m256d v05 = _mm256_set1_pd(0.5);
	__m256d v2 = _mm256_set1_pd(2.0);
	__m256d v3 = _mm256_set1_pd(3.0);
	__m256d v4 = _mm256_set1_pd(4.0);
	__m256d v5 = _mm256_set1_pd(5.0);

	/* Term 1: 2 * P1 */
	__m256d term1 = _mm256_mul_pd(v2, p1);

	/* Term 2: (-P0 + P2) * t */
	__m256d term2 = _mm256_mul_pd(_mm256_sub_pd(p2, p0), t_vec);

	/* Term 3: (2*P0 - 5*P1 + 4*P2 - P3) * t^2 */
	__m256d t3_inner = _mm256_sub_pd(_mm256_mul_pd(v2, p0), _mm256_mul_pd(v5, p1));
	t3_inner = _mm256_add_pd(t3_inner, _mm256_mul_pd(v4, p2));
	t3_inner = _mm256_sub_pd(t3_inner, p3);
	__m256d term3 = _mm256_mul_pd(t3_inner, t2);

	/* Term 4: (-P0 + 3*P1 - 3*P2 + P3) * t^3 */
	__m256d t4_inner = _mm256_add_pd(_mm256_sub_pd(p3, p0), _mm256_mul_pd(v3, _mm256_sub_pd(p1, p2)));
	__m256d term4 = _mm256_mul_pd(t4_inner, t3);

	/* Sum and Scale */
	__m256d sum = _mm256_add_pd(_mm256_add_pd(term1, term2), _mm256_add_pd(term3, term4));
	__m256d res = _mm256_mul_pd(sum, v05);

	/* Store back */
	double tmp[4];
	_mm256_storeu_pd(tmp, res);
	
	result.pos.x = tmp[0];
	result.pos.y = tmp[1];
	result.pos.z = tmp[2];
	result.color = s.p1.color; // Base color

	return (result);
}

t_point	lerp_point(t_point p1, t_point p2, double t)
{
	t_point	result;

	result.pos.x = p1.pos.x + (p2.pos.x - p1.pos.x) * t;
	result.pos.y = p1.pos.y + (p2.pos.y - p1.pos.y) * t;
	result.pos.z = p1.pos.z + (p2.pos.z - p1.pos.z) * t;
	result.color = interpolate_color(p1.color, p2.color, t);
	return (result);
}