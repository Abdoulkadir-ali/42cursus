/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 20:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 18:32:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pathfinder.h"

bool	pf_get_next_step(const t_map *m, t_pathfinder_params p)
{
	return (pf_search(m, p, true));
}
