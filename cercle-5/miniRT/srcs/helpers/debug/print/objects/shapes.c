/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 15:26:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_sphere(t_sphere *s)
{
	if (!s)
		return ;
	ft_print_debug("sphere(\n  transform: ");
	print_transform(&s->transform);
	ft_print_debug("\n  radius_sq: %.4f\n", s->radius_sq);
	ft_print_debug("  mat_id: %zu\n)", s->mat_id);
}

void	print_plane(t_plane *p)
{
	if (!p)
		return ;
	ft_print_debug("plane(\n  transform: ");
	print_transform(&p->transform);
	ft_print_debug("\n  mat_id: %zu\n)", p->mat_id);
}

void	print_cylinder(t_cylinder *c)
{
	if (!c)
		return ;
	ft_print_debug("cylinder(\n  transform: ");
	print_transform(&c->transform);
	ft_print_debug("\n  mat_id: %zu\n)", c->mat_id);
}

void	print_cone(t_cone *c)
{
	if (!c)
		return ;
	ft_print_debug("cone(\n  transform: ");
	print_transform(&c->transform);
	ft_print_debug("\n  mat_id: %zu\n)", c->mat_id);
}
