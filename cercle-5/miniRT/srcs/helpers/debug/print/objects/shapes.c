/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 15:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_sphere(t_sphere *s)
{
	if (!s)
		return ;
	printf("sphere(\n  transform: ");
	print_transform(&s->transform);
	printf("\n  radius_sq: %.4f\n", s->radius_sq);
	printf("  mat_id: %zu\n)", s->mat_id);
}

void	print_plane(t_plane *p)
{
	if (!p)
		return ;
	printf("plane(\n  transform: ");
	print_transform(&p->transform);
	printf("\n  mat_id: %zu\n)", p->mat_id);
}

void	print_cylinder(t_cylinder *c)
{
	if (!c)
		return ;
	printf("cylinder(\n  transform: ");
	print_transform(&c->transform);
	printf("\n  mat_id: %zu\n)", c->mat_id);
}

void	print_cone(t_cone *c)
{
	if (!c)
		return ;
	printf("cone(\n  transform: ");
	print_transform(&c->transform);
	printf("\n  mat_id: %zu\n)", c->mat_id);
}
