/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

extern int	gather_dbvt_contacts(t_scene *s, t_contact *contacts, int max_c);
extern int	gather_plane_contacts(t_scene *s, t_contact *contacts, int max_c);

/**
 * @brief Unified entry point for contact generation.
 * Combines dynamic actor pairs (DBVT) and static environment pairs (Plane).
 */
int	generate_contacts(t_scene *scene, t_contact *contacts, int max_c)
{
	int	c;
	int	n;

	c = gather_dbvt_contacts(scene, contacts, max_c);
	n = gather_plane_contacts(scene, &contacts[c], max_c - c);
	return (c + n);
}
