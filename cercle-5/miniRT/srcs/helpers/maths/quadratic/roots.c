/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roots.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

/*
** Numerically stable quadratic solver (Kahan's method).
** Computes the larger-magnitude root first using sign(b)*sqrt(disc)
** to avoid catastrophic cancellation, then derives the second root
** via Vieta's formula (t1 * t2 = c/a).
** Precomputes inv_2a to replace two divisions with one multiply each.
*/
bool	solve_quadratic(t_quadratic q, t_quadratic_roots *roots)
{
	double	disc;
	double	sqrt_d;
	double	sign_b;
	double	inv_2a;

	if (fabs(q.a) < EPSILON)
		return (false);
	disc = q.b * q.b - 4.0 * q.a * q.c;
	if (disc < 0.0)
		return (false);
	sqrt_d = sqrt(disc);
	inv_2a = 1.0 / (2.0 * q.a);
	if (q.b >= 0.0)
		sign_b = 1.0;
	else
		sign_b = -1.0;
	roots->t1 = (-q.b - sign_b * sqrt_d) * inv_2a;
	if (fabs(roots->t1) < EPSILON)
		roots->t2 = 0.0;
	else
		roots->t2 = (q.c / q.a) / roots->t1;
	return (true);
}
