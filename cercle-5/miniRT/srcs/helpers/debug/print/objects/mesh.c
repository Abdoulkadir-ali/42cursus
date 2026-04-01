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

void	print_mesh(t_mesh *m)
{
	const char	*name;

	if (!m)
		return ;
	name = "NULL";
	if (m->name)
		name = m->name;
	printf("mesh(\n  name: %s\n", name);
	printf("  tri_count: %d\n  mat_id: %d\n  bbox: ",
		m->tri_count, m->mat_id);
	print_aabb(&m->bbox);
	printf("\n  transform: ");
	print_transform(&m->transform);
	printf("\n)");
}
