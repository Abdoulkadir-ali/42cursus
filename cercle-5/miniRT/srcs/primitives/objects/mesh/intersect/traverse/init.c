/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

void	intersect_init(t_trace *trace, t_hit *hit)
{
	trace->top = 0;
	trace->node_idx = 0;
	trace->best_tri = (t_index){0, true};
	trace->best_uv = (t_vec2){0, 0};
	trace->best_t = hit->t;
}
