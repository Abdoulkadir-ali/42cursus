/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:02:34 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 13:02:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"


int sphere_plane_contacts(t_scene *s, int idx, t_gjk_shape *sa, t_contact *c, int count, int max)
{
	(void)s; (void)idx; (void)sa; (void)c; (void)count; (void)max;
	return count;
}
