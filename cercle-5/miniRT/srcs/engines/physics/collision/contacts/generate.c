/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 17:11:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Unified entry point for contact generation.
 * Combines dynamic actor pairs (DBVT) and static environment pairs (Plane).
 */
static int	gather_dbvt_contacts(t_physics *phys,
		t_contact *contacts, int max_c)
{
	(void)phys;
	(void)contacts;
	(void)max_c;
	return (0);
}

static int	gather_plane_contacts(t_physics *phys,
		t_contact *contacts, int max_c)
{
	(void)phys;
	(void)contacts;
	(void)max_c;
	return (0);
}

int	generate_contacts(t_physics *phys, t_contact *contacts, int max_c)
{
	int	c;
	int	n;

	c = gather_dbvt_contacts(phys, contacts, max_c);
	n = gather_plane_contacts(phys, &contacts[c], max_c - c);
	return (c + n);
}
