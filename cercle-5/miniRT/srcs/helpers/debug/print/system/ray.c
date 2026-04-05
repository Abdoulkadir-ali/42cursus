/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 15:26:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_ray(t_ray *r)
{
	if (!r)
		return ;
	ft_print_debug("ray(\n  origin: ");
	print_vec3(&r->origin);
	ft_print_debug("\n  direction: ");
	print_vec3(&r->direction);
	ft_print_debug("\n  inv_dir: ");
	print_vec3(&r->inv_dir);
	ft_print_debug("\n  sign: [%d, %d, %d]\n)",
		r->sign[0], r->sign[1], r->sign[2]);
}

void	print_hit(t_hit *h)
{
	if (!h)
		return ;
	ft_print_debug("hit(\n  t: %.4f\n  point: ", h->t);
	print_vec3(&h->point);
	ft_print_debug("\n  normal: ");
	print_vec3(&h->normal);
	ft_print_debug("\n  uv: (%.4f, %.4f)\n", h->u, h->v);
	ft_print_debug("  ref: type: %d, index: %zu\n)", h->ref.type, h->ref.index);
}
