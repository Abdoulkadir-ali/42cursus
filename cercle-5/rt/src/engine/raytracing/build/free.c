/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:56:15 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 00:56:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	bvh_free(t_bvh *bvh)
{
	free(bvh->nodes);
	free(bvh->indices);
	free(bvh->soa_tris);
	memset(bvh, 0, sizeof(*bvh));
}
