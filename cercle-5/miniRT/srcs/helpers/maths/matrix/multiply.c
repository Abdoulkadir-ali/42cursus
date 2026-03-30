/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_mul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

static void	mat4_mul_row(double *dst, const double *a, const t_mat4 *b)
{
	dst[0] = a[0] * b->m[0][0] + a[1] * b->m[1][0]
		+ a[2] * b->m[2][0] + a[3] * b->m[3][0];
	dst[1] = a[0] * b->m[0][1] + a[1] * b->m[1][1]
		+ a[2] * b->m[2][1] + a[3] * b->m[3][1];
	dst[2] = a[0] * b->m[0][2] + a[1] * b->m[1][2]
		+ a[2] * b->m[2][2] + a[3] * b->m[3][2];
	dst[3] = a[0] * b->m[0][3] + a[1] * b->m[1][3]
		+ a[2] * b->m[2][3] + a[3] * b->m[3][3];
}

t_mat4	mat4_mul(t_mat4 a, t_mat4 b)
{
	t_mat4	res;

	mat4_mul_row(res.m[0], a.m[0], &b);
	mat4_mul_row(res.m[1], a.m[1], &b);
	mat4_mul_row(res.m[2], a.m[2], &b);
	mat4_mul_row(res.m[3], a.m[3], &b);
	return (res);
}
