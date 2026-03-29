/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:42:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "debug.h"

void	print_physics(t_physics *phys)
{
	if (!phys)
		return ;
	printf("physics(\n");
	printf("  gravity:      ");
	print_vec3(&phys->gravity);
	printf("\n");
	printf("  damping:      %.4f\n", phys->damping);
	printf("  fixed_dt:     %.6f\n", phys->fixed_dt);
	printf("  solver_iters: %d\n", phys->solver_iters);
	printf("  needs_bake:   %s\n", phys->needs_bake ? "true" : "false");
	printf("  baked_ver:    %u\n", phys->baked_version);
	printf(")\n");
}
