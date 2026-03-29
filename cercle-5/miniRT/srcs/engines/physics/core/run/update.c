/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:04:51 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 15:10:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "debug.h"

static void	integrate_and_ccd(t_physics *phys, double dt)
{
	int	i;
	int	count;

	if (!phys->soa)
		return ;
	DBG_TRACE_MSG(DBG_CH_PHYSICS, "integrate_and_ccd: before integrate_bodies\n");
	integrate_bodies(phys, dt);
	DBG_TRACE_MSG(DBG_CH_PHYSICS, "integrate_and_ccd: after integrate_bodies\n");
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
	DBG_TRACE_MSG(DBG_CH_PHYSICS, "solve_contact_iterations: starting %d contacts\n", num_contacts);
	while (i < SOLVER_ITERATIONS)
	{
		solve_velocities(phys, contacts, num_contacts);
		solve_positions(phys, contacts, num_contacts);
		i++;
	}
	DBG_TRACE_MSG(DBG_CH_PHYSICS, "solve_contact_iterations: done\n");
}

void	update_physics(t_physics *phys, double dt)
{
	t_contact	contacts[MAX_CONTACTS];
	int			num_contacts;

	if (!phys || !phys->soa || phys->soa->count == 0)
		return ;
	DBG_TRACE_MSG(DBG_CH_PHYSICS, "update_physics: start dt=%.4f\n", dt);
	integrate_and_ccd(phys, dt);
	num_contacts = generate_contacts(phys, contacts, MAX_CONTACTS);
	DBG_TRACE_MSG(DBG_CH_PHYSICS, "update_physics: generated %d contacts\n", num_contacts);
	solve_contact_iterations(phys, contacts, num_contacts);
	scene_mark_dirty(phys->scene);
	if (phys->scene)
		phys->baked_version = phys->scene->version;
	DBG_TRACE_MSG(DBG_CH_PHYSICS, "update_physics: done, marked dirty and synced version to %d\n", phys->baked_version);
}
