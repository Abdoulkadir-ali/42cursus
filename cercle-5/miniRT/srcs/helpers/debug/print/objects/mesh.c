/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 15:26:06 by abdoali          ###   ########.fr       */
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
	ft_print_debug("mesh(\n  name: %s\n", name);
	ft_print_debug("  tri_count: %zu\n  mat_id: %zu\n  bbox: ",
		m->tri_count, m->mat_id);
	print_aabb(&m->bbox);
	ft_print_debug("\n  transform: ");
	print_transform(&m->transform);
	ft_print_debug("\n)");
}
