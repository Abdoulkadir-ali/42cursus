/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:22:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

void	phys_init(t_phys_world *w)
{
	memset(w, 0, sizeof(*w));
	w->cell_size = 1.0f;
	w->time_scale = 1.0f;
}

void	phys_free(t_phys_world *w)
{
	free(w->bodies);
	free(w->cell_count);
	free(w->cell_start);
	free(w->cell_items);
	memset(w, 0, sizeof(*w));
}
