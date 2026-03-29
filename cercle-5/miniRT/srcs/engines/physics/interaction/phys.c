/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 08:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 14:33:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

int	get_phys_body(t_physics *phys, int prim_idx)
{
	if (!phys || prim_idx < 0)
		return (-1);
	return (phys->scene->primitives.phys_idx[prim_idx]);
}
