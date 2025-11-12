/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:24:11 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 19:20:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int	lerp_color(int c1, int c2, double t)
{
	t_vec3	c1_vec;
	t_vec3	c2_vec;
	t_vec3	result_vec;

	c1_vec.x = get_red(c1);
	c1_vec.y = get_green(c1);
	c1_vec.z = get_blue(c1);
	c2_vec.x = get_red(c2);
	c2_vec.y = get_green(c2);
	c2_vec.z = get_blue(c2);
	result_vec.x = c1_vec.x + (c2_vec.x - c1_vec.x) * t;
	result_vec.y = c1_vec.y + (c2_vec.y - c1_vec.y) * t;
	result_vec.z = c1_vec.z + (c2_vec.z - c1_vec.z) * t;
	return (create_color((int)result_vec.x, (int)result_vec.y, (int)result_vec.z));
}