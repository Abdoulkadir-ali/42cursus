/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 12:48:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

extern int	gather_dbvt_contacts(t_physics *p, t_contact *contacts, int max_c);
extern int	gather_plane_contacts(t_physics *p, t_contact *contacts, int max_c);

/**
 * @brief Unified entry point for contact generation.
 * Combines dynamic actor pairs (DBVT) and static environment pairs (Plane).
 */
int	generate_contacts(t_physics *phys, t_contact *contacts, int max_c)
{
	int	c;
	int	n;

	c = gather_dbvt_contacts(phys, contacts, max_c);
	n = gather_plane_contacts(phys, &contacts[c], max_c - c);
	return (c + n);
}
