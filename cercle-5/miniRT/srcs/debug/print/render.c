/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:42:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "debug.h"

void	print_render_state(t_render_state *r)
{
	if (!r)
		return ;
	printf("render_state(\n");
	printf("  scale:      %d\n", r->scale);
	printf("  dirty:      %s\n", r->dirty ? "true" : "false");
	printf("  fps:        %.2f\n", r->fps);
	printf("  proj_dirty: %s\n", r->proj_dirty ? "true" : "false");
	printf("  num_cores:  %d\n", r->num_cores);
	printf(")\n");
}

void	print_rt_engine(t_rt_engine *rt)
{
	if (!rt)
		return ;
	printf("rt_engine(\n");
	printf("  baked_version:  %u\n", rt->baked_version);
	printf("  bvh:            %s\n", rt->bvh ? "set" : "NULL");
	printf("  texture_count:  %d\n", rt->texture_count);
	printf("  emissive_n:     %d\n", rt->emissive_n);
	printf(")\n");
}
