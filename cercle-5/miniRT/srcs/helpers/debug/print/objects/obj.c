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

void	print_obj(t_obj *c)
{
	if (!c)
		return ;
	printf("obj(\n");
	printf("  temp_v: %zu/%zu, ", c->v_count, c->v_cap);
	printf("temp_vt: %zu/%zu, ", c->vt_count, c->vt_cap);
	printf("temp_vn: %zu/%zu\n", c->vn_count, c->vn_cap);
	printf("  out_v: %zu/%zu, ", c->out_v_count, c->out_v_cap);
	printf("out_i: %zu/%zu\n", c->out_i_count, c->out_i_cap);
	printf("  bbox: ");
	print_aabb(&c->bbox);
	printf("\n)");
}
