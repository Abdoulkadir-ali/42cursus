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

#include "objects.h"
#include "debug.h"

void	print_mesh(t_mesh *m)
{
	if (!m)
		return ;
	printf("mesh(\n  tri_start: %d\n  mat_id: %d\n  bbox: ",
		m->tri_start, m->mat_id);
	print_aabb(&m->bbox);
	printf("\n  transform: ");
	print_transform(&m->transform);
	printf("\n)");
}
