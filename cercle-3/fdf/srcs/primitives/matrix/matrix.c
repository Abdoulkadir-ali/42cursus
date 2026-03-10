/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 12:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/03/10 02:27:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"

/**
 * @brief Build a 4x4 identity matrix.
 * @return Matrix with a unit diagonal and zero elsewhere.
 */
t_matrix4	matrix_identity(void)
{
	t_matrix4	m;

	ft_memset(&m, 0, sizeof(t_matrix4));
	m.m[0][0] = 1.0f;
	m.m[1][1] = 1.0f;
	m.m[2][2] = 1.0f;
	m.m[3][3] = 1.0f;
	return (m);
}

/**
 * @brief Multiply two 4x4 matrices.
 * @param a Left-hand matrix.
 * @param b Right-hand matrix.
 * @return Product matrix `a * b`.
 */
t_matrix4	matrix_multiply(t_matrix4 a, t_matrix4 b)
{
	t_matrix4	res;
	int			i;
	int			j;
	int			k;

	ft_memset(&res, 0, sizeof(t_matrix4));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (k < 4)
			{
				res.m[i][j] += a.m[i][k] * b.m[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (res);
}

/**
 * @brief Build a translation matrix from three offsets.
 * @param x Translation along the x axis.
 * @param y Translation along the y axis.
 * @param z Translation along the z axis.
 * @return Translation matrix.
 */
t_matrix4	matrix_translation(float x, float y, float z)
{
	t_matrix4	m;

	m = matrix_identity();
	m.m[0][3] = x;
	m.m[1][3] = y;
	m.m[2][3] = z;
	return (m);
}

/**
 * @brief Build a scaling matrix from three scale factors.
 * @param x Scale factor for the x axis.
 * @param y Scale factor for the y axis.
 * @param z Scale factor for the z axis.
 * @return Scaling matrix.
 */
t_matrix4	matrix_scale(float x, float y, float z)
{
	t_matrix4	m;

	m = matrix_identity();
	m.m[0][0] = x;
	m.m[1][1] = y;
	m.m[2][2] = z;
	return (m);
}
