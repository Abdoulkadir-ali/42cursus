/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:36:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

/**
 * @brief Advance to the next loaded map.
 * @param m Map collection whose current entry must change.
 */
void	cycle_map(t_maps *m)
{
	if (!m->maps || m->count == 0)
		return ;
	m->current_index = (m->current_index + 1) % m->count;
	m->current_map = m->maps[m->current_index];
}
