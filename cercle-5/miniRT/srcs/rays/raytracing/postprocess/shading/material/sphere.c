/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

int	get_sphere_mat(t_shading *ctx)
{
	t_hit	*h;

	h = ctx->hit;
	if (h->ref.index >= 0 && h->ref.index < ctx->scene->sphere_count)
		return (ctx->scene->spheres[h->ref.index].mat_id);
	return (0);
}
