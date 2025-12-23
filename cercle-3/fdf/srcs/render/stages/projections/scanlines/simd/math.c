/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:32:26 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:01:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "render.h"

__m256d	matrix_row_mul(t_simd_vec3 vec, t_simd_vec4 mat)
{
	__m256d	res;

	res = mat.m[3];
	res = _mm256_fmadd_pd(vec.x, mat.m[0], res);
	res = _mm256_fmadd_pd(vec.y, mat.m[1], res);
	res = _mm256_fmadd_pd(vec.z, mat.m[2], res);
	return (res);
}

__m256d	vector_dot(t_simd_vec3 vec, t_simd_vec3 v)
{
	__m256d	res;

	res = _mm256_setzero_pd();
	res = _mm256_fmadd_pd(vec.x, v.x, res);
	res = _mm256_fmadd_pd(vec.y, v.y, res);
	res = _mm256_fmadd_pd(vec.z, v.z, res);
	return (res);
}
