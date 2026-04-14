/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particles.h"

static void	swap_p_pv(t_particle_soa *soa, size_t a, size_t b)
{
	double	tmp;

	tmp = soa->px[a];
	soa->px[a] = soa->px[b];
	soa->px[b] = tmp;
	tmp = soa->py[a];
	soa->py[a] = soa->py[b];
	soa->py[b] = tmp;
	tmp = soa->pz[a];
	soa->pz[a] = soa->pz[b];
	soa->pz[b] = tmp;
	tmp = soa->vx[a];
	soa->vx[a] = soa->vx[b];
	soa->vx[b] = tmp;
	tmp = soa->vy[a];
	soa->vy[a] = soa->vy[b];
	soa->vy[b] = tmp;
	tmp = soa->vz[a];
	soa->vz[a] = soa->vz[b];
	soa->vz[b] = tmp;
}

static void	swap_p(t_particle_soa *soa, size_t a, size_t b)
{
	double	tmp;

	swap_p_pv(soa, a, b);
	tmp = soa->age[a];
	soa->age[a] = soa->age[b];
	soa->age[b] = tmp;
	tmp = soa->life[a];
	soa->life[a] = soa->life[b];
	soa->life[b] = tmp;
	tmp = soa->temp[a];
	soa->temp[a] = soa->temp[b];
	soa->temp[b] = tmp;
	tmp = soa->size[a];
	soa->size[a] = soa->size[b];
	soa->size[b] = tmp;
}

void	age_and_kill(t_particle_soa *soa, double dt)
{
	size_t	i;
	size_t	last;

	i = 0;
	while (i < soa->alive)
	{
		soa->age[i] += dt;
		if (soa->life[i] > 1e-9)
			soa->temp[i] = soa->temp[i] * (1.0 - dt / soa->life[i]);
		if (soa->age[i] >= soa->life[i])
		{
			last = soa->alive - 1;
			if (i != last)
				swap_p(soa, i, last);
			soa->alive--;
		}
		else
			i++;
	}
}
