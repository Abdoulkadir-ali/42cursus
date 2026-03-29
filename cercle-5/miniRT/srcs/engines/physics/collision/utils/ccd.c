/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ccd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:00:43 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 12:00:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

void phys_resolve_ccd(t_physics *phys, int body_idx, double dt)
{
	(void)dt;
	t_physics_soa *pso;

	pso = phys->soa;
	pso->hot.vx[body_idx] *= -0.1f;
	pso->hot.vy[body_idx] *= -0.1f;
	pso->hot.vz[body_idx] *= -0.1f;
}
