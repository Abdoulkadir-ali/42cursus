/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 15:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "debug.h"

void	print_sphere(t_sphere *s)
{
	if (!s)
		return ;
	printf("sphere(\n  center: ");
	print_vec3(&s->center);
	printf("\n  radius: %.4f\n", s->radius);
	printf("  mat_idx: %d\n)", s->mat_idx);
}

void	print_plane(t_plane *p)
{
	if (!p)
		return ;
	printf("plane(\n  point: ");
	print_vec3(&p->point);
	printf("\n  normal: ");
	print_vec3(&p->normal);
	printf("\n  mat_idx: %d\n)", p->mat_idx);
}

void	print_cylinder(t_cylinder *c)
{
	if (!c)
		return ;
	printf("cylinder(\n  pos: ");
	print_vec3(&c->pos);
	printf("\n  mat_idx: %d\n)", c->mat_idx);
}

void	print_cone(t_cone *c)
{
	if (!c)
		return ;
	printf("cone(\n  tip: ");
	print_vec3(&c->tip);
	printf("\n  mat_idx: %d\n)", c->mat_idx);
}
