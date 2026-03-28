/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbvt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:04:02 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 13:04:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static int process_pair(t_scene *s, t_body_pair *p, t_contact *contacts, int c)
{
	(void)s;
	(void)p;
	(void)contacts;
	(void)c;
	return (0);
}

int gather_dbvt_contacts(t_physics *phys, t_contact *contacts, int max_c)
{
	(void)phys;
	(void)contacts;
	(void)max_c;
	(void)process_pair;
	return (0);
}
