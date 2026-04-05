/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 15:26:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_obj(t_obj *c)
{
	if (!c)
		return ;
	ft_print_debug("obj(\n");
	ft_print_debug("  temp_v: %zu/%zu, ", c->v_count, c->v_cap);
	ft_print_debug("temp_vt: %zu/%zu, ", c->vt_count, c->vt_cap);
	ft_print_debug("temp_vn: %zu/%zu\n", c->vn_count, c->vn_cap);
	ft_print_debug("  out_v: %zu/%zu, ", c->out_v_count, c->out_v_cap);
	ft_print_debug("out_i: %zu/%zu\n", c->out_i_count, c->out_i_cap);
	ft_print_debug("  bbox: ");
	print_aabb(&c->bbox);
	ft_print_debug("\n)");
}
