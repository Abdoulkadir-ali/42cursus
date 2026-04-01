/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_reflect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:51:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 15:51:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec3	vec3_reflect(t_vec3 i, t_vec3 n)
{
	return (vec3_sub(i, vec3_scale(n, 2 * vec3_dot(i, n))));
}

static void	handle_refract_side(double *cosi, t_vec3 *n, double *etai,
		double *etat)
{
	double	tmp;

	if (*cosi < 0)
	{
		*cosi = -*cosi;
		*n = vec3_scale(*n, -1.0);
		tmp = *etai;
		*etai = *etat;
		*etat = tmp;
	}
}

t_vec3	vec3_refract(t_vec3 i, t_vec3 n, double ior)
{
	double	cosi;
	double	etai_etat[2];
	double	eta_k[2];
	t_vec3	norm;

	cosi = -fmax(-1.0, fmin(1.0, vec3_dot(i, n)));
	etai_etat[0] = 1.0;
	etai_etat[1] = ior;
	norm = n;
	handle_refract_side(&cosi, &norm, &etai_etat[0], &etai_etat[1]);
	eta_k[0] = etai_etat[0] / etai_etat[1];
	eta_k[1] = 1.0 - eta_k[0] * eta_k[0] * (1.0 - cosi * cosi);
	if (eta_k[1] < 0)
		return ((t_vec3){0, 0, 0, 0});
	return (vec3_add(vec3_scale(i, eta_k[0]),
			vec3_scale(norm, eta_k[0] * cosi - sqrt(eta_k[1]))));
}
