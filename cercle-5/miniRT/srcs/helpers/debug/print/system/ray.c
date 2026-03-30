/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 15:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "raytracing.h"

void	print_ray(t_ray *r)
{
	if (!r)
		return ;
	printf("ray(\n  origin: ");
	print_vec3(&r->origin);
	printf("\n  direction: ");
	print_vec3(&r->direction);
	printf("\n  inv_dir: ");
	print_vec3(&r->inv_dir);
	printf("\n  sign: [%d, %d, %d]\n)",
		r->sign[0], r->sign[1], r->sign[2]);
}

void	print_hit(t_hit *h)
{
	if (!h)
		return ;
	printf("hit(\n  t: %.4f\n  point: ", h->t);
	print_vec3(&h->point);
	printf("\n  normal: ");
	print_vec3(&h->normal);
	printf("\n  uv: (%.4f, %.4f)\n", h->u, h->v);
	printf("  ref: type: %d, index: %d\n)", h->ref.type, h->ref.index);
}
