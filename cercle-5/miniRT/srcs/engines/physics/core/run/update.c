/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:04:51 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 14:22:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static void	integrate_and_ccd(t_physics *phys, double dt)
{
	int	i;
	int	count;

	if (!phys->soa)
		return ;
	integrate_bodies(phys, dt);
	count = (int)phys->soa->count;
	i = 0;
	while (i < count)
	{
		phys_resolve_ccd(phys, i, dt);
		i++;
	}
}

static void	solve_contact_iterations(t_physics *phys, t_contact *contacts,
		int num_contacts)
{
	int	i;

	if (num_contacts <= 0)
		return ;
	i = 0;
	while (i < SOLVER_ITERATIONS)
	{
		solve_velocities(phys, contacts, num_contacts);
		solve_positions(phys, contacts, num_contacts);
		i++;
	}
}

void	update_physics(t_physics *phys, double dt)
{
	t_contact	contacts[MAX_CONTACTS];
	int			num_contacts;

	if (!phys)
		return ;
	integrate_and_ccd(phys, dt);
	num_contacts = generate_contacts(phys, contacts, MAX_CONTACTS);
#ifdef DEBUG_PHYSICS
	ft_print_debug("Physics: %d contacts, dt=%.4f\n", num_contacts, dt);
#endif
	solve_contact_iterations(phys, contacts, num_contacts);
}
