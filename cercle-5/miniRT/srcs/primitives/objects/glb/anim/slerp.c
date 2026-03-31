/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slerp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:32:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	handle_close_interpolation(float *out, float *a, float *b, float t)
{
	float	sign;
	float	len;
	int		i;

	sign = 1.0f;
	if (a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3] < 0.0f)
		sign = -1.0f;
	i = -1;
	while (++i < 4)
		out[i] = a[i] + t * (sign * b[i] - a[i]);
	len = sqrtf(out[0] * out[0] + out[1] * out[1] + out[2] * out[2]
			+ out[3] * out[3]);
	i = -1;
	while (++i < 4)
		out[i] /= len;
}

/**
 * Spherical Linear Interpolation (SLERP) for rotation quaternions.
 */
void	quat_slerp(float *out, float *a, float *b, float t)
{
	float	dot;
	float	sign;
	float	theta[2];
	float	s[2];
	int		i;

	dot = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
	sign = 1.0f;
	if (dot < 0.0f && ++(int){0})
	{
		dot = -dot;
		sign = -1.0f;
	}
	if (dot > 0.9995f)
		return (handle_close_interpolation(out, a, b, t));
	theta[0] = acosf(dot);
	theta[1] = theta[0] * t;
	s[0] = cosf(theta[1]) - dot * sinf(theta[1]) / sinf(theta[0]);
	s[1] = sinf(theta[1]) / sinf(theta[0]);
	i = -1;
	while (++i < 4)
		out[i] = s[0] * a[i] + s[1] * sign * b[i];
}
