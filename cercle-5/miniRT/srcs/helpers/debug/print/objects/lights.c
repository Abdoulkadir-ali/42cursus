/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 15:26:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_light(t_light *l)
{
	const char	*type;

	if (!l)
		return ;
	type = "SPOT";
	if (l->type == LIGHT_POINT)
		type = "POINT";
	ft_print_debug("light(\n  type: %s\n  transform: ", type);
	print_transform(&l->transform);
	ft_print_debug("\n  brightness: %.4f\n  rgb: ", l->brightness);
	print_vec3(&l->rgb);
	ft_print_debug("\n  cutoff: %.4f\n)", l->cutoff);
}

void	print_camera(t_camera *c)
{
	if (!c)
		return ;
	ft_print_debug("camera(\n  transform: ");
	print_transform(&c->transform);
	ft_print_debug("\n  fov: %.4f\n)", c->fov);
}

void	print_ambient(t_ambient *a)
{
	if (!a)
		return ;
	ft_print_debug("ambient(\n  brightness: %.4f\n  rgb: ", a->brightness);
	print_vec3(&a->rgb);
	ft_print_debug("\n)");
}
